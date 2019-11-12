## Sample output (crash triggered by attacker)

```
SGX=1 ./pal_loader readdir
[P04529] set tcb to 0xffe9938
[P04529] host: Linux-SGX
[P04529] initial random value: 950cfec99084ffd3
[P04529] bkeep_unmapped: 0xba9b000-0xba9d000 => vma
[P04529] allocate 0xba9b000-0xba9d000 for vmas
[P04529] Converting early VMA [0xbd72060] 0x400000-0x602000
[P04529] Converting early VMA [0xbd720a8] 0xffff000-0xffff764
[P04529] Converting early VMA [0xbd720f0] 0xba9b000-0xba9d000
[P04529] heap top adjusted to 0xae36000
[P04529] bkeep_unmapped: 0xba8a000-0xba9b000 => slab
[P04529] bkeep_unmapped: 0xba87000-0xba8a000 => slab
[P04529] bkeep_unmapped: 0xba83000-0xba87000 => slab
[P04529] bkeep_unmapped: 0xba7e000-0xba83000 => slab
[P04529] bkeep_unmapped: 0xba77000-0xba7e000 => slab
[P04529] shim loaded at 0xba9e000, ready to initialize
[P04529] bkeep_unmapped: 0xba76000-0xba77000 => slab
[P04529] bkeep_unmapped: 0xba74000-0xba76000 => slab
[P04529] mounting default root filesystem
[P04529] bkeep_unmapped: 0xba72000-0xba74000 => slab
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7ffe1cfa1a34 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7ffe1cfa1a34 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7ffe1cfa1a34 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7ffe1cfa1a34 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 992
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 992
enclave_ocalls.c: Copied 992 byte from 0x7ffe1cfa1a35 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 992
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7ffe1cfa1a34 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 632
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 632
enclave_ocalls.c: Copied 632 byte from 0x7ffe1cfa1a35 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 632
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 0
enclave_ocalls.c: Copied 0 byte from 0x7ffe1cfa1a37 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 0
[P04529] bkeep_unmapped: 0xba70000-0xba72000 => slab
[P04529] bkeep_unmapped: 0xba6d000-0xba70000 => slab
[P04529] bkeep_munmap: 0xba70000-0xba72000
[P04529] bkeep_unmapped: 0xba68000-0xba6d000 => slab
[P04529] bkeep_munmap: 0xba6d000-0xba70000
[P04529] bkeep_munmap: 0xba72000-0xba74000
[P04529] bkeep_munmap: 0xba68000-0xba6d000
[P04529] mounting as proc filesystem: /proc
[P04529] mounting as dev filesystem: /dev
[P04529] mounting as chroot filesystem: from dev:tty to /dev
[P04529] bkeep_unmapped: 0xba73000-0xba74000 => slab
[P04529] bkeep_unmapped: 0xba72000-0xba73000 => slab
[P04529] adding port (handle 0xbfa9db0) for process 0 (type 0001)
[P04529] creating pipe: pipe.srv:1781412509
[P04529] adding port (handle 0xbfaa5b0) for process 0 (type 0002)
[P04529] walk_thread_list(callback=0xbaddfbe)
[P04529] allocated pid: 1
[P04529] bkeep_unmapped: 0xba6d000-0xba72000 => slab
[     1] mounting as chroot filesystem: from file:../../../../Runtime to /lib
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 864
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 864
enclave_ocalls.c: Copied 864 byte from 0x7ffe1cfa1a35 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 864
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 0
enclave_ocalls.c: Copied 0 byte from 0x7ffe1cfa1a37 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 864
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 864
enclave_ocalls.c: Copied 864 byte from 0x7ffe1cfa1a35 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 864
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 0
enclave_ocalls.c: Copied 0 byte from 0x7ffe1cfa1a37 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] mounting as chroot filesystem: from file:/bin to /bin
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7ffe1cfa1a34 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7ffe1cfa1a34 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7ffe1cfa1a34 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7ffe1cfa1a34 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 880
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 880
enclave_ocalls.c: Copied 880 byte from 0x7ffe1cfa1a35 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 880
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 0
enclave_ocalls.c: Copied 0 byte from 0x7ffe1cfa1a37 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_unmapped: 0xba66000-0xba69000 => slab
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba66000-0xba69000
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7ffe1cfa1a34 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7ffe1cfa1a34 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7ffe1cfa1a34 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7ffe1cfa1a34 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 880
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 880
enclave_ocalls.c: Copied 880 byte from 0x7ffe1cfa1a35 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 880
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 0
enclave_ocalls.c: Copied 0 byte from 0x7ffe1cfa1a37 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_unmapped: 0xba66000-0xba69000 => slab
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba66000-0xba69000
[     1] mounting as chroot filesystem: from file:/home/user to /home/user
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xffe4c90
db_files.c: ocall_getdents(fd, 0xffe4c90, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 472
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 472
enclave_ocalls.c: Copied 472 byte from 0x7ffe1cfa1a35 to 0xffe4c90
db_files.c: ocall_getdents(fd, 0xffe4c90, 1024) = 472
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 0
enclave_ocalls.c: Copied 0 byte from 0x7ffe1cfa1a37 to 0xffe4c90
db_files.c: ocall_getdents(fd, 0xffe4c90, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 472
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 472
enclave_ocalls.c: Copied 472 byte from 0x7ffe1cfa1a35 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 472
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 0
enclave_ocalls.c: Copied 0 byte from 0x7ffe1cfa1a37 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_unmapped: 0xaa35000-0xae36000 => stack
[     1] heap top adjusted to 0xaa35000
[     1] bkeep_mprotect: 0xaa36000-0xae36000
[     1] allocated stack at 0xaa36000 (size = 4194304)
[     1] adding file:readdir as runtime object loaded at 0x400000-0x602000
[     1] bkeep_mmap: 0x400000-0x401000
[     1] bkeep_mmap: 0x600000-0x602000
[     1] bkeep_mmap: 0x1b45000-0x3b45000
[     1] brk area: 0x1b45000 - 0x1b46000
[     1] brk reserved area: 0x1b46000 - 0x3b45000
[     1] bkeep_mmap: 0x1b45000-0x1b46000
[     1] search interpreter: /lib/ld-linux-x86-64.so.2
[     1] bkeep_unmapped: 0xba69000-0xba6d000 => filebuf
[     1] bkeep_unmapped: 0xa812000-0xaa35000
[     1] heap top adjusted to 0xa812000
[     1] bkeep_mprotect: 0xa833000-0xaa32000
[     1] bkeep_mmap: 0xaa32000-0xaa34000
[     1] bkeep_mmap: 0xaa34000-0xaa35000
[     1] shim process initialized
[     1] ---- shim_brk(0x0) = 0x01b45000
[     1] ---- shim_uname(0xae35304) = 0
[P04529] set tcb to 0xffd9e30
[     1] ---- shim_mmap(0x0,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[P04529] ipc helper thread started
[     1] bkeep_unmapped: 0xa811000-0xa812000
[     1] heap top adjusted to 0xa811000
[     1] ---- return from shim_mmap(...) = 0x0a811000
[P04529] bkeep_unmapped: 0xba64000-0xba69000 => slab
[     1] ---- shim_open("/lib/tls/libc.so.6",O_RDONLY|2000000,1250640560) ... open
[P04529] bkeep_mprotect: 0xba65000-0xba69000
[P04529] allocated stack at 0xba65000 (size = 16384)
[     1] ---- return from shim_open(...) = -2
[P04529] listen to process 0 on port 0xba720c0 (handle 0xbfaa5b0, type 0002)
[     1] ---- shim_stat("/lib/tls",0xae34d5a) = -2
[P04529] listen to process 0 on port 0xba72048 (handle 0xbfa9db0, type 0001)
[     1] ---- shim_open("/lib/libc.so.6",O_RDONLY|2000000,1250640560) ... open
[     1] ---- return from shim_open(...) = 3
[     1] ---- shim_read(3,0xae34eaa,832) ... read
[     1] bkeep_unmapped: 0xba60000-0xba64000 => filebuf
[     1] ---- return from shim_read(...) = 832
[     1] ---- shim_fstat(3,0xae34d5a) = 0
[     1] ---- shim_mmap(0x0,3852760,PROT_READ|PROT_EXEC,MAP_PRIVATE|0x800,3,0) ... mmap
[     1] bkeep_unmapped: 0xa464000-0xa811000
[     1] heap top adjusted to 0xa464000
[     1] ---- return from shim_mmap(...) = 0x0a464000
[     1] ---- shim_mprotect(0xa608000,2093056,PROT_NONE) ... mprotect
[     1] bkeep_mprotect: 0xa608000-0xa807000
[     1] ---- return from shim_mprotect(...) = 0
[     1] ---- shim_mmap(0xa807000,24576,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_FIXED|0x800,3,1716224) ... mmap
[     1] mmap: allowing overlapping MAP_FIXED allocation at 0xa807000 with length 24576
[     1] bkeep_mmap: 0xa807000-0xa80d000
[     1] ---- return from shim_mmap(...) = 0x0a807000
[     1] ---- shim_mmap(0xa80d000,14808,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON|MAP_FIXED,-1,0) ... mmap
[     1] mmap: allowing overlapping MAP_FIXED allocation at 0xa80d000 with length 16384
[     1] bkeep_mmap: 0xa80d000-0xa811000
[     1] ---- return from shim_mmap(...) = 0x0a80d000
[     1] bkeep_munmap: 0xba60000-0xba64000
[     1] ---- shim_close(3) = 0
[     1] glibc register library /lib/libc.so.6 loaded at 0x0a464000
[     1] ---- shim_mmap(0x0,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[     1] bkeep_unmapped: 0xa463000-0xa464000
[     1] heap top adjusted to 0xa463000
[     1] ---- return from shim_mmap(...) = 0x0a463000
[     1] ---- shim_mmap(0x0,8192,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[     1] bkeep_unmapped: 0xa461000-0xa463000
[     1] heap top adjusted to 0xa461000
[     1] ---- return from shim_mmap(...) = 0x0a461000
[     1] set tcb to 0xa461700
[     1] ---- shim_arch_prctl(4098,0xa461700) = 0x00000000
[     1] ---- shim_mprotect(0xa807000,16384,PROT_READ) ... mprotect
[     1] bkeep_mprotect: 0xa807000-0xa80b000
[     1] ---- return from shim_mprotect(...) = 0
[     1] ---- shim_mprotect(0x600000,4096,PROT_READ) ... mprotect
[     1] bkeep_mprotect: 0x600000-0x601000
[     1] ---- return from shim_mprotect(...) = 0
[     1] ---- shim_mprotect(0xaa32000,4096,PROT_READ) ... mprotect
[     1] bkeep_mprotect: 0xaa32000-0xaa33000
[     1] ---- return from shim_mprotect(...) = 0
[     1] bkeep_unmapped: 0xba62000-0xba64000 => slab
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7ffe1cfa1a34 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7ffe1cfa1a34 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7ffe1cfa1a34 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7ffe1cfa1a34 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 992
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 992
enclave_ocalls.c: Copied 992 byte from 0x7ffe1cfa1a35 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 992
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7ffe1cfa1a34 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 632
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 632
enclave_ocalls.c: Copied 632 byte from 0x7ffe1cfa1a35 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 632
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 0
enclave_ocalls.c: Copied 0 byte from 0x7ffe1cfa1a37 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 0
[     1] bkeep_unmapped: 0xba60000-0xba62000 => slab
[     1] bkeep_unmapped: 0xba5d000-0xba60000 => slab
[     1] bkeep_munmap: 0xba60000-0xba62000
[     1] bkeep_unmapped: 0xba58000-0xba5d000 => slab
[     1] bkeep_munmap: 0xba5d000-0xba60000
[     1] bkeep_munmap: 0xba62000-0xba64000
[     1] bkeep_munmap: 0xba58000-0xba5d000
[     1] ---- shim_openat(AT_FDCWD,".",O_RDONLY|2204000,0000) = 3
[     1] ---- shim_fcntl(3,F_GETFD,0x0) = 1
[     1] ---- shim_brk(0x0) = 0x01b45000
[     1] brk area: 0x1b45000 - 0x1b6e000
[     1] brk reserved area: 0x1b6e000 - 0x3b45000
[     1] bkeep_mmap: 0x1b45000-0x1b6e000
[     1] ---- shim_brk(0x1b6e000) = 0x01b6e000
[     1] bkeep_unmapped: 0xba62000-0xba64000 => slab
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7ffe1cfa1a34 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7ffe1cfa1a34 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7ffe1cfa1a34 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7ffe1cfa1a34 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 992
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 992
enclave_ocalls.c: Copied 992 byte from 0x7ffe1cfa1a35 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 992
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7ffe1cfa1a34 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7ffe1cfa1a34 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 632
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 632
enclave_ocalls.c: Copied 632 byte from 0x7ffe1cfa1a35 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 632
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 0
enclave_ocalls.c: Copied 0 byte from 0x7ffe1cfa1a37 to 0xae34cd0
db_files.c: ocall_getdents(fd, 0xae34cd0, 1024) = 0
[     1] bkeep_unmapped: 0xba60000-0xba62000 => slab
[     1] bkeep_unmapped: 0xba5d000-0xba60000 => slab
[     1] bkeep_munmap: 0xba60000-0xba62000
[     1] bkeep_unmapped: 0xba58000-0xba5d000 => slab
[     1] bkeep_munmap: 0xba5d000-0xba60000
[     1] bkeep_munmap: 0xba62000-0xba64000
[     1] bkeep_unmapped: 0xba62000-0xba64000 => slab
[     1] bkeep_unmapped: 0xba5f000-0xba62000 => slab
[     1] bkeep_unmapped: 0xba53000-0xba58000 => slab
[     1] bkeep_unmapped: 0xba4e000-0xba53000 => slab
[     1] bkeep_unmapped: 0xba5d000-0xba5f000 => slab
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 72
sgx_enclave.c: Will fault the next 0-byte read!
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 72
enclave_ocalls.c: Copied 72 byte from 0x7ffe1cfa1a36 to 0xae34b30
db_files.c: ocall_getdents(fd, 0xae34b30, 1024) = 72
sgx_enclave.c: getdents64(fs, 0x7ffe1cfa1668, 1024) = 0
sgx_enclave.c: Faulting this ocall!
enclave_ocalls.c: ocall_getdents(0x7ffe1cfa1a68) = 2048
enclave_ocalls.c: Copied 2048 byte from 0x7ffe1cfa1a34 to 0xae34b30
db_files.c: ocall_getdents(fd, 0x40000007ffe, 1024) = 2048
[     1] memory fault at 0x00000000 (IP = 0x0bd8143b)
[     1] signal_logs[10]: head=0, tail=1 (counter = 1)
[     1] memory fault at 0x00000000 (IP = 0x0bd8143b)
```

## Sample output (normal operation not under attack)

```
[P13362] set tcb to 0xffe9938
[P13362] host: Linux-SGX
[P13362] initial random value: 4cd64bb4d89a294a
[P13362] bkeep_unmapped: 0xba9b000-0xba9d000 => vma
[P13362] allocate 0xba9b000-0xba9d000 for vmas
[P13362] Converting early VMA [0xbd72060] 0x400000-0x602000
[P13362] Converting early VMA [0xbd720a8] 0xffff000-0xffff764
[P13362] Converting early VMA [0xbd720f0] 0xba9b000-0xba9d000
[P13362] heap top adjusted to 0x9020000
[P13362] bkeep_unmapped: 0xba8a000-0xba9b000 => slab
[P13362] bkeep_unmapped: 0xba87000-0xba8a000 => slab
[P13362] bkeep_unmapped: 0xba83000-0xba87000 => slab
[P13362] bkeep_unmapped: 0xba7e000-0xba83000 => slab
[P13362] bkeep_unmapped: 0xba77000-0xba7e000 => slab
[P13362] shim loaded at 0xba9e000, ready to initialize
[P13362] bkeep_unmapped: 0xba76000-0xba77000 => slab
[P13362] bkeep_unmapped: 0xba74000-0xba76000 => slab
[P13362] mounting default root filesystem
[P13362] bkeep_unmapped: 0xba72000-0xba74000 => slab
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7fff711766e4 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7fff711766e4 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7fff711766e4 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7fff711766e4 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 992
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 992
enclave_ocalls.c: Copied 992 byte from 0x7fff711766e5 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 992
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7fff711766e4 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 632
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 632
enclave_ocalls.c: Copied 632 byte from 0x7fff711766e5 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 632
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 0
enclave_ocalls.c: Copied 0 byte from 0x7fff711766e7 to 0xffe6f10
db_files.c: ocall_getdents(fd, 0xffe6f10, 1024) = 0
[P13362] bkeep_unmapped: 0xba70000-0xba72000 => slab
[P13362] bkeep_unmapped: 0xba6d000-0xba70000 => slab
[P13362] bkeep_munmap: 0xba70000-0xba72000
[P13362] bkeep_unmapped: 0xba68000-0xba6d000 => slab
[P13362] bkeep_munmap: 0xba6d000-0xba70000
[P13362] bkeep_munmap: 0xba72000-0xba74000
[P13362] bkeep_munmap: 0xba68000-0xba6d000
[P13362] mounting as proc filesystem: /proc
[P13362] mounting as dev filesystem: /dev
[P13362] mounting as chroot filesystem: from dev:tty to /dev
[P13362] bkeep_unmapped: 0xba73000-0xba74000 => slab
[P13362] bkeep_unmapped: 0xba72000-0xba73000 => slab
[P13362] adding port (handle 0xbfa9db0) for process 0 (type 0001)
[P13362] creating pipe: pipe.srv:1881365221
[P13362] adding port (handle 0xbfaa5b0) for process 0 (type 0002)
[P13362] walk_thread_list(callback=0xbaddfbe)
[P13362] allocated pid: 1
[P13362] bkeep_unmapped: 0xba6d000-0xba72000 => slab
[     1] mounting as chroot filesystem: from file:../../../../Runtime to /lib
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 864
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 864
enclave_ocalls.c: Copied 864 byte from 0x7fff711766e5 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 864
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 0
enclave_ocalls.c: Copied 0 byte from 0x7fff711766e7 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 864
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 864
enclave_ocalls.c: Copied 864 byte from 0x7fff711766e5 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 864
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 0
enclave_ocalls.c: Copied 0 byte from 0x7fff711766e7 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] mounting as chroot filesystem: from file:/bin to /bin
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7fff711766e4 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7fff711766e4 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7fff711766e4 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7fff711766e4 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 880
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 880
enclave_ocalls.c: Copied 880 byte from 0x7fff711766e5 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 880
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 0
enclave_ocalls.c: Copied 0 byte from 0x7fff711766e7 to 0xffe4d80
db_files.c: ocall_getdents(fd, 0xffe4d80, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_unmapped: 0xba66000-0xba69000 => slab
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba66000-0xba69000
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7fff711766e4 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7fff711766e4 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7fff711766e4 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7fff711766e4 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 880
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 880
enclave_ocalls.c: Copied 880 byte from 0x7fff711766e5 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 880
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 0
enclave_ocalls.c: Copied 0 byte from 0x7fff711766e7 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_unmapped: 0xba66000-0xba69000 => slab
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba66000-0xba69000
[     1] mounting as chroot filesystem: from file:/home/user to /home/user
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0xffe4c90
db_files.c: ocall_getdents(fd, 0xffe4c90, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 472
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 472
enclave_ocalls.c: Copied 472 byte from 0x7fff711766e5 to 0xffe4c90
db_files.c: ocall_getdents(fd, 0xffe4c90, 1024) = 472
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 0
enclave_ocalls.c: Copied 0 byte from 0x7fff711766e7 to 0xffe4c90
db_files.c: ocall_getdents(fd, 0xffe4c90, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 472
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 472
enclave_ocalls.c: Copied 472 byte from 0x7fff711766e5 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 472
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 0
enclave_ocalls.c: Copied 0 byte from 0x7fff711766e7 to 0xffe4e90
db_files.c: ocall_getdents(fd, 0xffe4e90, 1024) = 0
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_unmapped: 0x8c1f000-0x9020000 => stack
[     1] heap top adjusted to 0x8c1f000
[     1] bkeep_mprotect: 0x8c20000-0x9020000
[     1] allocated stack at 0x8c20000 (size = 4194304)
[     1] adding file:readdir as runtime object loaded at 0x400000-0x602000
[     1] bkeep_mmap: 0x400000-0x401000
[     1] bkeep_mmap: 0x600000-0x602000
[     1] bkeep_mmap: 0x2109000-0x4109000
[     1] brk area: 0x2109000 - 0x210a000
[     1] brk reserved area: 0x210a000 - 0x4109000
[     1] bkeep_mmap: 0x2109000-0x210a000
[     1] search interpreter: /lib/ld-linux-x86-64.so.2
[     1] bkeep_unmapped: 0xba69000-0xba6d000 => filebuf
[     1] bkeep_unmapped: 0x89fc000-0x8c1f000
[     1] heap top adjusted to 0x89fc000
[     1] bkeep_mprotect: 0x8a1d000-0x8c1c000
[     1] bkeep_mmap: 0x8c1c000-0x8c1e000
[     1] bkeep_mmap: 0x8c1e000-0x8c1f000
[     1] shim process initialized
[     1] ---- shim_brk(0x0) = 0x02109000
[     1] ---- shim_uname(0x901f304) = 0
[     1] ---- shim_mmap(0x0,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[     1] bkeep_unmapped: 0x89fb000-0x89fc000
[     1] heap top adjusted to 0x89fb000
[P13362] set tcb to 0xffd9e30
[     1] ---- return from shim_mmap(...) = 0x089fb000
[P13362] ipc helper thread started
[P13362] bkeep_unmapped: 0xba64000-0xba69000 => slab
[     1] ---- shim_open("/lib/tls/libc.so.6",O_RDONLY|2000000,1060360560) ... open
[P13362] bkeep_mprotect: 0xba65000-0xba69000
[P13362] allocated stack at 0xba65000 (size = 16384)
[P13362] listen to process 0 on port 0xba720c0 (handle 0xbfaa5b0, type 0002)
[     1] ---- return from shim_open(...) = -2
[P13362] listen to process 0 on port 0xba72048 (handle 0xbfa9db0, type 0001)
[     1] ---- shim_stat("/lib/tls",0x901ed5a) = -2
[     1] ---- shim_open("/lib/libc.so.6",O_RDONLY|2000000,1060360560) ... open
[     1] ---- return from shim_open(...) = 3
[     1] ---- shim_read(3,0x901eeaa,832) ... read
[     1] bkeep_unmapped: 0xba60000-0xba64000 => filebuf
[     1] ---- return from shim_read(...) = 832
[     1] ---- shim_fstat(3,0x901ed5a) = 0
[     1] ---- shim_mmap(0x0,3852760,PROT_READ|PROT_EXEC,MAP_PRIVATE|0x800,3,0) ... mmap
[     1] bkeep_unmapped: 0x864e000-0x89fb000
[     1] heap top adjusted to 0x864e000
[     1] ---- return from shim_mmap(...) = 0x0864e000
[     1] ---- shim_mprotect(0x87f2000,2093056,PROT_NONE) ... mprotect
[     1] bkeep_mprotect: 0x87f2000-0x89f1000
[     1] ---- return from shim_mprotect(...) = 0
[     1] ---- shim_mmap(0x89f1000,24576,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_FIXED|0x800,3,1716224) ... mmap
[     1] mmap: allowing overlapping MAP_FIXED allocation at 0x89f1000 with length 24576
[     1] bkeep_mmap: 0x89f1000-0x89f7000
[     1] ---- return from shim_mmap(...) = 0x089f1000
[     1] ---- shim_mmap(0x89f7000,14808,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON|MAP_FIXED,-1,0) ... mmap
[     1] mmap: allowing overlapping MAP_FIXED allocation at 0x89f7000 with length 16384
[     1] bkeep_mmap: 0x89f7000-0x89fb000
[     1] ---- return from shim_mmap(...) = 0x089f7000
[     1] bkeep_munmap: 0xba60000-0xba64000
[     1] ---- shim_close(3) = 0
[     1] glibc register library /lib/libc.so.6 loaded at 0x0864e000
[     1] ---- shim_mmap(0x0,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[     1] bkeep_unmapped: 0x864d000-0x864e000
[     1] heap top adjusted to 0x864d000
[     1] ---- return from shim_mmap(...) = 0x0864d000
[     1] ---- shim_mmap(0x0,8192,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[     1] bkeep_unmapped: 0x864b000-0x864d000
[     1] heap top adjusted to 0x864b000
[     1] ---- return from shim_mmap(...) = 0x0864b000
[     1] set tcb to 0x864b700
[     1] ---- shim_arch_prctl(4098,0x864b700) = 0x00000000
[     1] ---- shim_mprotect(0x89f1000,16384,PROT_READ) ... mprotect
[     1] bkeep_mprotect: 0x89f1000-0x89f5000
[     1] ---- return from shim_mprotect(...) = 0
[     1] ---- shim_mprotect(0x600000,4096,PROT_READ) ... mprotect
[     1] bkeep_mprotect: 0x600000-0x601000
[     1] ---- return from shim_mprotect(...) = 0
[     1] ---- shim_mprotect(0x8c1c000,4096,PROT_READ) ... mprotect
[     1] bkeep_mprotect: 0x8c1c000-0x8c1d000
[     1] ---- return from shim_mprotect(...) = 0
[     1] bkeep_unmapped: 0xba62000-0xba64000 => slab
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7fff711766e4 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7fff711766e4 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7fff711766e4 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7fff711766e4 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 992
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 992
enclave_ocalls.c: Copied 992 byte from 0x7fff711766e5 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 992
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7fff711766e4 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 632
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 632
enclave_ocalls.c: Copied 632 byte from 0x7fff711766e5 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 632
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 0
enclave_ocalls.c: Copied 0 byte from 0x7fff711766e7 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 0
[     1] bkeep_unmapped: 0xba60000-0xba62000 => slab
[     1] bkeep_unmapped: 0xba5d000-0xba60000 => slab
[     1] bkeep_munmap: 0xba60000-0xba62000
[     1] bkeep_unmapped: 0xba58000-0xba5d000 => slab
[     1] bkeep_munmap: 0xba5d000-0xba60000
[     1] bkeep_munmap: 0xba62000-0xba64000
[     1] bkeep_munmap: 0xba58000-0xba5d000
[     1] ---- shim_openat(AT_FDCWD,".",O_RDONLY|2204000,0000) = 3
[     1] ---- shim_fcntl(3,F_GETFD,0x0) = 1
[     1] ---- shim_brk(0x0) = 0x02109000
[     1] brk area: 0x2109000 - 0x2132000
[     1] brk reserved area: 0x2132000 - 0x4109000
[     1] bkeep_mmap: 0x2109000-0x2132000
[     1] ---- shim_brk(0x2132000) = 0x02132000
[     1] bkeep_unmapped: 0xba62000-0xba64000 => slab
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1016
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1016
enclave_ocalls.c: Copied 1016 byte from 0x7fff711766e4 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 1016
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7fff711766e4 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7fff711766e4 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1008
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1008
enclave_ocalls.c: Copied 1008 byte from 0x7fff711766e4 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 1008
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 992
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 992
enclave_ocalls.c: Copied 992 byte from 0x7fff711766e5 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 992
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1024
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1024
enclave_ocalls.c: Copied 1024 byte from 0x7fff711766e4 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 1024
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 1000
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 1000
enclave_ocalls.c: Copied 1000 byte from 0x7fff711766e4 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 1000
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 632
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 632
enclave_ocalls.c: Copied 632 byte from 0x7fff711766e5 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 632
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 0
enclave_ocalls.c: Copied 0 byte from 0x7fff711766e7 to 0x901ecd0
db_files.c: ocall_getdents(fd, 0x901ecd0, 1024) = 0
[     1] bkeep_unmapped: 0xba60000-0xba62000 => slab
[     1] bkeep_unmapped: 0xba5d000-0xba60000 => slab
[     1] bkeep_munmap: 0xba60000-0xba62000
[     1] bkeep_unmapped: 0xba58000-0xba5d000 => slab
[     1] bkeep_munmap: 0xba5d000-0xba60000
[     1] bkeep_munmap: 0xba62000-0xba64000
[     1] bkeep_unmapped: 0xba62000-0xba64000 => slab
[     1] bkeep_unmapped: 0xba5f000-0xba62000 => slab
[     1] bkeep_unmapped: 0xba53000-0xba58000 => slab
[     1] bkeep_unmapped: 0xba4e000-0xba53000 => slab
[     1] bkeep_unmapped: 0xba5d000-0xba5f000 => slab
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 72
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 72
enclave_ocalls.c: Copied 72 byte from 0x7fff711766e6 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 72
sgx_enclave.c: getdents64(fs, 0x7fff71176318, 1024) = 0
enclave_ocalls.c: ocall_getdents(0x7fff71176718) = 0
enclave_ocalls.c: Copied 0 byte from 0x7fff711766e7 to 0x901eb30
db_files.c: ocall_getdents(fd, 0x901eb30, 1024) = 0
[     1] bkeep_unmapped: 0xba4c000-0xba4e000 => slab
[     1] bkeep_munmap: 0xba5d000-0xba5f000
[     1] bkeep_munmap: 0xba4c000-0xba4e000
[     1] bkeep_unmapped: 0xba45000-0xba4e000 => slab
[     1] bkeep_unmapped: 0xba40000-0xba45000 => slab
[     1] bkeep_unmapped: 0xba3b000-0xba40000 => slab
[     1] bkeep_unmapped: 0xba2a000-0xba3b000 => slab
[     1] bkeep_munmap: 0xba58000-0xba5d000
[     1] bkeep_unmapped: 0xba5e000-0xba5f000 => slab
[     1] ---- shim_getdents(3,0x2109040,32768) = 11791
[     1] ---- shim_fstat(1,0x901edc0) = 0
[     1] ---- shim_ioctl(1,TCGETS,0x901ed30) ... ioctl
[     1] ---- return from shim_ioctl(...) = -22
[     1] ---- shim_mmap(0x0,8192,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[     1] bkeep_unmapped: 0x8649000-0x864b000
[     1] heap top adjusted to 0x8649000
[     1] ---- return from shim_mmap(...) = 0x08649000
[     1] ---- shim_getdents(3,0x2109040,32768) = 0
[     1] ---- shim_brk(0x212a000) = 0x0212a000
[     1] ---- shim_close(3) = 0
[     1] ---- shim_write(1,0x8649000,5860) ... write
found .
found sleep.sig
found cpuinfo.token
found msg_send
found epoll_socket.token
found pid_alloc.c
found rename.c
found helloworld.pthread.token
found file.sig
found script3.sh
found Makefile
found pie.manifest.sgx
found static.manifest.template
found multisleep.sig
found ls.sig
found kill.c
found msg_send.token
found futextest.pthread.token
found test_start_pthread_m.m.c
found sqrt.m.sig
found dup
found epoll
found msg_create.libos
found pipe.sig
found msg_create.sig
found readdir.manifest.sgx
found tcp.token
found sem
found msg_create.libos.manifest.sgx
found pal_loader
found vfork
found dup.sig
found manifest.template
found sqrt.m.c
found pipe_latency
found rename.token
found sleep.c
found kill
found static.token
found pid_kill
found get_time.m
found fork_exec
found static
found dup.c
found script.token
found epoll_socket.sig
found meminfo.token
found file.manifest.sgx
found vfork_exec
found proc.c
found sync.pthread.c
found helloworld.pthread.manifest.sgx
found script1.sh
found pid_alloc.sig
found futextest.pthread.sig
found sandbox_create.libos.token
found divzero.manifest.sgx
found exec_fork
found errno.token
found errno.sig
found epoll.sig
found sem.sig
found proc.token
found pipe
found proc.sig
found ls.manifest.template
found exec_fork.manifest.sgx
found testdir
found fork_exec.sig
found multiproc.manifest.sgx
found pid_alloc
found msg_create.c
found malloc
found vfork_exec.manifest.sgx
found malloc.manifest.sgx
found pid_kill.c
found pipe.manifest.sgx
found alarm.token
found msg_create.libos.sig
found fork
found helloworld
found sync.pthread.token
found fork_exec.manifest.sgx
found helloworld.token
found time.token
found socketpair.token
found pipe_latency.sig
found sleep.manifest.sgx
found file
found system.manifest.sgx
found script
found sync.pthread.sig
found unix.sig
found pipe_latency.manifest.sgx
found pid_kill.sig
found ls.manifest.sgx
found fork.token
found sync.pthread
found cpuinfo
found futextest.pthread.manifest.sgx
found unix.c
found time.c
found dir.manifest.sgx
found system.c
found .gitignore
found test.open.file
found multisleep
found sandbox_create.libos
found vfork.token
found tcp.sig
found rename.sig
found alarm.sig
found helloworld.pthread.c
found pid_kill.token
found start.pthread.m.token
found condvar.pthread.token
found msg_send.libos.token
found static.manifest
found multiproc.c
found ls.manifest
found get_time.m.c
found msg_send.libos.c
found malloc.sig
found unix
found readdir.c
found sem.c
found multisleep.c
found helloworld.c
found condvar.pthread
found sem.token
found epoll.c
found clone
found divzero.sig
found meminfo
found meminfo.manifest.sgx
found fs.token
found malloc.token
found multisleep.token
found start.pthread.m.sig
found helloworld.pthread.sig
found clone.sig
found script.c
found fork.manifest.sgx
found system
found multisleep.manifest.sgx
found brk
found fork_bomb.manifest.sgx
found pid_kill.manifest.sgx
found pie
found system.sig
found socketpair.manifest.sgx
found fork_exec.token
found readdir
found start.pthread.m
found epoll.manifest.sgx
found condvar.pthread.c
found vfork.manifest.sgx
found fork.sig
found multiproc.sig
found epoll_socket.c
found file.c
found testfile
found retval.txt
found errno
found futextest.pthread
found udp.sig
found test_start_pthread_m.m.sig
found fs.c
found file.token
found vfork.c
found udp
found get_time.m.sig
found msg_create.libos.c
found msg_create
found condvar.pthread.sig
found vfork_exec.token
found clone.manifest.sgx
found script.manifest.sgx
found multiproc
found tcp
found msg_send.c
found dup.manifest.sgx
found pie.token
found pipe_latency.token
found brk.sig
found errno.c
found rename.manifest.sgx
found script2.sh
found sqrt.m.manifest.sgx
found helloworld.manifest.sgx
found pie.c
found errno.manifest.sgx
found socketpair
found fs
found kill.manifest.sgx
found time.manifest.sgx
found sqrt.m
found epoll_socket.manifest.sgx
found sqrt.m.token
found brk.c
found msg_create.token
found socketpair.sig
found exec_fork.token
found dup.token
found alarm
found sync.pthread.manifest.sgx
found pipe.c
found pipe_latency.c
found fork_bomb.sig
found msg_create.manifest.sgx
found multiproc.token
found manifest
found divzero
found udp.token
found fork_bomb.token
found udp.c
found malloc.c
found fs.manifest.sgx
found fork_exec.c
found msg_send.libos.manifest.sgx
found kill.sig
found unix.token
found clone.token
found dir.sig
found get_time.m.token
found fork.c
found start.pthread.m.manifest.sgx
found alarm.manifest.sgx
found cpuinfo.sig
found time
found divzero.c
found pid_alloc.token
found fork_bomb.c
found tcp.c
found tcp.manifest.sgx
found epoll.token
found proc.manifest.sgx
found vfork_exec.c
found kill.token
found static.manifest.sgx
found pipe.token
found msg_send.libos.sig
found script.sig
found cpuinfo.manifest.sgx
found sandbox_create.libos.manifest.sgx
found sandbox_create.libos.sig
found readdir.sig
found test_start_pthread_m.m
found fork_bomb
found ls.token
found helloworld.sig
found vfork.sig
found udp.manifest.sgx
found test_start_pthread_m.m.token
found dir.token
found log.txt
found readdir.token
found system.token
found dir
found epoll_socket
found dir.c
found time.sig
found exec_fork.c
found futextest.pthread.c
found pid_alloc.manifest.sgx
found pie.sig
found sleep
found start.pthread.m.c
found static.c
found socketpair.c
found sandbox_create.libos.c
found meminfo.sig
found test_start_pthread_m.m.manifest.sgx
found meminfo.c
found condvar.pthread.manifest.sgx
found sem.manifest.sgx
found static.sig
found msg_send.manifest.sgx
found get_time.m.manifest.sgx
found sleep.token
found fs.sig
found helloworld.pthread
found msg_create.libos.token
found alarm.c
found divzero.token
found msg_send.sig
found brk.manifest.sgx
found exec_fork.sig
found vfork_exec.sig
found brk.token
found cpuinfo.c
found msg_send.libos
found rename
found clone.c
found unix.manifest.sgx
[     1] ---- return from shim_write(...) = 5860
[     1] ---- shim_exit_group (returning 0)
[     1] now kill other threads in the process
[     1] walk_thread_list(callback=0xbb2cb72)
[     1] now exit the process
[     1] ipc broadcast: IPC_CLD_EXIT(1, 1, 0)
[     1] found port 0xba720c0 (handle 0xbfaa5b0) for process 0 (type 0002)
[     1] found port 0xba72048 (handle 0xbfa9db0) for process 0 (type 0001)
[     1] parent not here, need to tell another process
[     1] ipc broadcast: IPC_CLD_EXIT(1, 1, 0)
[     1] found port 0xba720c0 (handle 0xbfaa5b0) for process 0 (type 0002)
[     1] found port 0xba72048 (handle 0xbfa9db0) for process 0 (type 0001)
[     1] this is the only thread 1
[     1] exiting ipc helper
[P13362] ipc helper thread terminated
[     1] deleting port 0xba720c0 (handle 0xbfaa5b0) for process 0
[     1] deleting port 0xba72048 (handle 0xbfa9db0) for process 0
[     1] process 13362 exited with status 0
user@bagger:~/graphene/LibOS/shim/test/native$
```
