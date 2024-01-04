VUOS SCUSE: System Calls in USErspace
====

what
----
The System Call API is generally perceived as the *language* used by processes
to ask the kernel for services.
The same *language* can be used to forward the System Call requests to
processes running in user space.
In this way hypervisors running in user space (without any specific privilege
or capability) can provide processes with different *views*.
SCUSE is a general methodology enabling the implementation of many features
in user-space like namespaces, chroot, file system and networking support...
Projects like FUSE support the user-space delegation of specific services implementation,
SCUSE implements a similar concept but working at system call level it provides
a general purpose solution, not limited to a specific domain (as file systems for FUSE).

why
----
FUSE allows users to implement their own file systems in user space. A kernel
module forwards requests for each FUSE mounted file system to its corresponding
user process. The communication between the kernel module and the user process
takes place through /dev/fuse. Although FUSE implemented file systems are less
efficient than the file systems implemented in the kernel, FUSE is very
appreciated for its flexibility.

VUOS forwards all the system call requests to a hypervisor running in
user-space. At each system request the hypervisor can use its own implementation
of the service or let the process forward the request to the actual Linux
Kernel.  In some sense it is a generalized approach: FUSE is only for file
systems, the VUOS approach to forward System Calls in USErspace (SCUSE) is for
"everything".

VUOS hypervisor (umvu) runs in user-space and does not require any specific user
privilege or capability. Using specific plug-in modules VUOS provides
implementations of file systems (fuse), networking stacks, devices,
user/groups, overlay file systems, chroot.

For example the fuse module of VUOS is compatible with FUSE but it needs no
code in the kernel: mount and /dev/fuse are virtualized by VUOS.

VUOS can be seen as a way to implement namespaces at user level, a Virtual
Operating System in user space.

how
----
SCUSE is a general methodology to extend the system services at user level
by forwarding the system call request in the user-space.
The current implementation of the VUOS hypervisor (umvu) is based on ptrace.
`umvu` shows the effectiveness and the fields of application of SCUSE.
More efficient supports for SCUSE can be developed in the future.

where
----
[vuos](https://github.com/virtualsquare/vuos)
