# VirtualSquare repositories

Note: repositories tagged with &#9785; are old versions. Many of them include
convenient features which have not been ported yet to the new codebase.

## VDE and virtual networking projects

 * [vdeplug4](https://github.com/rd235/vdeplug4)
VDE: Virtual Distributed Ethernet. Plug your VM directly to the cloud.
This is the new vde\_plug. It also implements the idea of local area cloud.
Fully backwards compatible with vdeplug of vde2.

 * [vdens](https://github.com/rd235/vdens)
Create User Namespaces connected to VDE networks

 * [libvdeslirp](https://github.com/virtualsquare/libvdeslirp)
Libslirp (A TCP-IP emulator as a library) made easy peasy for Linux (this library obsoletes virtualsquare's [old libslirp](https://github.com/rd235/libslirp)).

 * [vdeplug\_slirp](https://github.com/virtualsquare/vdeplug_slirp)
A slirp plugin for vdeplug4. (this obsoletes the [old vdeplug\_slirp plugin](https://github.com/rd235/vdeplug_slirp) based on the deprecated [old libslirp](https://github.com/rd235/libslirp) library).

 * [vdeplug\_agno](https://github.com/virtualsquare/vdeplug_agno)
agnostic encryption nested plugin for vdeplug4

 * [vdeplug\_vlan](https://github.com/virtualsquare/vdeplug_vlan)
802.1q (vlan) support nested plugin for vdeplug4

 * [vdeplug\_pcap](https://github.com/virtualsquare/vdeplug_pcap)
A pcap plugin for vdeplug4

 * [vdeplug\_vdesl](https://github.com/virtualsquare/vdeplug_vdesl)
VDE point to point nets over serial links

 * [vxvdex](https://github.com/rd235/vxvdex)
VXVDEX: connect distributed private network namespaces

 * [libioth](https://github.com/virtualsquare/libioth)
The definitive API for the Internet of Threads

 * [libnlq](https://github.com/virtualsquare/libnlq)
Netlink Queue Library: managing network configuration via netlink (client and server side)

 * [nlinline](https://github.com/virtualsquare/nlinline)
NLINLINE (netlink inline) is a library of inline functions implementing a quick and clean API for networking configuration via netlink.

 * [ioth\_picox](https://github.com/virtualsquare/ioth_picox)
The picoxnet module for libioth

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

 * [libvdestack](https://github.com/rd235/libvdestack)
Internet of Threads through Network Namespaces

 * [virtualbricks](https://github.com/virtualsquare/virtualbricks)
A GTK frontend for VDE and QEMU/KVM. Supports multiple network on the same host, tunneling between hosts networks, a fully featured configuration interface.

 * [&#9785; vde-2](https://github.com/virtualsquare/vde-2)
The vde-2 vde\_switch is fully compatible with vdeplug4. Although it has not been rewritten yet, it includes
several tools that are actual like vde\switch and wirefilter.

 * [&#9785; vdetelweb](https://github.com/virtualsquare/vdetelweb)
Telnet and web configuration client for vde\_switch and wirefilter

 * [&#9785; vde\_dnsutils](https://github.com/rd235/vde_dnsutils)
DNS utilities for vde projects (hashdns/fqdndhcp)
Obsolete: the features of vde\_dnsutils have been reimplemented in iothnamed and namedhcp

 * [&#9785; ipn](https://github.com/virtualsquare/ipn)
inter process networking, a proposal for a multicasting API in Linux (interesting but obsolete)

 * [&#9785; kernel-patch-ipn](https://github.com/virtualsquare/kernel-patch-ipn)
the kernel part of the inter process networking (IPN) implementation.

 * [&#9785; vde-netemu](https://github.com/virtualsquare/vde-netemu)
An alternative implementation of vde's wirefilter based on a different organization of components

## VUOS (and partial virtualization) projects

 * [vuos](https://github.com/virtualsquare/vuos)
VUOS view based o.s.

 * [purelibc](https://github.com/virtualsquare/purelibc)
A glibc overlay library for process self-virtualization

 * [fusefatfs](https://github.com/virtualsquare/fusefatfs)
mount FAT file systems using FUSE and VUOS/vufuse

 * [vufusearchive](https://github.com/virtualsquare/vufusearchive)
A `vufuse module based on libarchive: it supports tar/zip/iso (including compressed archives)

 * [vunetioth](https://github.com/virtualsquare/vunetioth) A VUOS vunet module for libioth.

 * [vunetpicox](https://github.com/virtualsquare/vunetpicox) A VUOS vunet module for picoxnet.

 * [&#9785; view-os](https://github.com/virtualsquare/view-os)
View-OS is the previous implementation of VUOS. This repository also includes lwipv6, a hybrid v4/v6 netwrking stack
implemented as a library.

## Other projects

 * [cado](https://github.com/rd235/cado)
CADO: Capability DO (like a sudo providing users with just the capabilities they need)

 * [umps](https://github.com/virtualsquare/umps3)
µMPS is an educational computer system architecture and an accompanying
emulator designed from the ground up to achieve the right trade-off between
simplicity and elegance on one side, and realism on the other.

 * [v2syslog](https://github.com/virtualsquare/v2syslog)
Syslog library and deamon for virtualsquare projects

 * [picotcp](https://github.com/virtualsquare/picotcp): picoTCP is a small-footprint,
modular TCP/IP stack designed for embedded systems and the Internet of Things.
This fork is also known as picoTCP-ng.
There is also an exprerimental-still unofficial Debian package (on
[salsa](https://salsa.debian.org/virtualsquare-team/picotcp)) which
generates/installs a shared library to support IoTh (Internet of Threads).

 * [picoxnet](https://github.com/virtualsquare/picoxnet) a stack for the Internet of Threads based on picoTCP-ng.
picoxnet provides a standard API based on BSD-Sockets, it supports NETLINK for stack configuration. The file descriptors
defined by picoxnet's functions can be used in event driven system calls like `select`, `poll`, `epoll`, etc.

 * [strcase](https://github.com/rd235/strcase)
Multiway branch (switch) for short strings in C (in one header file)

 * [s2argv-execs](https://github.com/virtualsquare/s2argv-execs)
s2argv converts a command string into an argv array for execv\*, execs is like execv taking a string instead of an argv

 * [userbindmount](https://github.com/rd235/userbindmount)
A library and a utility command providing support for bind mount in user namespaces.

 * [libvolatilestream](https://github.com/rd235/libvolatilestream)
volatile stream = stdio FILE\* stream as a temporary dynamically allocated (and deallocated) memory buffer

 * [libfduserdata](https://github.com/rd235/libfduserdata)
associate file descriptors with user defined data

 * [libvpoll-eventfd](https://github.com/rd235/libvpoll-eventfd)
generate synthetic events for poll/select/ppoll/pselect/epoll

 * [libstropt](https://github.com/rd235/libstropt)
Parse options from a string (supports quotation, option arguments, no malloc needed for parsing)

 * [libpam-net](https://github.com/rd235/libpam-net)
LIBPAM-NET: create/join network namespaces at login

 * [randmac](https://github.com/virtualsquare/randmac)
Create random MAC addresses for Virtual Machines.

 * [virtualsquare](https://github.com/virtualsquare/virtualsquare.github.io)
VirtualSquare wiki (the source code of this web site!)

 * [v2glossary](https://github.com/virtualsquare/v2glossary)
VirtualSquare Glossary

 * [nsutils](https://github.com/rd235/nsutils)
linux namespace utilities
