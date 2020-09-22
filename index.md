#![](v2large.png) VirtualSquare

**_all the virtuality you always wanted but you were afraid to ask_**

Welcome to Virtual Square wiki (2.0)! We are currently rewriting the entire
codebase of the VirtualSquare. We have almost completed the task.

Here you'll find almost everything you need to know to get started using
Virtual Square suite of tools and software. Remember that the software
presented in this Wiki is produced by a research projects and so the latest
developments are extremely experimental.

Virtualsquare mailing list: [virtualsquare (at)
cs.unibo.it](http://www.cs.unibo.it/cgi-bin/mailman/listinfo/virtualsquare)
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
repositories under free software licenses, the most part under GPL (v2 or later
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
* It enables interconnection between virtual machines, applications and virtual connectivity tools.
* Last but not least, it does not require administrative privileges to run.

Vde now implements the idea of Local Area Cloud using vxvde: virtual machines, namespaces,
processes running their own networking stacks, also running on different hosts on a LAN,
do not need any dispatching process (virtual switch).
Process migration is as simple as stopping a process on one host and restart it on another.
No reconfiguration is required.

### VUOS (and UMVU)

The motto of this projects is "give each process its own VU" (if you spell v.u. it should sound like *view*). This is the point: each process or even each thread in VUOS can *see* a different *execution environment*: file system contents, networking, devices, user ids etc.

The VUOS idea is much broaden than what can be implemented by namespaces today. UMVU is a user-mode implementation of VUOS. UMVU is a partial virtual machine: it is a layer between the process and the kernel. System calls can be processed by UMVU to provide processes with a virtual view. On the contrary, system calls can be forwarded to the kernel when non-virtualized access to the system resources is required.

UMVU does not require any privilege to run (i.e. no capability or root access). Long debated features like file system user-mounting in namespaces are supported (without any risk!) by UMVU.

The kernel is unaware of the virtualization provided by UMVU, so the attack surface to the operating system can be reduced (it is possible to run UMVU *namespaces* on linux kernel where the namespace support has been disabled).

### other projects

During the design and development of the ideas of VirtualSquare several convenient general purpose tools, libraries have been created. It is the case of CADO: Capability DO (like a sudo providing users with just the capabilities they need). Another example is libnlq: a netlink library that can be used by programmers to configure the networking services (using functions, not external commands) and by designers of user-level networking stack libraries to provide their stack with netlink configuration support.
Many other utilities in terms of programs and libraries are valuable side effects of VirtualSquare projects.

## How to contribute to this Wiki

Note: contributions to this wiki are welcome. Send pull requests to [https://github.com/virtualsquare/virtualsquare.github.io](https://github.com/virtualsquare/virtualsquare.github.io)
