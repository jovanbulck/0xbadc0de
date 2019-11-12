#ifndef READER_H
#define READER_H

#include <sancus/sm_support.h>

extern struct SancusModule reader;

typedef struct
{
    char a;
    int b;
} ReaderOutput;

typedef unsigned nonce_t;

void SM_ENTRY(reader) spray_stack_secret(void);
void SM_ENTRY(reader) get_readings(nonce_t no, ReaderOutput* out);

#endif
