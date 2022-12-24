Internet of Threads
====

[Internet of Threads (IoTh)](/ideas/ioth.md) means the ability to give the role of Internet nodes to
processes or even to threads.

A process can have its own IP address. While this idea sounds hardly exploitable in IPV4 due to the scarcity of
addresses, it is a convenient usage of the wide IPV6 address space.

The combination of this concept with VDE, the network namespaces (`vdens`) and local area clouds (`vxvde`)
shows the high flexibility of the overall design. A server process (a networking daemon) owning its address
can migrate across the hosts of the local area network: no reconfiguration is needed neither for the
networking infrastructure, operating system support nor even name resolution.

_This section of the tutorials is for programmers_

A TCP-IP stack can be implemented as a library. In fact a TCP-IP stack implements the
_link_, _internetwork_ and _transport_ layers. A TCP-IP stack provide connection-oriented
(TCP) or connectionless (UDP) communications, sending and receiving packets of a
physical (or virtual) network.

![ioth idea](pictures/iothidea.png)

The picture here above compares the legacy implementation of TCP-IP stacks (on the left)
and the IoTh (on the right).

The legacy model is based on the idea that the network stack must be unique and provided
by the kernel. This implementation protects the physical network from abuses.

IoTh instead has a completely opposite approach, each process can use one or more
network stacks implemented as libraries, users can own and manage their virtual networks.

Note: ![wip](pictures/wip.png) we are working to support user-level stacks. We are
evaluating the porting of
[lwip](https://savannah.nongnu.org/projects/lwip/) and our old
[lwipv6](https://github.com/virtualsquare/view-os/tree/master/lwipv6)
