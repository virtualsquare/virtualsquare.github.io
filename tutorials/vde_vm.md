VDE and Virtual Machines
====

This tutorial has been designed to run on a virtual machine or in a Linux box
where the virtualsquare tools have been installed as described in the previous tutorials:
[Set up the Virtual Machine](setup_the_vm.md) or [Set up a Linux host](setup_a_host) respectively.

Note: many examples require to use several virtual terminals. On a Linux Box just start several
x-terminals. No GUI has been installed in the virtual machine configured for the VirtualSquare tutorials.
It is clearly possible to install your preferite GUI (like as _gnome_, _kde_, _lxde_...).
It is also possible for the processes of the VM to have their GUIs through the X-server of the hosting computer.
If the VM has been using the commands suggested in the [_Set up the Virtual Machine_](setup_the_vm.md) 
run (on the hosting computer):
`ssh -X -p 2222 user@localhost xterm`.
The resulting `xterm` is running on the virtual machine and from there it is possible to start other virtual
terminals (`xterm &`) or other X-window clients (e.g. `qemu-system-x86_64`).


This tutorial is not meant to be a guide to implement projects based on VirtualSquare tools but
to provide users with examples to explain how to use VDE.

This tutorial uses minimal Linux distributions in the Virtual Machines of the examples and if  
the tutorial in a VM the examples will start a second layer of virtualization.

The goal here is to show how to use VDE, all the commands can be applied to more realistic
scenarios on production VM.

## Two qemu/kvm machines connected by a switch.

The architecture we want to get is depicted here below:

![qemu/kvm and a switch](pictures/qemukvm_switch.png)

### install `qemu-system-x86`

```
$ su -
# apt-get update
# apt-get install qemu-system-x86
# exit
$
```

### load a disk image for the qemu/kvm VMs

```
$ wget http://dl-cdn.alpinelinux.org/alpine/v3.12/releases/x86_64/alpine-virt-3.12.0-x86_64.iso
```
or the latest version in [Alpine Linux download page](https://alpinelinux.org/downloads/) in the section
`VIRTUAL`.

### start a VDE switch:

Open a terminal and run:
```
$ vde_plug null:// switch:///tmp/mysw
```

Note: this is a very simple switch. It does not provide remote management, vlan support, loop avoidance (fast spanning tree).
VirtualSquare provide `vde_switch` which supports all these features.

Note: The _name_ of the switch is `/tmp/mysw`. All the VDE clients using the UVDEL `vde:///tmp/mysw` will be connected
by a virtual ethernet.

### start a VDE switch:

Open two more terminals and start the qemu/kvm VMs.

Type the same command on both terminals: either the command to run qemu:
```
$ qemu-system-x86_64 -cdrom alpine-virt-3.12.0_rc5-x86_64.iso -monitor stdio \
		-device e1000,netdev=vde0,mac=$(randmac -q) -netdev vde,id=vde0,sock=vde:///tmp/mysw
```
or the command to run kvm:
```
$ qemu-system-x86_64 -enable-kvm -cdrom alpine-virt-3.12.0_rc5-x86_64.iso -monitor stdio \
		-device e1000,netdev=vde0,mac=$(randmac -q) -netdev vde,id=vde0,sock=vde:///tmp/mysw
```

Warning: nested kvm is allowed only if that feature has been enabled by a specific option of the kernel module in the hosting system
(`nested=Y` for `kvm-intel` or `nested=1` for `kvm-amd`) as described [in this page](https://www.linux-kvm.org/page/Nested_Guests).

### configure the networking of the VDE connected virtual machines

Log in as root in the two virtual machines and configure their `eth0` iterfaces.

On the first:
```
# ip addr add 10.0.0.1/24 dev eth0
# ip link set eth0 up
```

on the other:
```
# ip addr add 10.0.0.2/24 dev eth0
# ip link set eth0 up
```

Now it is possible for each VM to `ping` the other. The virtual ethernet is up and running.

