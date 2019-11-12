#include <msp430.h>
#include <stdio.h>
#include <sancus/sm_support.h>
#include <sancus_support/sm_io.h>
#include "reader.h"

int main()
{
    msp430_io_init();

    pr_info1("sizeof(ReaderOutput)=%d; enabling sensor/reader SMs..\n", sizeof(ReaderOutput));
    sancus_enable(&reader);
    pr_sm_info(&reader);

    pr_info("requesting sensor readings..");
    nonce_t no = 0xabcd;
    ReaderOutput out;

    spray_stack_secret();
    get_readings(no, &out);

    pr_info1("dumping sealed output from reader SM (secret=%x)\n", 'S');
    dump_buf((uint8_t*)&out, sizeof(out), "OUT");

    pr_info("all done!");
    EXIT();
}
