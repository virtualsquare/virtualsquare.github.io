Local Area Cloud
====

what
----
The scenario is a set of host computers connected by a Local Area Network (LAN).
A Local Area Cloud (LAC) is a virtual network. Virtual Machines, Namespaces or [IoTh](ioth.md) processes 
can be connected directly to the LAC. They do not need any specific infrastructure or configuration on the hosting computer.

All Virtual Machines, Namespaces or [IoTh](ioth.md) processes using the same LAC address communicate on the same virtual (VDE) network.

Process or VM migration is as simple as stopping the program on one host and restarting on the other.

why
----
Because LACs are very convenient, flexible and fast.

It is a very effective support for the idea of [Internet of threads](ioth.md). Processes (or virtual machines or namespaces) can run
on any host of the LAN. They will use their own IP address to communicate.

how
----
vxvde implements Local Area Clouds. vxvde creates a distributed virtual switch,
All the virtual machines, namespaces or IoTh processes on the same LAC bind the same IP multicast address of the real network.
Broadcast, multicast packets as well as packets addressed to unknown receipients sent on the LAC are delivered using the IP
multicast address from a socket bound to a unicast socket, so it is received by all the LAC nodes.
When a packet is received, the sender's MAC address can be paired with the IP address and port of the sender on the real network
and stored in a hash table (similarly to what happens in an ethernet switch device where a hash table stores
		the pairing between MAC addresses and physical port numbers).

Unicast packets sent on the LAC to already known MAC addresses are sent as UDP unicast packets to the
IP address and port stored in the hash table.

where
----

Qemu of Kvm virtual machines can join a vxvde LAC using the following parameters:
```
qemu-system-x86_64 .... -net nic,macaddr="52:54:....." -net vde,sock=vxvde://239.0.0.1
```
(each vm must be given a different MAC address otherwise qemu assigns the same to all)

vdens can start a namespace connected to a LAC:
```
vdens vdens vxvde://239.0.0.1
```

All the virtual machines and namespaces started 
as explained here above 
on random hosts of the local area network 
will be connected to the same virtual (VDE) network (identified by the multicast address 239.0.0.1).

references:
----
R. Davoli and M. Goldweber, [_VXVDE: A Switch-Free VXLAN Replacement_](https://ieeexplore.ieee.org/document/7414109) 2015 IEEE Globecom Workshops (GC Wkshps), San Diego, CA, 2015, pp. 1-6.
