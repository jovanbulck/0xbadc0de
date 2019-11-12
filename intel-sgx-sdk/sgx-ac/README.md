# SGX-AC: Alignment fault enclave side-channel attacks

## Attack overview

We noticed that current enclave runtimes do _not_ sanitize x86's alignment check flag `RFLAGS.AC` on enclave entry. This opens up the possibility for an attacker to be notified for every unaligned memory access performed by the enclave (for a full list of "Alignment Requirements by Data Type", see Table 6-7. in Intel SDM Vol.3A). This novel side-channel vector compares closely to the well known `#PF` channel, but this time abuses `#AC` alignment-check exceptions. Importantly, we show that observing alignment faults for enclaved data accesses may sometimes offer an enhanced byte-granular precision, as compared to state-of-the-art 64B cacheline or 4KiB page table-based side-channel attacks.

We developed a minimal sample enclave to showcase how `#AC` exceptions can reveal fine-grained side-channel address information when dereferencing in-enclave pointers in both traditional secret-dependent control and data flow application scenarios. Note that one of the challenges we encountered, is to make the enclave progress after the first `#AC` exception (as the contents of `RFLAGS` is stored in private memory and cannot be changed when resuming the enclave). To overcome this challenge, we make use of the adversary's root privileges to load a simple kernel module `/dev/drv-am` to set and clear the processor's "alignment mask" (`CR0.AM`) on demand. Combined with a single-stepping attack primitive like [SGX-Step](https://github.com/jovanbulck/sgx-step), this approach allows to determine noise-free alignment side-channel info for _every_ single instruction in the enclave.

## Attack impact

In our current assessment, we do _not_ consider this attack technique immediately dangerous, i.e., address-related side-channel leakage falls outside of SGX's threat model as documented. We also think our proposed software patch (detailed below and enclosed in attach) is a very minimal and elegant solution to completely block the side-channel leakage.

Instead of merely opening a public PR on GitHub, we decided to reach out to Intel responsibly in this way. Please let us know if you still prefer us to open a public GitHub pull request for this issue. Given that we believe AC leakage to be a clear software issue, we also want to disclose this issue to other affected SGX runtimes (particularly Microsoft OpenEnclave, Fortanix-RustEDP, Graphene-SGX, SGX-LKL, etc.). We plan to send them this writeup over the course of the following days (unless hearing different from you).

## Proposed software-level defense

We propose to completely eliminate unintended side-channel leakage from `#AC` faults by changing the enclave's trusted runtime to always clear `RFLAGS.AC` after entering the enclave. We implemented this countermeasure for the latest Intel SGX-SDK (`linux-sgx v2.6`), and experimentally verified that it indeed blocks all leakage in our proof-of-concept attacks. The complete patch can be found in attach, and merely adds the following to the enclave entry code:

```
pushf
andl $~(0x40000),(%xsp)             /* eliminate #AC side-channel leakage */
popf
```

## Building and running

### 1. Build and load `/dev/drv-am`

The required driver module can be build and loaded for a stock Linux kernel as follows (tested on a recent `4.15.0-55-generic` kernel):

```
$ cd driver/
$ make load
```

### 2. Build and run proof-of-concept enclave code

Our proof-of-concept enclave code has been developed with the latest SGX-SDK `linux-sgx v2.6` and can be ran as follows:

```
$ cd sgx-ac-poc/
$ make run
```

## Sample output

For reference, expected output is as follows (as ran on a recent i7-8650U processor):

```
Opening /dev/drv-am ...
Creating enclave...
pinning to CPU 1...
registering SIGBUS handler..

--------------------------------------------------
RFLAGS.AC secret-dependent data flow
--------------------------------------------------

Running victim w input=0
---> OK
enclave lookup(0)=0x4241

Running victim w input=1
---> OK
enclave lookup(1)=0x4342

Running victim w input=0
---> OK
enclave lookup(0)=0x4241

Running victim w input=1
---> OK
enclave lookup(1)=0x4342

--------------------------------------------------
RFLAGS.AC secret-dependent control flow
--------------------------------------------------

Running victim w input=0
---> OK

Running victim w input=1
---> OK

Running victim w input=0
---> OK

Running victim w input=1
---> OK

all is well; exiting..
```
