Internet of Threads (IoTh)
====

what
----
Processes and even threads can be the endpoints of Internet connections.

In other words IP addresses should be given to processes, because they are addressing services.

why
----
Because people are interested in services, it does not matter which computer is currently hosting
that service.

Using IP addresses assigned to hardware network controllers is as obsolete as using telephone fixed lines.
Portable phones are very convenient because they _address_ people, fixed lines _point_ to geographical
places. 

how
----
processes (or groups of processes) must have their own networking support. There are two methods:
kernel provided namespaces or networking stacks implemented as user-space libraries.

where
----
Several projects in VirtualSquare implement the idea of IoTh:

* [libioth](https://github.com/virtualsquare/libioth)
a convenient API for IoTh. Stack implementations can be loaded as plug-ins. `libioth` includes also
a plugin for vdestack
* [picoxnet](https://github.com/virtualsquare/picoxnet) a TCP-IP stack for the Internet of Threads based on picoTCP-ng.
* [ioth\_picox](https://github.com/virtualsquare/ioth_picox)
The picoxnet plug-in module for libioth

* [iothconf](https://github.com/virtualsquare/iothconf)
Internet of Threads (IoTh) stack configuration made easy peasy
* [iothdns](https://github.com/virtualsquare/iothdns)
Name Resolution support for the Internet of Threads.
* [iothnamed](https://github.com/virtualsquare/iothnamed)
iothnamed is a DNS server/forwarder/cache for the Internet of Threads supporting hash based IPv6 addresses and OTIP, i.e. one time IP.
* [namedhcp](https://github.com/virtualsquare/namedhcp)
A dhcpv6 server (and a dhcpv4 server) using the FQDN option (fully qualified domain name) to
query the DNS for the address to assign. (It can be used with iothnamed for hash based addresses and OTIP).
* [otip-utils](https://github.com/virtualsquare/otip-utils)
One Time IP address (OTIP) utilities: `otip_rproxy` (a reverse proxy to otip-ize tcp and udp
servers) and `otipaddr` (a simple command to compute the current otip address).
* [iothradvd](https://github.com/virtualsquare/iothradvd)
t is a router advertisement deamon library. The server runs as a thread.

* [vdens](https://github.com/rd235/vdens): create namespaces where services can have their own IP addresses
* [libvdestack](https://github.com/rd235/libvdestack): use a networking thread to provide a process with its own networking support (using kernel namespaces)

references:
----
Renzo Davoli, _Internet of Threads: Processes as Internet Nodes_, in International Journal on Advances in Internet Technology, 2014, 1-2, pp. 17 - 28
