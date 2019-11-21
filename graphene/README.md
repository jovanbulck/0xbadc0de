# Graphene-SGX

The [Graphene project](https://grapheneproject.io/) offers an open-source
library OS which allows to run unmodified Linux binaries inside SGX enclaves.
The trusted Graphene-SGX runtime transparently takes care of all enclave
boundary interactions. For this, the libOS offers a limited `ecall` interface
to launch the application, and translates all system calls made by the shielded
application binary into untrusted `ocall`s. Graphene started as a research
project, but now has a growing user and contributor community and thrives
to become a standard solution in the Intel SGX landscape.

## Developer response and current status

We actively worked together with Graphene-SGX developers to ensure that all of
the discovered vulnerabilities were promptly fixed. The developers provided a
detailed overview of the current status with references to specific commits
containing the patches
[here](https://github.com/jovanbulck/0xbadc0de/issues/1). While most of the
issues were disclosed in April 2019, one specific
[issue](https://github.com/oscarlab/graphene/issues/28) was found by our team
already back in December 2016 and got subsequently fixed in the Graphene code
base in 2017 following our report. Hence, recent Graphene-SGX distributions are
not affected by the attacker code in the `entry-stack` directory.

