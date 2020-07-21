IP multicast supports only one server per IP address
====

# The problem

An IP multicast *channel* is defined by a muticast IP address and a port.
(e.g. 239.0.0.1:4789).

A process uses the standard sequence to join a multicast channel: it opens a socket and binds it to the multicast address and port.

The problem is that when a process uses the multicast socket to send a packet the source port number and the destination
port number are the same in the packet (usually UDP) headers.

So, if there are two or more processes running one the same host and connected to the same IP multicast channel it is not possible
to distinguish which process actually sent a packet.

It is clear that the design of IP multicast support was based on the idea of a few servers and many clients, not a real peer to peer
multicast interaction.

# Workaround

This problem arose during the implementation of vxvde.

The workaroud consists of two sockets:

* a multicast IP socket, used to receive multicast packets
* a unicast socket, used to send both unicast and multicast packets.

In this way when a host receives a multicast packet it is possible to distnguish which is the sender and it is possible to send
unicast replies.

The drawback of this method is that each process receives a copy of the multicast packets it sends, vxvde implements
workarounds to skip the self received packets.

# Please

...design a way to create ip multicast sockets using tha group port number to receive packets and another port (maybe an ephemeral port) for sending.

# References

[vxvde is part of vdeplug4](https://github.com/rd235/vdeplug4.git)

Renzo Davoli; Michael Goldweber, *VXVDE: A Switch-free VXLAN Replacement* in Proceedings of 2015 Globecom workshops
