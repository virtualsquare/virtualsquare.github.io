Let us fix the World!
====

During the development of VirtualSquare project we have found bugs, missing features, design weaknesses and
obsolete concepts in programs, libraries and protocols. 

* [map IP addresses to network controllers is anachronistic](newipaddr.md)
* [the C library is impure](impurelibc.md)
* [netdevice is obsolete](nonetdevice.md)
* [/etc/resolv.conf is hardcoded in glibc](vresolvconf.md)
* [Berkeley Sockets supports only one stack](nomsocket.md)
* [IP multicast supports only one server per IP address](multimulticast.md)
* [VXLAN's VTEP is a bottleneck](novtep.md)
* [the mount command is a *censor*](freemount.md)
* [ptrace's `SYSCALL_EMU` is for User-Mode Linux only](nosyscall_emu.md)

## We do V better

VirtualSquare tools can be seen as general purpose solutions,
Features currently provided by other projects can be regarded as
VirtualSquare use cases.

<!-- TBD list of projects
https://github.com/rootless-containers/slirp4netns
fakeroot
fuse
-->
