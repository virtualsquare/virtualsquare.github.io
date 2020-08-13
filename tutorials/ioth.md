Internet of Threads
====

[Internet of Threads (IoTh)](/ideas/ioth.md) means the ability to give the role of Internet nodes to
processes or event to threads.

A process can have its own IP address. While this idea sounds hardly exploitable in IPV4 due to the scarcity of
addresses, it is a convenient usage of the wide IPV6 address space.

The combination of this concept with VDE, the network namespaces (`vdens`) and local area clouds (`vxvde`)
shows the high flexibility of the overall design. A server process (a networking daemon) owning its address
can migrate across the hosts of the local area network: no reconfiguration is needed neither for the
networking infrastructure, operating system support nor even name resolution.

_This section of the tutorials is for programmers_
