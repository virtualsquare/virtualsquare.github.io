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
Libslirp (A TCP-IP emulator as a library) made easy peasy for Linux (this library obsolets virtualsquare's [old libslirp](https://github.com/rd235/libslirp)).

 * [vdeplug\_slirp](https://github.com/virtualsquare/vdeplug_slirp)
A slirp plugin for vdeplug4. (this obsoletes the [old vdeplug\_slirp plugin](https://github.com/rd235/vdeplug_slirp) based on the deprecated [old libslirp](https://github.com/rd235/libslirp) library).

 * [vdeplug\_agno](https://github.com/rd235/vdeplug_agno)
agnostic encryption nested plugin for vdeplug4

 * [vdeplug\_vlan](https://github.com/rd235/vdeplug_vlan)
802.1q (vlan) support nested plugin for vdeplug4

 * [libvdestack](https://github.com/rd235/libvdestack)
Internet of Threads through Network Namespaces

 * [vxvdex](https://github.com/rd235/vxvdex)
VXVDEX: connect distributed private network namespaces

 * [vdeplug\_pcap](https://github.com/rd235/vdeplug_pcap)
A pcap plugin for vdeplug4

 * [vdeplug\_vdesl](https://github.com/virtualsquare/vdeplug_vdesl)
VDE point to point nets over serial links

 * [virtualbricks](https://github.com/virtualsquare/virtualbricks)
A GTK frontend for VDE and QEMU/KVM. Supports multiple network on the same host, tunneling between hosts networks, a fully featured configuration interface.

 * [libnlq](https://github.com/virtualsquare/libnlq)
Netlink Queue Library: managing network configuration via netlink (client and server side)

 * [nlinline](https://github.com/virtualsquare/nlinline)
NLINLINE (netlink inline) is a library of inline functions implementing a quick and clean API for networking configuration via netlink.

 * [&#9785; vde-2](https://github.com/virtualsquare/vde-2)
The vde-2 vde\_switch is fully compatible with vdeplug4. Although it has not been rewritten yet, it includes
several tools that are actual like vde\switch and wirefilter.

 * [&#9785; vdetelweb](https://github.com/virtualsquare/vdetelweb)
Telnet and web configuration client for vde\_switch and wirefilter

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

 * [&#9785; view-os](https://github.com/virtualsquare/view-os)
View-OS is the previous implementation of VUOS. This repository also includes lwipv6, a hybrid v4/v6 netwrking stack
implemented as a library.

## Other projects

 * [cado](https://github.com/rd235/cado)
CADO: Capability DO (like a sudo providing users with just the capabilities they need)

 * [strcase](https://github.com/rd235/strcase)
Multiway branch (switch) for short strings in C (in one header file)

 * [s2argv-execs](https://github.com/rd235/s2argv-execs)
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

 * [v2utils](https://github.com/rd235/(https://github.com/virtualsquare/v2utils)
v2utils: virtualsquare libraries and utilities. It is for Debian packaging of small general
purpose libraries and tools.

 * [v2glossary](https://github.com/virtualsquare/v2glossary)
VirtualSquare Glossary

 * [nsutils](https://github.com/rd235/nsutils)
linux namespace utilities
