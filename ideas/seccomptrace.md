SECCOMP optimization for tracing
====

what
----
A BPF seccomp program can speed up a virtualization based on ptrace.

why
----
Because a partial virtualization hypervisor needs the support for three different behaviors when it processes a system call request:

1. the kernel ignores the system call which is handled entirely by the hypervisor
2. the kernel runs the system call
3. the kernel runs the system call (or a different system call). The hypervisor need to get the control again when the kernel has
completed to get the return value (and maybe to change it).

Without this idea (1) is implemented changing the system call to a harmless and relatively fast call like `getpid`.
Ptrace always provides a second tracing event when the kernel has completed the system call. This event can be ignored
in (1) and (2). There are useless interactions between the kernel and the hypervisor, this idea soves this problem.

how
----
Use a BPF program like the following one:
```C
static struct sock_filter seccomp_filter[] = {
  BPF_STMT(BPF_LD+BPF_W+BPF_ABS, offsetof(struct seccomp_data, nr)),

  BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_restart_syscall, 0, 1),
  BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),

  BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_TRACE),
};

static struct sock_fprog seccomp_prog = {
  .filter = seccomp_filter,
  .len = (unsigned short) (sizeof(seccomp_filter)/sizeof(seccomp_filter[0])),
};
```

attach the program to the traced process:
```C
if (r_prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == -1) {
	perror("prctl(PR_SET_NO_NEW_PRIVS)");
	return -1;
}
if (r_seccomp(SECCOMP_SET_MODE_FILTER, 0, &seccomp_prog) == -1) {
	perror("when setting seccomp filter");
	return -1;
}
```

Then for each syscall request the hypervisor gets a tracing event via `wait(2)`.  The status is `SIGTRAP | (PTRACE_EVENT_SECCOMP << 8)`.
The three cases above can be handled as follows:

1. change the syscall number to -1. Restart the process by `PTRACE_CONT`.
2. restart the process by `PTRACE_CONT`
3. restart the process by `PTRACE_SYSCALL`.

where
----
It is implemented in umvu, the source file is [`umvu_tracer.c`](https://github.com/virtualsquare/vuos/blob/master/umvu/src/umvu_tracer.c).
(Actually the seccomp program here includes a second trick to combine this idea with the [guardian angels](partrace.md) technique.)

<!-- references: -->
