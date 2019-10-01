Parallel Tracing of Concurrent Threads (guardian angels)
====

what
----
When several processes/threads must be tracked for debugging or for virtualization, the tracer/hypervisor spawns a thread for each process or thread.

There is a one-to-one relationship between each traced process/thread and each tracee's thread (each tracee's thread is the _guardian angel_ of a 
traced process or thread).

why
----
Because this technique exploits the parallelism of multi-core systems.

how
----
The current implementation uses a trick based on ptrace. When a traced process calls a fork, vfork or clone, the first system call of the new traced process/thread 
is received by the guardian angel of the parent process/thread. The system call is temporarily changed to `poll((struct pollfd *)1, 0, -1)`.
The current guardian angel detaches from the new traced process/thread (which is blocked), a new thread is created in the tracee and it _grabs_ the new traced process or thread
using `PTRACE_SEIZE`, the original system call is then restored and the process restarted.

where
----
the code is in the [tracer of umvu](https://github.com/virtualsquare/vuos/blob/master/umvu/src/umvu_tracer.c), function `transfer_tracee`.

references:
----
