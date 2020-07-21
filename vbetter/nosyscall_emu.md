`PTRACE_SYSEMU` is for User-Mode Linux only
====

# The problem

`ptrace` provides a means by which one *tracer* process can observe and control the execution of other
*tracee* processes.

`ptrace` is used for debuggin and virtualization. User-Mode Linux as well as VirtualSquare's project `VUOS`
are based on it.

The tag `PTRACE_SYSCALL` enables the tracing of system calls. THe tracee receves two events for each system call request of a tracee process:
before and after the processing of the system call request by the kernel.
In this way the tracer can cobserve and eventually modify the system call parameters during the first event. The tracer can
as well read and modify if needed the return value of the system call during the second event.

Paolo Giarrusso (Blaisorblade) proposed a feature named `PTRACE_SYSEMU` which entered the mainstream Linux kernel v. 2.6.14.
`PTRACE_SYSEMU` skips the kernel processing of the system call and only one upcall to the traces takes place.
This permits to speed-up User-Mode Linux. before `PTRACE_SYSEMU` User-Mode Linux used `PTRACE_SYSTEM` to change all the system calls
of the virtualized processes to `getpid`, a fast system call without any side effects. In fact User-Mode Linux needs to virtualize *all* the system calls
which are processed by a linux kernel running as a user process.

Unfortumatelu `PTRACE_SYSEMU` can be used only when *all* the system calls must be skipped/virtualized. There is no way to
read the system call parameters and choose if it has to be virtualized or processed by the kernel.

In the past VirtualSquare has proposed solutions like `PTRACE_SYSVM` and `PTRACE_MULTI`.
 
# Workaround

We have developed an effective workaround supporting the selective skipping/virtualization of system calls.

`umvu`, the user-mode implementation of `VUOS` uses a seccomp BPF filter (tag `SECCOMP_RET_TRACE`) instead of
`PTRACE_SYSCALL` or `PTRACE_SYSEMU` to get an event before the system call processing.

The umvu tracer has three choices:

* change the syscall numebr to -1 to skip the syscall, 
* restart the process using `PTRACE_SYSCALL` to get the second event after the syscall processing
* restart the process using `PTRACE_CONT` to process the syscall without the second event.

# Please

The role of the BPF seccomp is minimal due to the limitations of BFP. 
Please speedup the adoption of eBPF for seccomp.

# References

[umvu tracer](https://github.com/virtualsquare/vuos/blob/master/umvu/src/umvu_tracer.c)
