per user networking definition (pam\_net)
====

what
----

In Unix/Linux, network access is provided by the kernel and it is regarded
as a shared services: all the users and processes have a unified view
on the networking services.

Libpam-net provides Linux users with their own network definition using
Linux Pluggable Authentication Modules.

why
----

A sysadm may need to provide users with different networking services,
their own IP address, routing, shaping etc... or no network access at all.

For example libpam-net enables the creation of accounts whose users 
can use ssh to log-in,
run commands but any attempt to the network is forbidden (e.g. further
ssh connection, web access etc). 
The only interface they can see is an isolated loopback lo interface created 
at login time.
It if not possible in this way to misuse these accounts to have anonymous
net access maybe to attack remote systems.

how
----
The two modules `pam_newnet` and `pam_usernet` create and/or join a network
namespace during the authorization process.

where
----
Libpam-net is available as a [VirtualSquare project on GITHUB](https://github.com/rd235/libpam-net) and it is provided as [Debian Package](https://packages.debian.org/sid/libpam-net)
