How to set up the Virtual Machine for the tutorials.
======

## step 0: check if kvm is installed

If qemu or kvm is not installed refer to your distribution on how to add it.

In case of Debian or Debian derivatives (like Ubuntu):

```
apt-get install qemu-kvm
```

## step 1: download the disk image 

Download it from [http://www.cs.unibo.it/renzo/virtualsquare/tutorial/](http://www.cs.unibo.it/renzo/virtualsquare/tutorial/).

It is approximately 0.8GB.

## step 2: run the VM

We suggest the following command:

```
kvm -smp 8 -drive file=v2tutorial.img,format=raw -m 1G -monitor stdio -net user,hostfwd=tcp::2222-:22 -net nic
```

The number of cores (``-smp 8``) and the amount of memory (``-m 1G``) should be adapted to your environment.

## step 3: log in as root

the password is ``virtualsquare``

## step 4: download the latest install scripts

run:
```
./wget_install_scripts
```
This script gets the latest versions of the scripts for the steps 5 and 6 here below.

## step 5: install the required debian packets

run:
```
./install_packets_for_v2.sh
```

This script downloads and installs several debian packets needed by the virtualsquare projects.
This operation may require some minutes (the actual time needed depends on the bandwidth of your internet 
connection and the performance of your processor).

## step 6: install the VirtualSquare projects

run
```
./install_v2_projects.sh
```

This script downloads the source code of the projects from the repositories, it compiles and installs
all the VirtualSquare tools required for the tutorials.
This operation may require some minutes (the actual time needed depends on the bandwidth of your internet 
connection and the performance of your processor).
now you can logout as root.

```
logout
```

## step 7: login as _user_

Type `user` at the login prompt, the password is `virtualsquare`

## step 8: The VM is ready!

Now you can choose the tutorial experiment you like from the menu and run it.

... when you have completed your experiments:

## step 9: shut down the VM

type:

```
sudo poweroff
```

# Next time

Now the VM and all the VirtualSquare tools have been installed.

When you want to try more tutorial experiments you can run just the following steps:

* step 2: run the VM
* step 7: login as _user_
* step 8: The VM is ready!
* step 9: shut down the VM
