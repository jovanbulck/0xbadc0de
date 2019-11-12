#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sgx_lfence.h>

/* NOTE: The following byte buffer fits _within_ a 64B cache line (and 4KiB page) */
uint8_t __attribute__ ((aligned(0x1000))) lut[] = {'A', 'B', 'C', 'D', 'E'};

uint16_t ecall_data_lookup( uint8_t input )
{
    if (input > 3) return 0;
    sgx_lfence();

    uint16_t *p = (uint16_t*) (lut+input);
    return *p;
}

uint8_t *cptr = NULL;
uint16_t *iptr  = NULL;

uint16_t ecall_control_flow( uint8_t input )
{
    if (!cptr)
    {
        /* Default 16 byte alignment in malloc is specified in x86_64 abi. */
        cptr = malloc(sizeof(uint16_t));
        iptr = (uint16_t*) (cptr + 1);
    }

    /* NOTE: The following conditional control flow and data accesses might
     * exist _within_ a 64B cache line (and 4KiB page) */
    if (input)
        *cptr = 1;
    else
        *iptr = 1;

    return 0;
}
