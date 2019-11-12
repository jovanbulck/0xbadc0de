## Sample output

```
../../build/sgx-lkl-run sgxlkl-disk.img app/helloworld 123 test
enclave_start = 0x7f4407c43000
ubase = 0x7f43f8000000


------------------------------
attacker: enter offset from ubase, current arguments[1]=0x7ffd2ddc6734 > 26797a8

attacker: replacing untrusted string pointer argv[1] with adrs 0x7f43fa6797a8
------------------------------




Hello world from enclaved application binary!
        --> enclave secret at 0x7f43fa6797a8


Echoing user-provided command line arguments
        argv[0] @0x7ffd2ddc6725 = 'app/helloworld'
        argv[1] @0x7f43fa6797a8 = 'super secret enclave string'
        argv[2] @0x7ffd2ddc6738 = 'test'
```
