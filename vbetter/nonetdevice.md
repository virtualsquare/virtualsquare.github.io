netdevice is obsolete
====

# The problem

Linux provides two ways to configure netowrk links, addresses, routes etc:
`netdevice` and `netlink`. (rtnetlink).

`netdevice` is the ancient (and obsolete) way. it is based on `ioctl`(2).
Many features are limited to IPv4 and do not support IPv6.
`netdevice`'s `ioctl` requests can be used on any
socket's file descriptor regardless of the family or type.

`AF_NETLINK` is a family of protocols, and `rtnetlink` is the protocol of `netlink`
designed for network configuration.
All the features providded by `nedevice` can be implemented using `rtnetlink` messages
whilst the language of `rtnetlink` is far more powerful in terms of options and
flexibility.

The current version of `glibc` uses a mix of `netdevice` and `netlink`.
e.g. the implementation of `if_nametoindex`uses `netdevice` (specifically the
		`SIOCGIFINDEX` ioctl request) while `if_nameindex` uses `rtnetlink` (a message of type
			`RTM_GETLINK` with flag `NLM_F_DUMP`).

It is a waste of resources to maintain two different support for the same service.

This makes harder to design virtual networking services, as both supports must be
provided.

Moreover glibc uses `AF_UNIX` sockets for `netdevices`'s `ioctl`s.
This works but it is inconsistent. `AF_UNIX` sockets have nothind to do with
networking, they are just Inteer Process Communication means.

This is the strace of `if_nametoindex("eth0");`
```
socket(AF_UNIX, SOCK_DGRAM|SOCK_CLOEXEC, 0) = 3
ioctl(3, SIOCGIFINDEX, {ifr_name="eth0", }) = 0
close(3)                                = 0
```

`umvu` support for virtual TCP-IP networking is based on the virtualization of sockets
for the families `AF_INET`, `AF_INET6`, `AF_PACKET` and `AF_NETLINK`.
We had to add a dirty workaround to support glibc's `netdevice` requests.
All ioctls are captured and interpreted as netdevice requests if the request TAG
matches.

# Workaround

Libnlq provides a set of drop-in replacement functions for those based on ioctl in glibc.

Libnlq provides a server side support which translates ioctl requests in netlink.

We are working on user-space networking stacks (e.g. picox-tcp). We will support netlink only.

# Please

... update glibc converting all the code to use netlink instead of netdevice.
At least use `AF_INET` (or `AF_PACKET`, or `AF_INET6`) for netdevice, please avoid
`AF_UNIX`.

# Links

* [libnlq](https://github.com/virtualsquare/libnlq)
* [Request to opensock](https://patchwork.ozlabs.org/patch/804504/)

