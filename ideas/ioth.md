Internet of Threads (IoTh)
====

what
----
Processes and even threads can be the endpoints of Internet connections.

In other words IP addresses should be given to processes, because they are addressing services.

why
----
Because people are interested in services, it does not matter which computer is currently hosting
that service.

Using IP addresses assigned to hardware network controllers is as obsolete as using telephone fixed lines.
Portable phones are very convenient because they _address_ people, fixed lines _point_ to geographical
places. 

how
----
processes (or groups of processes) must have their own networking support. There are two methods:
kernel provided namespaces or networking stacks implemented as user-space libraries.

where
----
Several projects in VirtualSquare implement the idea of IoTh:

* [vdens](https://github.com/rd235/vdens): create namespaces where services can have their own IP addresses
* [libvdestack](https://github.com/rd235/libvdestack): use a networking thread to provide a process with its own netowrkign support (using kernel namespaces)
* [lwipv6](https://github.com/virtualsquare/view-os/tree/master/lwipv6): (codebase to be updated): an entire TCP-IP stack running in user-space

references:
----
Renzo Davoli, _Internet of Threads: Processes as Internet Nodes_, in International Journal on Advances in Internet Technology, 2014, 1-2, pp. 17 - 28
