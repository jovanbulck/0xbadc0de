#include <string.h>

char buf[] = {'A', 0x00, 'B', 'C', 'D', 0x00};

int ecall_strlen( void )
{
    //asm ("std");
    int rv = strlen(&buf[4]);
    //asm ("cld");
    return rv;
}

void ecall_memset( char *out )
{
    //asm ("std");
    memset(&out[50], 'A', 50);
    //asm ("cld");
}

void ecall_edger8r( char *buf )
{
    /*
     * This ecall expects buf[] to be memset to zero in the edger8r code. However,
     * setting DF=1 before EENTER causes the memset direction to be inverted and the
     * preceding heap fields to be corrupted. This ultimately leads to a
     * (non-exploitable) crash on the next free() invocation in the edger8r
     * code. The malloc chunk's size and prev_meta_data_ptr fields are
     * erroneously zeroed, leading to an illegal pointer computation.
     * Fortunately, the resulting NULL pointer is XORed with a secret 64-bit
     * `mparam.magic` value, leading to a non-canonical address dereference and
     * a #GP that eventually halts the enclave.
     */
    return;
}

inline void __attribute__((always_inline)) maccess(void *p)
{
    asm volatile("movb (%0), %%cl\n" : : "c"(p) :);
}

void ecall_leak_df( int secret, char *p )
{
    if (secret)
        asm ("std");
    else
        asm ("cld");

    /*
     * Provoke page fault so we can determine whether AEX properly clears the
     * enclave's RFLAGS.DF (note that a real-world adversary could use a
     * precise enclave interrupt framework like SGX-Step to probe this
     * information after _every_ single instruction.
     */
    maccess(p);
    volatile char c = *p;

    asm ("cld");
}
