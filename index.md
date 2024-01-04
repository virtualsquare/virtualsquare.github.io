![](v2large.png)

# VirtualSquare

**_all the virtuality you always wanted but you were afraid to ask_**

Welcome to Virtual Square wiki (2.0)! We are currently rewriting the entire
codebase of the VirtualSquare. We have almost completed the task.

Here you'll find almost everything you need to know to get started using
Virtual Square suite of tools and software. Remember that the software
presented in this Wiki is produced by research projects and so the latest
developments are extremely experimental.

Virtualsquare mailing list: [virtualsquare (at)
cs.unibo.it](https://lists.cs.unibo.it/mailman3/postorius/lists/virtualsquare.lists.cs.unibo.it/)
(click on the address to reach the mailing list info/subscribe page).

## The Virtual Square

### What is Virtual Square?

Virtual Square has existed since 2003. Now it is a virtual place where new
concepts of virtualization can be explored, implemented and can become new
tools for users and developers.

The best way to describe VirtualSquare is the list of its projects. There is a
short description of the main projects here below. For a complete view of
VirtualSquare projects please refer to the [list of VirtualSquare's
repositories](repos.md) and to the specific description and tutorial pages,
	accessible from the navigation bar on the top.

### An open laboratory for Virtuality

All the code written within the Virtual Square project is available on public
repositories under free/libre software licenses, the most part under GPL (v2 or later
		version) . Everyone can download Virtual Square tools and test the
effectiveness of proposed ideas.

All VirtualSquare contributors are software researcher-developers: when we
realize that a new abstraction is missing and would be convenient, we design,
				implement and release the software to make it real (or better to say
						*virtual*!).

## VirtualSquare *flagship* projects

### Virtual Distributed Ethernet

VDE is one of the tools developed within the Virtual Square project to provide
an effective communication platform for virtual entities interoperability. In
this context virtual entities can be virtual machines, namespaces, virtual
switches and routers, etc.

The main features of VDE are:

* consistent behavior with real ethernet network.
* It enables interconnection between virtual machines, namespaces, applications and virtual connectivity tools.
* Last but not least, it does not require administrative privileges to run.

Vde now implements the idea of Local Area Cloud using vxvde: virtual machines, namespaces,
processes running their own networking stacks, also running on different hosts on a LAN,
do not need any dispatching process (virtual switch).
Process migration is as simple as stopping a process on one host and restart it on another.
No reconfiguration is required.

### Internet of Threads (IoTh)

IoTh means the ability to give the role of Internet nodes to processes or even
to threads.  A process can have its own IP address. While this idea sounds
hardly exploitable in IPV4 due to the scarcity of addresses, it is a convenient
usage of the wide IPV6 address space.

A TCP-IP stack can be implemented as a library. In fact a TCP-IP stack implements the
_link_, _internetwork_ and _transport_ layers. A TCP-IP stack provide connection-oriented
(TCP) or connectionless (UDP) communications, sending and receiving packets of a
physical (or virtual) network (e.g. a VDE network).

### VUOS (and UMVU)

VUOS is a Virtual Operating System implemented at user space. Currently it implements about 150 Linux-
compatible system calls providing support for a wide range of applications. Each process or even each
thread in VUOS can see a different execution environment: file system contents, networking, devices, user ids
etc.

The VUOS idea is much broaden than what can be implemented by namespaces or containers today.
UMVU is a user-mode implementation of VUOS. UMVU is a partial virtual machine: it is a layer between the
processes and the kernel. System calls can be processed by UMVU to provide processes with a virtual view.
Instead, system calls can be forwarded to the kernel when non-virtualized access to the system
resources is required.

UMVU does not require any privilege to run (i.e. neither specific capabilities nor root access). Long debated
features like file system user-mounting in namespaces are supported by UMVU (without any risk!).
The kernel is unaware of the virtualization provided by UMVU, so the attack surface to the operating
system can be reduced (it is possible to run UMVU *namespaces* on linux kernel where the namespace
support has been disabled).

### other projects

During the design and development of the ideas of VirtualSquare several convenient general purpose tools, libraries have been created. It is the case of CADO: Capability DO (like a sudo providing users with just the capabilities they need). Another example is libnlq: a netlink library that can be used by programmers to configure the networking services (using functions, not external commands) and by designers of user-level networking stack libraries to provide their stack with netlink configuration support.
Many other utilities in terms of programs and libraries are valuable side effects of VirtualSquare projects.

## How to contribute to this Wiki

Note: contributions to this wiki are welcome. Send pull requests to [https://github.com/virtualsquare/virtualsquare.github.io](https://github.com/virtualsquare/virtualsquare.github.io)
