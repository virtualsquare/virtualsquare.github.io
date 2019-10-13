execs is (was) missing
====

what
----
`execve(2)` system call has a number of helper functions giving users many options to specify the
command line args. (e.g. `execl, execlp, execle, execv, execvp, execvpe...`).
A way to specify the args as one string (as args are given when typing a command using a shell) is missing.
More precisely, it *was* missing, because [the library `s2argv-execs`](https://github.com/rd235/s2argv-execs) has 
filled the lack.

why
----
* because otherwise programmers use the unsafe `system(3)`
* or (even worse) use `fork/exec` of `/bin/ssh -c "..."`
* wise programmers must survive code wrestling using strtok

how
----
the syntax is crear and follows the standard scheme of naming for `exec*` functions:
```C
int execs(const char *path, const char *args);
int execse(const char *path, const char *args, char *const envp[]);
int execsp(const char *args);
int execspe(const char *args, char *const envp[]);
```

Notes:

* `execsp` does not need any pathname, it uses `argv[0]` as parsed from `args`.
* args is const, i.e. `exec*` functions do not modify it.
* `execs*` functions do not use dynamic allocation (allocate memory on the stack)
* `execs*` functions are thread safe
* the library provides also eexecs functions (using less memory, but modifying args)
* for lazy programmers, the library includes drop-in replacements for `system(3)` and `popen(3)` 
(named `system_nosh` and `popen_nosh` respectively) using execs instead of starting a shell.

where
----
Virtualsquare uses execs in many places. An incomplete list includes:

* cado/scado.c: to start the command
* libvdestack/vdestack.c: uses a more advanced interface provided by the library `s2multiargv` (mutiple commands, semicolon `;` separated.)

references:
----
[on GITHUB](https://github.com/rd235/s2argv-execs)
