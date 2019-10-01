Hash based IPv6 addresses
====

what
----
The host part of an IPv6 address can be computed as the result of a hash function 
computer on the fully qualified domain name.

This eases the life of system administrators dealing with IPv6 networks.

why
----
Because the configuration of an IPv6 network is a rather daunting and
error-prone procedure for system administrators. Each node must be
provided with its own (128 bit long) IPv6 address and with a domain name
manageable by human beings.

Autoconfiguration methods can give addresses to interfaces but
do not provide any means of configuring the DNS.
So autoconfiguration is suitable for clients. If a host has to
act as a server, it must have a fully qualified domain name and 
the DNS service has to map its name to its IP address.

In the [Internet of Thread](ioth.md) scenario, the number of network _nodes_
can be orders of magnitude higher than before, as each process or thread can be a _node_. 
This idea of hash based IPv6 addresses is a viable
solution to the problem to manage the DNS resolution in IoTh environments.

how
----
The host part of an IPv6 address can be computed as the result of a hash function
computer on the fully qualified domain name.

In this way it is possible to write a DNS server able to resolve the addresses
of any hostname in a sub-domain provided the network prefix of that sub-domain.

The installation of a new node of the network (computer, [namespace](non.md), [IoTh process](ioth.md))
is as simple as providing it with its IPv6 address
(the one obtained by concatenating the network prefix and the
 host address computed by the hash function).

There is no need to change the configuration of the DNS.

Actually the installation of a new node (or its renaming) is even simpler than that.
The host can use a DHCP service designed to get the right address
from the DNS server given its fully qualified domain name.

So a system administrator has nothing to do more than assigning
the new node its name. (They have just to _baptize_ the new node)

where
----
[VDE DNS utilities](https://github.com/rd235/vde_dnsutils) project provide 
tools like `hashdns` and `fqdndhcp` to implement hash based IPv6 addresses.

references:
----

Renzo Davoli, _IPv6 Hash-Based Addresses for Simple Network Deployment_, in: Proc. of AFIN 2013 : The Fifth International Conference on Advances in Future Internet, 2013, pp. 15 - 20 
