## News

new: libpam-net ad umps3 are in Debian unstable.

----

new: vde-2 new packet is in Debian unstable. Now vdeplug4 can move from experiemntal to unstable.

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
  * vde-2: close the bug #965872 (Removal of obsolete debhelper compat 5 and 6). debhelper compat is 10.
  * fuse-umfuse-ext2, vdetelweb: update debhelper
  * vdeplug4: promote from experimental to sid/unstable
  * purelic: FTBFS the latest version on GITHUB should fix the remaining incompatibilities
  * fuse-umfuse-iso9660:  FTBFS. libumlib is a requirement (in debian/control and configure.ac but it seems it is not needed at all. please ck).
  * libvpoll-eventfd on salsa is ready to be submitted in new for SID
  * vdeplug_slirp, vdeplug_vdels, vdeplug_vlan, vdeplug_agno can be packaged 
  * libexecs: move to the set of virtualsquare team packages

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
  * randmac
  * libpam-net
  * umps3

#### in Debian stable
  * libexecs (move to virtualsquare team)

### vdeplug4
Note: still in experimental, waiting to be promoted to unstable.

### purelibc
purelibc 1.0.3 is in sid and testing. Some work must be done to port on some architectures.
NEW: faccessat emulation added. NEW: teh compatibility problems for x32 should have been fixed.

### vdeplug\_slirp, vdeplug\_vdesl, vdeplug\_vlan
Ready to be packaged.

Note: can enter experimental only as it needs vdeplug4

### libvpoll-eventfd
Packaged. Some checks needed for the kernel module. Almost ready for the NEW queue.

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

### mutli-arch support for vuos modules

## Design stage

### new vde\_switch

### new vde\_wirefilter

### new vdetelweb

### lwip/lwipv6 convergence
