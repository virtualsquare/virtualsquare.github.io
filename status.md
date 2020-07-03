## News

New vde\_plug: `vdesl`.

This vde\_plug creates a virtual point to point ethernet link over a serial line.

Example: connect the uart ports of two Raspberry PI boards (GND-\>GND, TXD-\>RXD, RXD-\>TXD).

The following command (on both RasPIs):
```bash
       sudo vde_plug -d tap://vdesl0 vdesl:///dev/ttyAMA0[speed=4000000]
```

creates a 4Mbps ethernet link connecting the two `vdesl0` interfaces.

## Debian

Note: we worked on a v2util package including all the small projects (mainly utility
libraries). Given the experience on complex projects waiting in the WAIT/BYHAND queue
it is more effective to propose one package per project.

### packaged projects (new)
  * cado
  * vdens
  * libvdeplirp
  * libvdestack
  * vdens
  * libexecs (move to virtualsquare team)

### vde2
Attention: we are still waiting the new packet to leave the NEW-BYHAND queue (*six monthes!*)

This is a bottleneck for us, `vdeplug4` cannot migrate from experimental to unstable,
and all the other plugs we can package has to wait in experimental.

### vdeplug4
Note: still in experimental, it collides with current vde2 on unstable

### purelibc
newrepo on github, the code has been ported to cmake, this is ready to be packaged, it should *not* need to enter the NEW-BYHAND queue as it is just an update of an existing package

### vdeplug\_slirp, vdeplug\_vdesl, vdeplug\_vlan
Ready to be packaged.

Note: can enter experimental only as it needs vdeplug4

### libpam-net
Ready to be packaged (check the multiple ITPs)

### strcase, userbindmount, libvolatilestream, libfduserdata, libstropt, nlinline
Ready to be packaged (split v2utils)

### libvpoll-eventfd
To be packaged: it includes a kernel module

### lwipv6 (old)
There is ftbfs with glibc-2.31 (doko)

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
