Let us fix the World!
====

During the development of VirtualSquare project we have found bugs, missing features, design weaknesses and
obsolete concepts in programs, libraries and protocols. 

* [map IP addresses to network controllers is anachronistic](newipaddr.md)
* [the C library is *impure*](impurelibc.md)
* [netdevice is obsolete](nonetdevice.md)
* [/etc/resolv.conf is hardcoded in glibc](vresolvconf.md)
* [Berkeley Sockets supports only one stack](nomsocket.md)
* [IP multicast supports only one server per IP address](multimulticast.md)
* [VXLAN's VTEP is a bottleneck](novtep.md)
* [the mount command is a *censor*](freemount.md)
* [`PTRACE_SYSEMU` is for User-Mode Linux only](nosyscall_emu.md)
* [eBPF for seccomp is useful (and harmless)!](seccomp_ebpf.md)
* [We need to synthesize poll/select events](vpoll.md)
* [iproute: `ip link add` for generic interfaces](iplinkadd.md)
* [qemu/kvm: all interfaces have the same default MAC](qemudefmac.md)
* [Linux \*at system calls idiosyncrasies](atidiosyncrasies.md)
* [Linux: dlmopen problems (dlclose does not work)](dlopen_problems.md)
