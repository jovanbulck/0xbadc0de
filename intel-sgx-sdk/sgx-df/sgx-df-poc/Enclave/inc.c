#include <string.h>
#include <stdlib.h>

char buf[] = {'A', 0x00, 'B', 'C', 'D', 0x00};

int ecall_strlen( void )
{
    /* Clearly, this enclaved computation should always return '1'. */
    return strlen(&buf[4]);
}

void ecall_memset( char *out )
{
    /*
     * NOTE: We use [user_check] here for demo purposes (otherwise the enclave
     * crashes from a heap corruption in edger8r-generated code, cf. below).
     */
    memset(&out[50], 'A', 50);
}

char *chunk;
void my_init_chunk( char c)
{
    for (int i=0; i < 100; i++)
        chunk[i] = c;
}

void ecall_fill_heap( char c )
{
    /*
     * After freeing this chunk, subsequent (uninitialized) malloc allocations
     * may contain secrets. (We use a helper function to prevent the compiler
     * from optimizing out the initialization).
     */
    chunk = malloc(100);
    my_init_chunk(c);
    free(chunk);
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

void ecall_leak_df( int set, int scrub, char *p )
{
    /* RFLAGS.DF may leak to untrusted runtime if not scrubbed before EEXIT/AEX */
    if (set)
        asm("std");

    /*
     * Provoke page fault so we can determine whether AEX properly clears the
     * enclave's RFLAGS.DF (note that a real-world adversary could use a
     * precise enclave interrupt framework like SGX-Step to probe this
     * information after _every_ single enclave instruction.
     */
    volatile char c = *p; 

    if (scrub)
        asm("cld");
}
