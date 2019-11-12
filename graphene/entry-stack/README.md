We identified several security-critical vulnerabilities in Graphene's trusted runtime for SGX enclaves. It should be noted that the containing host application, including the unprotected Graphene runtime, is completely *untrusted* in the SGX attacker model.

This issue was tracked earlier via https://github.com/oscarlab/graphene/issues/28

## Vulnerabilities

As a general rule, the trusted intra-enclave runtime should properly check *all* arguments/return values passed from the untrusted runtime. This is currently not the case in at least the following places:

* `enclave_entry.S`: does not perform bounds checking on the provided index for the entry function lookup table. The untrusted runtime can overflow/underflow the ecall_table lookup by providing an out-of-bounds entry index in `%rdi`:

```assembly
.Lhandle_ecall:
    lea ecall_table(%rip), %rbx
    mov (%rbx,%rdi,8), %rbx
        ...
    call *%rbx
```

An attacker controlling the unprotected application can redirect control flow to non-entry functions by abusing intra-enclave function pointers. She could even jump to arbitrary in-enclave code by over/underflowing the ecall_table lookup to unprotected memory (or enclave memory that holds user input).

* `enclave_entry.S`: allows to "return" into an enclave thread that is not waiting for a previous ocall return. Untrusted runtime can simply provide the special return entry index in `%rdi`:

```assembly
    cmp $RETURN_FROM_OCALL, %rdi
    je .Lreturn_from_ocall
        ...
.Lreturn_from_ocall
    mov %gs:SGX_LAST_STACK, %rsp
        popfq
        ...
        ret
```

An attacker can abuse this to initialize the in-enclave stack pointer of a newly started thread with the value of the last ocall. The memory content at these locations determine register values, and ultimately control flow.

* `enclave_ecalls.c` contains an entry function `enclave_ecall_thread_start` that redirects control flow to a provided function address. The function pointer is not restricted in any way, allowing an attacker to jump to arbitrary code locations within the enclave. The attacker also has control over the first argument provided to the function.

## Proof-of-Concept Exploit

I included a proof-of-concept exploit at [https://github.com/jovanbulck/graphene](https://github.com/jovanbulck/graphene/blob/master/Pal/src/host/Linux-SGX/sgx_enclave.c#L739).

To demonstrate the danger of allowing arbitrary non-entry code execution, I wrote an elementary application that decides access to an `access_allowed` function by comparing a user-provided number with a secret PIN code.  After confirming the application has been loaded, the untrusted runtime abuses the ecall_table lookup in `enclave_entry.S` to call `access_allowed`, regardless of the provided PIN. This shows that an attacker can redirect control flow to arbitrary enclaved code, including the loaded application binary:

```
Hello world from enclaved application binary!
    --> ac.allowAccess at 0x601078 is 0x4007e1 (access_allowed_handler)
app: enter PIN..
> 1233
user entered 1233
app: checking acess..
===> app: access denied! <===
app: ocall: opening dummy_file

[urts] entering enclave with illegal ecall idx -24332361 (ecall_table_adrs=0xbfa52c0)
enclave_handle_ecall: asm stub passed function pointer:
[ocall_dump] 0x4007e1
===> app: access allowed! <===
destroying enclave...
```

I also included a proof-of-concept exploit that redirects control flow to an arbitrary non-entry function of the trusted runtime by abusing the argument of `enclave_ecall_thread_start`. It can easily be understood that this allows for code abuse attacks that could break the confidentiality/integrity of in-enclave data.

## Security Patches

It should be clear from the above explanation and the exploit that Graphene's trusted runtime should *restrict enclave entry to a few well-defined entry points*. I did not write a patch since it is not yet entirely clear what the best solution would be:

* `enclave_entry.S`: given the security-sensitive role of the entry assembly code, I suggest reducing it to the absolute minimum. After switching to the secure stack, a normal C function could be called to take care of the ecall/return from ocall. At this point, entry index bounds checking and illegal returns could be properly handled. This approach resembles the official SGX SDK, where an [enter_enclave](https://github.com/01org/linux-sgx/blob/master/sdk/trts/trts.cpp) C function is called from the [enclave_entry](https://github.com/01org/linux-sgx/blob/master/sdk/trts/linux/trts_pic.S) asm stub.

* `enclave_ecalls.c`: the current implementation of `thread_start` is fundamentally flawed. Entry code execution should be limited to predefined entry points. It is unclear to me how this fits in Graphene's untrusted runtime/glibc threading model (?)
