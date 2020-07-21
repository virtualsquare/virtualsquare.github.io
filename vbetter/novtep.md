VXLAN's VTEP is a bottleneck
====

# The problem

Virtual Extensible LAN (VXLAN) is a networking virtualization method. It
uses ethernet frames encapsulation in IP multicast and unicast packets.

All the VM running on a host use a VXLAN tunnel endpoint (VTEP) deamon as a L2
switch and gateway.

So all the packets exchanged between virtual machines need to be dispatched by the VTEPs, this adds
delay and requires processing power.

# A better solution

Virtual Machine Monitors can open unicast and multicast connections by themselves.
In other words, VMM can have their embedded VTEP.

VXVDE implements his idea. All the packets exchanged between virtual machines are directly exchanged 
between the VMMs.
VXVDE implements a distributed ethernet switch. It needs almost no configuration to run: just the multicast IP address and port.

# References

[VXLAN: RFC 7348](https://www.rfc-editor.org/info/rfc7348)

[vxvde is part of vdeplug4](https://github.com/rd235/vdeplug4.git)

Renzo Davoli; Michael Goldweber, *VXVDE: A Switch-free VXLAN Replacement* in Proceedings of 2015 Globecom workshops
