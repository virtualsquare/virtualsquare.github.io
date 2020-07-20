qemu/kvm: all interfaces have the same default MAC
=====

# The problem

Qemu/Kvm does not provide a way to generate random MAC addresses for the netwrking interfaces of the virtual machines.

The first interface has the default MAC address `52:54:00:12;34:56` while the second ``52:54:00:12;34:57` and so on.

It is possible to set different mac addresses using specific flags on the command line.
e.g.:

```
qemu-system-x86_64 -enable-kvm ... \
		-device e1000,netdev=vde0,mac=52:54:00:00:00:02 -netdev vde,id=vde0,sock=vxvde://
```

In order to start several concurrent virtual machines in the same virtual network care must be taken not to give the same MAC address to
several virtual interfaces.

# Workaround

The simple tool `randmac` returns random MAC addresses.

```
$ randmac 
ca:7b:94:11:f8:e7
```

`randmac` has several options, for example it is possible to select the oui (vendor id).
For example `randmac -q` generates a qemu-like MAC address (oui=`52:54:00`)

So it is possible to use randmac in the qemu-kvm command:

```
qemu-system-x86_64 -enable-kvm ... \
		-device e1000,netdev=vde0,mac=$(randmac -q) -netdev vde,id=vde0,sock=vxvde://
```

# Please
... add an option to set random mac addresses to qemu/kvm virtual host interfaces.

# Links

* [randmac on GitHub](https://github.com/virtualsquare/randmac)
* [Qemu networking documentation](https://wiki.qemu.org/Documentation/Networking)

