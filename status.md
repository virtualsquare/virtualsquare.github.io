## News

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
fuse-umfuse-ext2, fuse-umfuse-fat, lwipv6, umview, vdetelweb. vde2: the new package
waiting in the NEW queue for 8 monthes would solve the compat problem.

Note: we worked on a v2util package including all the small projects (mainly utility
libraries). Given the experience on complex projects waiting in the WAIT/BYHAND queue
it is more effective to propose one package per project.

### packaged projects 
#### Debian unstable/testing
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

#### in Debian stable
  * libexecs (move to virtualsquare team)

### vde2
Attention: we are still waiting the new packet to leave the NEW-BYHAND queue (*six monthes!*)

This is a bottleneck for us, `vdeplug4` cannot migrate from experimental to unstable,
and all the other plugs we can package has to wait in experimental.

### vdeplug4
Note: still in experimental, it collides with current vde2 on unstable

### purelibc
purelibc 1.0.2 is in sid and testing. Some work must be done to port on some architectures.
NEW: faccessat emulation added. Debian package needs to be updated.

### libstropt:
NEW: there is bugfix (on GITHUB). Debian package needs to be updated.

### libpam-net
Packaged. in the NEW queue.for sid

### randmac
Packaged, in the NEW queue for sid

### umps
Packaged: it should be ready for the NEW queue

### vdeplug\_slirp, vdeplug\_vdesl, vdeplug\_vlan
Ready to be packaged.

Note: can enter experimental only as it needs vdeplug4

### libvpoll-eventfd
Packaged. Some checks needed for the kernel module. Almost ready for the NEW queue.

### libvdeplug\_vdesl:
Ready to be packaged.

## Open Suse
[... add status here]

## Arch
[... add status here]

## Not yet ready for packaging:

### libnlq
doc is still missing

### vuos
freeze a stable relase for packaging.

### vdeplug\_agno
need porting to cmake and review.

### vxvdex
still too experimental

### nsutils
could be packaged, it is a useful tool.

## Bleeding edge of developing

### fuse modules

### lwip new

### picox

### dnsutils

## Design stage

### new vde\_switch

### new vde\_wirefilter

### new vdetelweb

### lwipv6 convergence
