Berkeley Sockets supports only one stack
====

# The problem

When the Berkeley Sockets API was created, networking was perceived as
a way for *computers* to communicate.

So it was natural the equation one computer, one networking stack.

Now many problems would require to use more networking stacks at the same time,
but the API does not support the selection of the actual stack.
In fact a coscket is created using the following function/system call:
```C
int socket(int domain, int type, int protocol);
```

# Workaround

We propose and support in our projects a new function:
```
int msocket(char *stack, int domain, int type, int protocol);
```
where stack is the path of a special file representing the stack.

# Please

The multi-stack support whould be added to the Berkeley Sockets API.

# References

Davoli R., Goldweber M., *msocket: Multiple stack support for the Berkeley Socket api.* In ACM 27th Symposium On Applied Com-
putingi (SAC), 2012.
