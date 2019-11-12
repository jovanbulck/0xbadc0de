Expected output:

```
sancus-cc -I"/usr/local/share/sancus-support"/include/ -Wfatal-errors -fcolor-diagnostics -Os -g   -c -o main.o main.c
sancus-cc -I"/usr/local/share/sancus-support"/include/ -Wfatal-errors -fcolor-diagnostics -Os -g   -c -o reader.o reader.c
sancus-ld -L"/usr/local/share/sancus-support"/lib/ --ram 16K --rom 41K  -lsm-io -ldev --inline-arithmetic --standalone --verbose -o no_mac_main.elf main.o reader.o sensor.o
INFO: Found new Sancus modules:
INFO:  * reader:
INFO:   - Entries: get_readings, spray_stack_secret
INFO:   - No calls to other modules
INFO:   - Unprotected calls: puts
INFO: No existing Sancus modules found
INFO: Found asm MMIO Sancus modules:
INFO:  * sensor
INFO:   - Entries: read_sensor_data
INFO:   - Config: callerID=any, private data=[0x190, 0x198[
INFO: Found MSP430 install directory: /usr/msp430
INFO: Found MSP430 GCC install directory: /usr/lib/gcc/msp430/4.6.3
INFO: Using output file no_mac_main.elf
sancus-crypto --fill-macs --key 4078d505d82099ba --verbose -o main.elf no_mac_main.elf
unbuffer sancus-sim --ram 16K --rom 41K  main.elf | tee sim.out
Starting Verilog simulation. Press <Ctrl-C> to get to the Icarus Verilog CLI, then "finish" to exit.
******************************
* Sancus simulation started  *
* ROM: 41984B                *
* RAM: 16384B                *
******************************
=== Spongent parameters ===
Rate:        18
State size: 176
===========================
=== SpongeWrap parameters ===
Rate:           16
Security:       64
Blocks in key:   4
=============================
=== File I/O ===
Input:  'sim-input.bin'
Output: 'sim-output.bin'
================
FST info: dumpfile sancus_sim.fst opened for output.

------


[main.c] sizeof(ReaderOutput)=4; enabling sensor/reader SMs..
New SM config: 6fb8 71d8 02a8 03b0, 0
Vendor key: 4078d505d82099ba
................................................................................................................................................................................................................................................................................
SM key: 0be5007503e484e7
SM reader with ID 1 enabled : 0x6fb8 0x71d8 0x02a8 0x03b0
[main.c] requesting sensor readings..
[main.c] dumping sealed output from reader SM (secret=53)
OUT (32 bits) is: 41530100
[main.c] all done!
 ===============================================
|               SIMULATION PASSED               |
 ===============================================
```
