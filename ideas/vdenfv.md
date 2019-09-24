network function virtualization squared
====

what
----
Once upon a time there were physical networking devices named _switches_, _gateway_, _routers_, ...

Then the _Network Function Virtualization_ (NFV) arrived and network function were deployed on general
purpose standadized hardware.

VDE allows one more layer of virtualization: network functions can run on namespaces ([NoN](non.md).

why
----
Because in [Local Area Cloud](lac.md) environments where virtual machines, namespaces, [Internet of Thread](iot.md)
processes can be deployed on any of the physical hosting computers, the network functions must be
cloud-ized as well.

how
----
A [VDE namespace](https://github.com/rd235/vdens) (using `--multi`) can be connected to several [VDE plugs](https://github.com/rd235/vdeplug4):
it this way it has several virtual interfaces connected to seveeral virtual (or real) networks.

e.g.
```bash
vdens --multi vxvde://239.1.2.3 vxvde://239.1.2.4 vde:///var/run/vde.ctl tap://tapx
```
Inside the new namespace there will be four virtual interfaces `vde0, vde1, vde2, vde3` connected to the 
four plugs, `vde0` to the vxvde whose IP multicast address is 239.1.2.3 and so on.

All the tools for NFV designed for Linux hosts can run in a VDE namespace. Some simple examples include the kernel bridge or
routing daemons like Zebra or Quagga.

where
----
The support is provided by [vdens](https://github.com/rd235/vdens).
Actually, the VDE namespace provides just the support for several VDE plugs the same time.
Network functions virtualization software runs in the namespace as it would run on the bare O.S.
(except from the fact that root access or specific capabilities are not required to manage and run NFV user namespaces).

references:
----
Renzo Davoli, _NFV à la VDE way_ Presentation at [FOSDEM 2018](https://archive.fosdem.org/2018/schedule/event/vde/)
