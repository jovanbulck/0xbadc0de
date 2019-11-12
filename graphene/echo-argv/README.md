## Sample output

```
------------------------------
attacker: enter enclave address, current arguments[1]=0x7ffc1d2b87b2 > 400688

attacker: replacing untrusted string pointer argv[1] with adrs 0x400688
------------------------------


[P09831] set tcb to 0xffe9928
[P09831] host: Linux-SGX
[P09831] initial random value: 437d1ec7dc9e5316
[P09831] bkeep_unmapped: 0xba9b000-0xba9d000 => vma
[P09831] allocate 0xba9b000-0xba9d000 for vmas
[P09831] Converting early VMA [0xbd72060] 0x400000-0x602000
[P09831] Converting early VMA [0xbd720a8] 0xffff000-0xffff704
[P09831] Converting early VMA [0xbd720f0] 0xba9b000-0xba9d000
[P09831] heap top adjusted to 0x249e000
[P09831] bkeep_unmapped: 0xba8a000-0xba9b000 => slab
[P09831] bkeep_unmapped: 0xba87000-0xba8a000 => slab
[P09831] bkeep_unmapped: 0xba83000-0xba87000 => slab
[P09831] bkeep_unmapped: 0xba7e000-0xba83000 => slab
[P09831] bkeep_unmapped: 0xba77000-0xba7e000 => slab
[P09831] shim loaded at 0xba9e000, ready to initialize
[P09831] bkeep_unmapped: 0xba76000-0xba77000 => slab
[P09831] bkeep_unmapped: 0xba74000-0xba76000 => slab
[P09831] mounting default root filesystem
[P09831] bkeep_unmapped: 0xba72000-0xba74000 => slab
[P09831] bkeep_unmapped: 0xba70000-0xba72000 => slab
[P09831] bkeep_unmapped: 0xba6d000-0xba70000 => slab
[P09831] bkeep_munmap: 0xba70000-0xba72000
[P09831] bkeep_unmapped: 0xba68000-0xba6d000 => slab
[P09831] bkeep_munmap: 0xba6d000-0xba70000
[P09831] bkeep_munmap: 0xba72000-0xba74000
[P09831] bkeep_munmap: 0xba68000-0xba6d000
[P09831] mounting as proc filesystem: /proc
[P09831] mounting as dev filesystem: /dev
[P09831] mounting as chroot filesystem: from dev:tty to /dev
[P09831] bkeep_unmapped: 0xba73000-0xba74000 => slab
[P09831] bkeep_unmapped: 0xba72000-0xba73000 => slab
[P09831] adding port (handle 0xbfa9cb0) for process 0 (type 0001)
[P09831] creating pipe: pipe.srv:771609638
[P09831] adding port (handle 0xbfaa4b0) for process 0 (type 0002)
[P09831] walk_thread_list(callback=0xbaddfbe)
[P09831] allocated pid: 1
[P09831] bkeep_unmapped: 0xba6d000-0xba72000 => slab
[     1] mounting as chroot filesystem: from file:../../../../Runtime to /lib
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] mounting as chroot filesystem: from file:/bin to /bin
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_unmapped: 0xba66000-0xba69000 => slab
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba66000-0xba69000
[     1] bkeep_unmapped: 0xba6b000-0xba6d000 => slab
[     1] bkeep_unmapped: 0xba69000-0xba6b000 => slab
[     1] bkeep_unmapped: 0xba66000-0xba69000 => slab
[     1] bkeep_munmap: 0xba69000-0xba6b000
[     1] bkeep_munmap: 0xba6b000-0xba6d000
[     1] bkeep_munmap: 0xba66000-0xba69000
[     1] bkeep_unmapped: 0x209d000-0x249e000 => stack
[     1] heap top adjusted to 0x209d000
[     1] bkeep_mprotect: 0x209e000-0x249e000
[     1] allocated stack at 0x209e000 (size = 4194304)
[     1] adding file:helloworld as runtime object loaded at 0x400000-0x602000
[     1] bkeep_mmap: 0x400000-0x401000
[     1] bkeep_mmap: 0x600000-0x602000
[     1] bkeep_mmap: 0x2f08000-0x4f08000
[     1] brk area: 0x2f08000 - 0x2f09000
[     1] brk reserved area: 0x2f09000 - 0x4f08000
[     1] bkeep_mmap: 0x2f08000-0x2f09000
[     1] search interpreter: /lib/ld-linux-x86-64.so.2
[     1] bkeep_unmapped: 0xba69000-0xba6d000 => filebuf
[     1] bkeep_unmapped: 0x1e7a000-0x209d000
[     1] heap top adjusted to 0x1e7a000
[     1] bkeep_mprotect: 0x1e9b000-0x209a000
[     1] bkeep_mmap: 0x209a000-0x209c000
[     1] bkeep_mmap: 0x209c000-0x209d000
[     1] shim process initialized
[     1] ---- shim_brk(0x0) = 0x02f08000
[     1] ---- shim_uname(0x249d2d3) = 0
[     1] ---- shim_mmap(0x0,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[     1] bkeep_unmapped: 0x1e79000-0x1e7a000
[     1] heap top adjusted to 0x1e79000
[P09831] set tcb to 0xffd9e30
[P09831] ipc helper thread started
[     1] ---- return from shim_mmap(...) = 0x01e79000
[P09831] bkeep_unmapped: 0xba64000-0xba69000 => slab
[     1] ---- shim_open("/lib/tls/libc.so.6",O_RDONLY|2000000,202340560) ... open
[P09831] bkeep_mprotect: 0xba65000-0xba69000
[P09831] allocated stack at 0xba65000 (size = 16384)
[P09831] listen to process 0 on port 0xba720c0 (handle 0xbfaa4b0, type 0002)
[     1] ---- return from shim_open(...) = -2
[P09831] listen to process 0 on port 0xba72048 (handle 0xbfa9cb0, type 0001)
[     1] ---- shim_stat("/lib/tls",0x249cd29) = -2
[     1] ---- shim_open("/lib/libc.so.6",O_RDONLY|2000000,202340560) ... open
[     1] ---- return from shim_open(...) = 3
[     1] ---- shim_read(3,0x249ce79,832) ... read
[     1] bkeep_unmapped: 0xba60000-0xba64000 => filebuf
[     1] ---- return from shim_read(...) = 832
[     1] ---- shim_fstat(3,0x249cd29) = 0
[     1] ---- shim_mmap(0x0,3852760,PROT_READ|PROT_EXEC,MAP_PRIVATE|0x800,3,0) ... mmap
[     1] bkeep_unmapped: 0x1acc000-0x1e79000
[     1] heap top adjusted to 0x1acc000
[     1] ---- return from shim_mmap(...) = 0x01acc000
[     1] ---- shim_mprotect(0x1c70000,2093056,PROT_NONE) ... mprotect
[     1] bkeep_mprotect: 0x1c70000-0x1e6f000
[     1] ---- return from shim_mprotect(...) = 0
[     1] ---- shim_mmap(0x1e6f000,24576,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_FIXED|0x800,3,1716224) ... mmap
[     1] mmap: allowing overlapping MAP_FIXED allocation at 0x1e6f000 with length 24576
[     1] bkeep_mmap: 0x1e6f000-0x1e75000
[     1] ---- return from shim_mmap(...) = 0x01e6f000
[     1] ---- shim_mmap(0x1e75000,14808,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON|MAP_FIXED,-1,0) ... mmap
[     1] mmap: allowing overlapping MAP_FIXED allocation at 0x1e75000 with length 16384
[     1] bkeep_mmap: 0x1e75000-0x1e79000
[     1] ---- return from shim_mmap(...) = 0x01e75000
[     1] bkeep_munmap: 0xba60000-0xba64000
[     1] ---- shim_close(3) = 0
[     1] glibc register library /lib/libc.so.6 loaded at 0x01acc000
[     1] ---- shim_mmap(0x0,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[     1] bkeep_unmapped: 0x1acb000-0x1acc000
[     1] heap top adjusted to 0x1acb000
[     1] ---- return from shim_mmap(...) = 0x01acb000
[     1] ---- shim_mmap(0x0,8192,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[     1] bkeep_unmapped: 0x1ac9000-0x1acb000
[     1] heap top adjusted to 0x1ac9000
[     1] ---- return from shim_mmap(...) = 0x01ac9000
[     1] set tcb to 0x1ac9700
[     1] ---- shim_arch_prctl(4098,0x1ac9700) = 0x00000000
[     1] ---- shim_mprotect(0x1e6f000,16384,PROT_READ) ... mprotect
[     1] bkeep_mprotect: 0x1e6f000-0x1e73000
[     1] ---- return from shim_mprotect(...) = 0
[     1] ---- shim_mprotect(0x600000,4096,PROT_READ) ... mprotect
[     1] bkeep_mprotect: 0x600000-0x601000
[     1] ---- return from shim_mprotect(...) = 0
[     1] ---- shim_mprotect(0x209a000,4096,PROT_READ) ... mprotect
[     1] bkeep_mprotect: 0x209a000-0x209b000
[     1] ---- return from shim_mprotect(...) = 0
[     1] ---- shim_fstat(1,0x249d430) = 0
[     1] ---- shim_ioctl(1,TCGETS,0x249d3a0) ... ioctl
[     1] ---- return from shim_ioctl(...) = -22
[     1] ---- shim_mmap(0x0,8192,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0) ... mmap
[     1] bkeep_unmapped: 0x1ac7000-0x1ac9000
[     1] heap top adjusted to 0x1ac7000
[     1] ---- return from shim_mmap(...) = 0x01ac7000
[     1] ---- shim_write(1,0x1ac7000,247) ... write


Hello world from enclaved application binary!
        --> enclave secret at 0x400688


Echoing user-provided command line arguments
        argv[0] @0x249dff0 = 'file:helloworld'
        argv[1] @0x249dfd4 = 'super secret enclave string'
        argv[2] @0x249dfd0 = '123'
[     1] ---- return from shim_write(...) = 247
[     1] ---- shim_exit_group (returning 0)
[     1] now kill other threads in the process
[     1] walk_thread_list(callback=0xbb2cb72)
[     1] now exit the process
[     1] ipc broadcast: IPC_CLD_EXIT(1, 1, 0)
[     1] found port 0xba720c0 (handle 0xbfaa4b0) for process 0 (type 0002)
[     1] found port 0xba72048 (handle 0xbfa9cb0) for process 0 (type 0001)
[     1] parent not here, need to tell another process
[     1] ipc broadcast: IPC_CLD_EXIT(1, 1, 0)
[     1] found port 0xba720c0 (handle 0xbfaa4b0) for process 0 (type 0002)
[     1] found port 0xba72048 (handle 0xbfa9cb0) for process 0 (type 0001)
[     1] this is the only thread 1
[     1] exiting ipc helper
[P09831] ipc helper thread terminated
[     1] deleting port 0xba720c0 (handle 0xbfaa4b0) for process 0
[     1] deleting port 0xba72048 (handle 0xbfa9cb0) for process 0
[     1] process 9831 exited with status 0
```
