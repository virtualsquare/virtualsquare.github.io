Using several networking stack together: msocket
====

what
----
A new system call:
```C
int msocket(char * path, int domain, int type, int protocol);
```
It is like `socket(2)`: the new argument `path` identifies the stack to use.

why
----
Because there can be several networking stacks available for a process.

Because while UNIX uses the file system as a global naming facility
(e.g. devices, `PF_LOCAL` sockets, etc), networking support does 
not use it yet.

how
----
We propose a new filetype `S_IFSTACK` for networking stack special files.

Programmers can choose among the available stacks using `msocket` instead
of `socket(2)`.

e.g.:
This statement opens a TCP socket using the stack __/dev/net/mynet__
```C
fd = msocket("/dev/net/mynet", AF_INET, SOCK_STREAM, 0);
```

It is possible to define a default stack for each address family.
In a system providing `msocket`, the default stack is used for `socket(2)`
or when in `msocket` the argument `path` is NULL,

The definition of the default stack is a feature of `msocket`:
when the argument `type` is `SOCK_DEFAULT` msocket does not define any communication
endpoint, instead it defines the stack that will be used for  the  successive  
msocket  calls  with  NULL  path, or for the successive (obsolete)
socket(2) calls.

e.g.:
The following excerpt of a C program defines the default stack for IPV4 to be
__/dev/net/topnet__ and then it opens a TCP socket (that will be provided by
		the current default stack, i.e.`topnet):
```C
if (msocket("/dev/net/topnet", AF_INET, SOCK_DEFAULT, 0) < 0)
	/* error handling */;
fd = socket(AF_INET, SOCK_STREAM, 0);
```

This feature provides backwards compatibility for programs using `socket(2)`
in environments where there are several available stacks.
These programs will be able to use one stack at a time. Several instances of the
same program can use different stacks.


where
----
`msocket` is implemented in [vuos](https://github.com/virtualsquare/vuos).
Vuos, in fact, permits to extend the set of system calls available to processes.

The utility command `vustack` (also in [vuos](https://github.com/virtualsquare/vuos))
allows users to choose the current default stack.

references:
----
Renzo Davoli and Michael Goldweber. _msocket: multiple stack support for the berkeley socket API_. In Proc. of ACM SAC '12. 2012, pp. 588-593. 
