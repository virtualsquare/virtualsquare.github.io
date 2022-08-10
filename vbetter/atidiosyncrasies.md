Linux \*at system calls idiosyncrasies
====

# The problem
Linux Kernel version 2.6.16 added the \*at system calls (defined in POSIX 2008).
Namely: openat, mkdirat, mknodat, fchownat, futimesat, newfstatat, unlinkat, renameat,
linkat, symlinkat, readlinkat, fchmodat, faccessat, utimensat.

There are some weird inconsistencies.

* `openat` do not support `AT_EMPTY_PATH`. 

* `faccessat` system call has three args, the complete implementation of the 
specifications, including the flags is *emulated* by the glibc wrapper function.
(see [faccessat.c](https://sourceware.org/git/?p=glibc.git;a=blob;f=sysdeps/unix/sysv/linux/faccessat.c)).
This implementation does not seem to support posix ACL.

* the \*at function for truncate is missing (something like `truncateat` or
`ftruncateat`).

# Workaround

`vufs` is deeply based on the \*at system calls. It uses file descriptors to
identify the root of the mounted tree, of the mountpoint and of the hidden
tree which stores virtual removed files and virtual file attributes.
Each `openat` has an exception to manage the root dir.
The function `fake_truncateat` provides a workaround for the missing system call.

In purelibc `faccessat` must be emulated as in glibc.

# Please

Dear syscall designers, kernel and glibc developers: 

* `openat`: `AT_EMPTY_PATH` should be added, maybe extending the new `openat2`

* `faccessat`: please add `faccessat2` fully compliant with the POSIX definition
(so we can get rid of *emulators* and ACL can be supported).

* `truncateat`: please add it
