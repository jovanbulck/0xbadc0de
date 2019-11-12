## Sample output

```
../../build/sgx-lkl-run sgxlkl-disk.img app/helloworld
sgx.c: ubase = 0x7feed8000000, size = 5d7f -> end = 0x7feed8005d7e
ubase = 0x7feed8000000
enclave: super secret string at 0x7feeda678aa0
sgxlkl_run.c: Forward signal with siginfo at 0x7feee09ca7f0, signum = 4, siginfo.arg = 0x33bb4a46074
Oho, I will modify it then to 0x7feeda678aa0
DORESUME
tsc = 7465726365732072
Hello World!
```
