#include "reader.h"
#include <sancus/sm_support.h>
#include <sancus_support/sm_io.h>

DECLARE_SM(reader, 0x1234);

void SM_FUNC(reader) my_memcpy(char *dest, char *src, size_t sz)
{
    int i;
    for (i = 0; i < sz; i++)
        dest[i] = src[i];
}

void SM_FUNC(reader) my_memset(char *dest, char c, size_t sz)
{
    int i;
    for (i = 0; i < sz; i++)
        dest[i] = c;
}

void SM_ENTRY(reader) spray_stack_secret(void)
{
    volatile char buf[100];
    int i;
    for (i = 0; i < 100; i++)
        buf[i] = 'S';
}

void SM_ENTRY(reader) get_readings(nonce_t no, ReaderOutput* out)
{
    ReaderOutput my_out;
    //my_memset((char*) &my_out, 'S', sizeof(ReaderOutput));
    my_out.a = 'A';
    my_out.b = 0x1;

    /* Ensure output memory range about to be dereferenced lies outside SM. */
    ASSERT(sancus_is_outside_sm(reader, out, sizeof(ReaderOutput)));
    my_memcpy((char*) out, (char*) &my_out, sizeof(ReaderOutput));
}
