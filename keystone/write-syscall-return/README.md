## Building and running

changes: 

```
cd keystone/sdk
make

cd keystone/sdk/examples/hello
./vault.sh

cd keystone
make image

./scripts/run-qemu.sh

root
sifive

insmod keystone-driver.ko
cd hello
./hello.ke
```

## Sample output
```
$ cd hello/
$ ./hello.ke 
Verifying archive integrity... All good.
Uncompressing Keystone vault archive  100%  
Syscall no. 40
write(128)
The quick brown fox jumps over the lazy dog The quick brown fox jumps over the lazy dog The quick brown fox jumps over the lazy Syscall no. 40
write(92)
dog The quick brown fox jumps over the lazy dog The quick brown fox jumps over the lazy dogboom
Syscall no. 40
write(128)
--> buff at %p

 %d byte written, %d remaining
super secret enclave string--> enclave secret '%s' at %p

libc-Syscall no. 40
write(181)
--> buff at 0x61c10

 128 byte written, 92 remaining

 93 byte written, -1 remaining

 128 byte written, -129 remaining
--> enclave secret 'super secret enclave string' at 0x61d28
```
