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
purelibc 1.0.2 is in sid and testing. SOme work must be done to port on some architectures.

### vdeplug\_slirp, vdeplug\_vdesl, vdeplug\_vlan
Ready to be packaged.

Note: can enter experimental only as it needs vdeplug4

### libpam-net
Packaged. Need some final checks and can enter the NEW queue.

### libvpoll-eventfd
Packaged. Some checks needed for the kernel module. Almost ready for the NEW queue.

### lwipv6 (old)
There is ftbfs with glibc-2.31 (doko). `lwipv6_1.5a-6` is going to be upladed.

### randmac
Packaged, ready for NEW

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
