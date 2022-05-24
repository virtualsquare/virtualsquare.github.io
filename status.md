## News

ioth utilities:

* `iothconf`: Internet of Threads (IoTh) stack configuration made easy peasy: one string configuration for ioth stacks.
It supports: ethernet MAC assignment or hash computation, static IPv4 IPv6, dhcp v4 or v6, slaac, slaac +
hash autoconfiguration.
* `iothdns`: Name Resolution support library for the IoTh stacks.
It provides  for client programs that need to query DNS servers (inluding `ioth_getaddrinfo` and `ioth_getnameinfo`)
and for DNS servers, forwarders, filters that need to parse DNS queries, compose and send back appropriate replies

---

new (Debian): 

* libvpoll-eventfd, vdeplug-slirp, vdeplug-vdels, vdeplug-vlan, vdeplug-agno, vdeplug-pcap are now in SID.
* libexecs package has been updated (converted to cmake and migrated to the virtualsquare team management)
* fuse-umfuse-ext2, vdetelweb: debhelper updated.

We are ready for Bullseye freeze and release as stable.

new: libioth: The definitive API for the Internet of Threads

* the API is minimal: Berkeley Sockets + msocket + newstack/delstack.
* the stack implementation can be chosen as a plugin at run time.
* netlink based stack/interface/ip configuration via _nlinline_.
* ioth sockets are real file descriptors, poll/select/ppoll/pselect/epoll friendly
* plug-ins are loaded in private address namespaces: libioth supports several stacks
of the same type (same plugin) even if the stack implementation library was designed to
provide just one stack.

---

new: vdeplug4, libpam-net ad umps3 are now in SID

As a consequence of vdeplug4, user-mode linux and virtualbox available in SID
can now use the rich set of new vde plugins out of the box... pardon, out of the package.
(qemu/kvm was already compatible).

---

new: vde-2 new packet is in Debian SID.

----

new: [picotcp](https://github.com/virtualsquare/picotcp): picoTCP is a small-footprint, 
modular TCP/IP stack designed for embedded systems and the Internet of Things. 
There is also an exprerimental-still unofficial Debian package (on 
[salsa](https://salsa.debian.org/virtualsquare-team/picotcp)) which
generates/installs a shared library to support IoTh (Internet of Threads).

Warning: picotcp is *not* yet ready to enter Debian. We are working on it.

----

New: [vufusearchive](https://github.com/virtualsquare/vufusearchive)
A `vufuse module based on libarchive: it supports tar/zip/iso (including compressed archives)

----

New: [fusefatfs/vufusefatfs](https://github.com/virtualsquare/fusefatfs): 
FUSE/VUOS-vufuse module for FAT12/16/32 and exFAT.

----

New: The pages of the tutorials are almost complete. Give it a try, it is the 
third menu here above!

----

New vde\_plug: `vdesl`.

This vde\_plug creates a virtual point to point ethernet link over a serial line.

Example: connect the uart ports of two Raspberry PI boards (GND-\>GND, TXD-\>RXD, RXD-\>TXD).

The following command (on both RasPIs):
```bash
       sudo vde_plug -d tap://vdesl0 vdesl:///dev/ttyAMA0[speed=4000000]
```

creates a 4Mbps ethernet link connecting the two `vdesl0` interfaces.


## Debian

Warning: debhelper compat 5 and 6 are now planned for removal. V² packages affected:
fuse-umfuse-ext2, vdetelweb.

### TODO:
  * purelibc: FTBFS still pending a FTBFS error for riscv64

  * vuos: fix module/submodule install path to support multi arch. To be packaged
  * fusefatfs: to be packaged (after vuos?)
  * vufusearchive: to be packaged (after vuos).
  * libnlq: docs/man missing, to be packaged

  * nsutils? change cmdline syntax? convert from autotools to cmake. Is this meaningful in Debian? compare with lsns

### packaged projects 

#### Debian stable/Bullseye
  * vdeplug4
  * cado
  * vdens
  * libvdeplirp
  * libvdestack
  * strcase
  * userbindmount
  * libvolatilestream
  * libfduserdata
  * libstropt
  * nlinline
  * randmac
  * libpam-net
  * umps3
  * libexecs 
  * vdeplug-slirp
  * vdeplug-vdesl
  * vdeplug-vlan
  * vdeplug-agno
  * vdeplug-pcap
  * libexecs 

<!--
#### Debian testing/SID
-->

### purelibc
purelibc 1.0.3 is in sid and testing. Some work must be done to port on some architectures.
NEW: faccessat emulation added. NEW: the compatibility problems for x32 should have been fixed.

Note: can enter experimental only as it needs vdeplug4

## Open Suse
[... add status here]

## Arch
[... add status here]

## Not yet ready for packaging:

### libnlq
doc is still missing

### vuos
freeze a stable relase for packaging.

### vxvdex
still too experimental

### nsutils
could be packaged, it is a useful tool.

## Bleeding edge of developing

### fuse modules

### lwip new

### picox

### dnsutils

### mutli-arch support for vuos modules

## Design stage

### new vde\_switch

### new vde\_wirefilter

### new vdetelweb

### lwip/lwipv6 convergence
