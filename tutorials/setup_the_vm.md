How to set up the Virtual Machine for the tutorials.
======

## step 0: check if kvm is installed

If qemu or kvm is not installed refer to your distribution on how to add it.

In case of Debian or Debian derivatives (like Ubuntu):

```
apt-get install qemu-kvm
```

## step 1: download the disk image 

Download the latest [Daily brewed Debian disk images for VirtualSquare](/daily_brewed.md).

It is approximately 0.45GB.

## step 2: uncompress the image:

```bash
$ bunzip2 debian-sid-v2-amd64-daily-????????-???.qcow2.bz2
```

question marks should be changed with the actual date and version number of the disk image.
e.g.:

```bash
$ bunzip2 debian-sid-v2-amd64-daily-20200528-277.qcow2.bz2
```


## step 3: run the VM

We suggest the following command:

``` bash
$ qemu-system-x86_64 -enable-kvm -smp $(nproc) -m 2G -monitor stdio -cpu host\
    -netdev type=user,id=net,hostfwd=tcp::2222-:22 -device virtio-net-pci,netdev=net \
    -drive file=$(echo debian-sid-v2-amd64-daily-????????-???.qcow2)
```

The number of cores (``-smp $(nproc)``) and the amount of memory (``-m 2G``) should be adapted to 
your environment. (This command uses all the cores available in the hosting computer -- the output of the `nproc` command).
It is possible to name the actual file name including the date and version number in this way:

``` bash
$ qemu-system-x86_64 -enable-kvm -smp $(nproc) -m 2G -monitor stdio -cpu host\
    -netdev type=user,id=net,hostfwd=tcp::2222-:22 -device virtio-net-pci,netdev=net \
    -drive file=debian-sid-v2-amd64-daily-20200611-294.qcow2
```

## step 4: log in as root

the password is ``virtualsquare``

## step 5: run the `get_v2all` script

This command installs all the packets needed by the virtualsquare projects and then downloads, builds and installs all the latest versions of the projects directly from the development repositories.

``` bash
# ./get_v2all
```

This operation may require some minutes (the actual time needed depends on the bandwidth of your internet 
connection and the performance of your processor).
now you can logout as root.

```
logout
```

## step 6: login as _user_

Type `user` at the login prompt, the password is `virtualsquare`

## step 7: The VM is ready!

Now you can choose the tutorial experiment you like from the menu and run it.

... when you have completed your experiments:

## step 8: shut down the VM

type:

```
sudo poweroff
```

# Next time

Now the VM and all the VirtualSquare tools have been installed.

When you want to try more tutorial experiments you can run just the following steps:

* step 3: run the VM
* step 6: login as _user_
* step 7: The VM is ready!
* step 8: shut down the VM


### Note:
Images before June 17, 2020 may use `virtualsquare` instead of `user` as login name in step 6.
