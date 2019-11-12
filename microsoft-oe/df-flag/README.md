# Direction flag memory corruption in Open Enclave

We noticed that Open Enclave currently does _not_ sanitize x86's direction flag `RFLAGS.DF` on SGX enclave entry. This is problematic since trusted enclave code may now incorrectly assume that `RFLAGS.DF` is properly cleared on function entry, i.e., as mandated by the x86-64 sysv ABI and many others (see <https://www.agner.org/optimize/calling_conventions.pdf>). We indeed verified that for instance the commonly used gcc v5.4.0 compiler replaces a.o., `strlen()` and `memset()` with inlined x86 string instructions at optimization level `-Os` (only needed in the enclave Makefile). We show that by setting the direction flag in an unexpected "decrement" direction right before EENTER in the untrusted runtime, attackers can cause incorrect `strlen()` computations and memory corruption when overwriting unintended memory locations with `memset`. 

We have developed a minimal PoC to showcase such unexpected behaviors in the scenario of an unexpected `strlen()` result (which can easily lead to subsequent enclave memory corruptions). Note that there are many other potential cases (such as `memset()` or also oedger8r-generated code) where this issue might be exploitable as well.

Note that in the current version of Open Enclave (compiled on Ubuntu 16.04 with gcc v5.4.0), setting `RFLAGS.DF` will actually crash the trusted runtime on entry. This is because the following code:

 https://github.com/openenclave/openenclave/blob/master/enclave/core/sgx/calls.c#L344

compiles into a `rep` construct (with the default Makefile for OE), so effectively setting `RFLAGS.DF` here will overwrite a piece of _trusted runtime stack_ with zeroes, crashing the enclave. We have not investigated if this behaviour is further exploitable (it might be), but instead modified the respective code to use `memset()`, which (in this particular case) does not compile to `rep`, allowing the entry code to progress. We also note that the emitted assembly for code like `Callsite callsite = {{0}};` depends on compiler, version, and probably compiler flags. 

As a sidenote, we'd also like to remark that - if `RFLAGS.DF` is not cleared on enclave exit, this will yield a side channel leak for the direction of the last `rep` operation in the enclave.

Proposed software-level defense: We propose to completely eliminate attack surface from `RFLAGS.DF` by changing the enclave's trusted runtime to always clear this flag after entering and before exiting the enclave. 

Sample output: After applying the attached patch, running the modified helloworld sample will yield:

$ make run
host/helloworldhost ./enclave/helloworldenc.signed
ecall_strlen() with DF = 0 returned 1
ecall_strlen() with DF = 1 returned 3
