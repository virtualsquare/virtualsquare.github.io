eBPF for seccomp is useful (and harmless)!
=====

# Introduction

Berkeley Packet Filter was initially introduced to capture network packets
efficiently. 
Using BPF packets get selected in the kernel: BPF selects the packets that need
to be forwarded to the user level and those that must be dropped.
Filter programs are written in a quite restrictive language.
It is user code run by the kernel: it has access only to the packet buffer and
some private registers. The language has been designed to forbid loops.

BPF has evolved during the time:

* The language has evolved: now it supports helper functions and data structures
that permit communication with the user level code. The extended language is
often referred to as *eBPF* extended BPF (on the contrary in order to stress
the difference sometimes *cBPF*, classic BPF, is the name used for the original language).

* BPF has been applied to a number of different usages. It is used for kernel debugging:
in this case BPF filters data coming from hooks and probes in the kernel instead
of networking packets. BPF is used also to filter and/or trace system calls.
In fact BPF programs can be used as filters for seccomp.

* The Linux kernel has a just-in-time compiler for eBPF programs so the filtering program
can run at machine code speed.

* There are supports for compilers (e.g. clang) able to generate eBPF bytecode, so
complex filters can be written using high level languages.

# The problem

* In Linux BPF filters can be used only by programs owning the `CAP_SYS_ADMIN` capability.
There are two exceptions: network packet filters and seccomp.

* Linux supports eBPF for all BPF usages *but* seccomp.

* A proposal to add seccomp-eBPF was refused[1].

* Fast user level syscall interposition needs some form of offloading of code
in the kernel.

# Discussion

We  do not understand which further threats could
be added by seccomp eBPF.

Currently it is possible for unprivileged users:

* A) to add a seccomp (classic) BPF filter
* B) to add a eBPF socket filter (e.g. for UDP traffic).

Programs for A and B receive a buffer (the packet for B and `struct seccomp_data` for A),
run some code and give a result which is the length of the packet for A 
(packets may be trucated, zero length
means to drop the packet) or a tag for B (allow/trap/trace/kill process).

Now let us assume by Reductio ad absurdum that we allow seccomp eBPF and that
an eBPF process P is able to create a breach in the security of the system.
(We assume that we give to seccomp eBPF access to at most the same set of helper
functions and data structures currently available for Socket filtering eBPF).

Now if P succeeds to break the security due to its return value, it is already possible
to generate the same tag using BPF.

If P breaks the security  of the system during its execution let us create a program
P' which simply adds an offset to all references to the input buffer
(the offset is equal to the length of the UDP packet header).

Now let us send a UDP packet to P' with the same contents of the `struct seccomp_data`
processed by P.

P' makes on this packet the same steps of P on its input.
So the attack is already possible by using packet filtering eBPF.

# Workaround
In `umvu` we use seccomp-cBPF to avoid the double mode switch of ptrace syscall tracing.
All the system call filtering is currently implemented as user space code.

# Please
The discussion about seccomp-eBPF must be reopened.

# References:

[LKML thread about seccomp-eBPF](https://lore.kernel.org/netdev/20180226072651.GA27045@ircssh-2.c.rugged-nimbus-611.internal/)

[LWN article on this problem](https://lwn.net/Articles/796328/)
