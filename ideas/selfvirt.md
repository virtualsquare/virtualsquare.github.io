Self Virtualization (purelibc)
====

what
----
The ability of a process to change the behavior of its own syscalls.

why
----
Because in this way it is possible to extend the scope of existing libraries.

how
----
The current implementation named [purelibc](https://github.com/virtualsquare/purelibc) is based on an overlay library loaded over libc (it uses `LD_PRELOAD`).
A specific "pure" target for the libc is in the future challenges of VirtualSquare. (A pure C library does not include the interface functions to the system calls,
a process can provide its own implementation of the system calls).

where
----
It is used in umvu to support nested virtualization. It is purelibc that permits to re-use libraries like e2fslib in vufuseext2 on virtual resources.
The implementation of this feature in umvu is in the [`vu_nested.c` file](https://github.com/virtualsquare/vuos/blob/master/umvu/src/vu_nesting.c).

<!--references:-->


