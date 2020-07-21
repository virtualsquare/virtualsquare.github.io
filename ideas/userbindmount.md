user bind mount
====

what
----
`libuserbindmount` is a library providing support for bind mount in user namespaces. `userbindmount` is a utility command based on libuserbindmount.

why
----
A common usage of libuserbindmount is to support user configuration of files whose path is hard-coded in libraries
(e.g. to allow the choice of the domain name server for name resolution: `/etc/resolv.conf` is hardcoded in glibc).

how
----
In your code add:
```C
userbindmount_string("nameserver 9.9.9.9\n", "/etc/resolv.conf", 0600);
```

The library supports the *substitution* of file contents using strings (as in the example here above), other files or
data.


The project supplies also a command named `userbindount`. Here is an example:
```
$ echo "nameserver 9.9.9.9" > /tmp/resolv.conf
$ userbindmount /tmp/resolv.conf /etc/resolv.conf --
$ cat /etc/resolv.conf
nameserver 9.9.9.9
$ exit
```

where
----
*userbindmount* is useful to test user level networking stacks (in many cases the name resolver configured in `/etc/resolv.conf`
		is meaningless in the virtual networks).

references:
----

* [userbindmount](https://github.com/rd235/userbindmount)
