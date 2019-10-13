network configuration: must be simple, inlined and via netlin
====

what
----
`nlinline` is a *library* (one header file) providing a simple API to perform
the most important configuration actions using netlink:
* interface up and down
* add/delete IPv4 addresses
* add/delete IPv4 routes
* add/delete IPv6 addresses
* add/delete IPv6 routes

why
----
* because there is not a standard API for network configuration (netdevice(3) 
	is obsolete!).
* because the standard way to configure the net is *de-facto* NETLINK
* because many programs fork/execute ip(8) to configure networking
* because some programs use system(3) or fork/exec `/bin/sh -c ip ...', 
	and this is even worse
* libnl is poorly documented, quite complex and generates run-time lib dependencies

how
----
`nlinline` is a minimal library. It depends only at compile time
only on the the linux glibc headers (linux-libc-dev).

where
----
We use nlinline in [`libpam-net`](https://github.com/rd235/libpam-net).
It is a PAM module providing users with personal network namespaces.
Being a pam module it has stringent security requirements.
`nlinline` gives `libpam-net` the ability to set interfaces up and down
still having no run-time dependencies.

references:
----
[`nlinline`: https://github.com/virtualsquare/nlinline](https://github.com/virtualsquare/nlinline)

[`libpam-net`: https://github.com/rd235/libpam-net](https://github.com/rd235/libpam-net)
