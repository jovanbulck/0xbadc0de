## Sample output

```
../../build/sgx-lkl-run sgxlkl-disk.img app/helloworld
enclave_start = 0x7fde05415000
ubase = 0x7fddf8000000

The quick brown fox jumps over the lazy dog The quick brown fox jumps over the lazy dog The quick brown fox jumps over the lazy Hello world from enclaved application binary!
 128 byte written, 92 remaining
dog The quick brown fox jumps over the lazy dog The quick brown fox jumps over the lazy dog
 Faulting write() to stdout: 0x7fde09c15000 92 92

 93 byte written, -1 remaining

 %d byte written, %d remaining
super secret enclave string     --> enclave secret at %p

zRx
$
 128 byte written, -129 remaining
        --> enclave secret at 0x7fddfa61e969

```
