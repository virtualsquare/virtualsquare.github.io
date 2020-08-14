VUOS virtual `chroot`
====

`chroot` is implemented by the hypervisor (`umvu`).

## Run a GNU-Linux distribution in a `chroot` environment.

First of all download the distribution. In this example we'll use the 
_MINI ROOT FILESYSTEM_ of [Alpine Linux](https://www.alpinelinux.org/downloads/).
```
$$ wget http://dl-cdn.alpinelinux.org/alpine/v3.12/releases/x86_64/alpine-minirootfs-3.12.0-x86_64.tar.gz
```

Load the modules to virtualize uid/gid and ownership of files.
```
$$ vu_insmod vufs unrealuidgid
```

Create the directories for alpine and the virtual `root` home dir,
then enter the _fake_ root environment.
```
$$ mkdir /tmp/alpine /tmp/root
$$ vumount -t vufs /tmp/root /root
$$ vumount -t vufs -o cow /tmp/alpine /tmp/alpine
$$ vusu -
```

Change dir to `/tmp/alpine`, set the ownership of the mount-point,
and extract the tar archive.

```
## cd /tmp/alpine
## chown root:root .
## tar xf /home/user/alpine-minirootfs-3.12.0-x86_64.tar.gz
```
This list (`ls`) shows that the virtualization of ownership has worked properly:
```
## ls -l
total 68
drwxr-xr-x  2 root root 4096 May 29 14:20 bin
drwxr-xr-x  2 root root 4096 May 29 14:20 dev
drwxr-xr-x 15 root root 4096 May 29 14:20 etc
drwxr-xr-x  2 root root 4096 May 29 14:20 home
drwxr-xr-x  7 root root 4096 May 29 14:20 lib
drwxr-xr-x  5 root root 4096 May 29 14:20 media
drwxr-xr-x  2 root root 4096 May 29 14:20 mnt
drwxr-xr-x  2 root root 4096 May 29 14:20 opt
dr-xr-xr-x  2 root root 4096 May 29 14:20 proc
drwx------  2 root root 4096 May 29 14:20 root
drwxr-xr-x  2 root root 4096 May 29 14:20 run
drwxr-xr-x  2 root root 4096 May 29 14:20 sbin
drwxr-xr-x  2 root root 4096 May 29 14:20 srv
drwxr-xr-x  2 root root 4096 May 29 14:20 sys
drwxrwxrwt  2 root root 4096 May 29 14:20 tmp
drwxr-xr-x  7 root root 4096 May 29 14:20 usr
drwxr-xr-x 12 root root 4096 May 29 14:20 var
```

Now we are ready to start the `chroot`-ed environment.
```
## chroot /tmp/alpine /bin/sh
/ # cat etc/alpine-release 
3.12.0
```

VUOS has created a virtual chroot environment.
```
/ # ls -l /
total 68
drwxr-xr-x    2 root     root          4096 May 29 14:20 bin
drwxr-xr-x    2 root     root          4096 May 29 14:20 dev
drwxr-xr-x   15 root     root          4096 May 29 14:20 etc
drwxr-xr-x    2 root     root          4096 May 29 14:20 home
drwxr-xr-x    7 root     root          4096 May 29 14:20 lib
drwxr-xr-x    5 root     root          4096 May 29 14:20 media
drwxr-xr-x    2 root     root          4096 May 29 14:20 mnt
drwxr-xr-x    2 root     root          4096 May 29 14:20 opt
dr-xr-xr-x    2 root     root          4096 May 29 14:20 proc
drwx------    2 root     root          4096 Aug 13 19:23 root
drwxr-xr-x    2 root     root          4096 May 29 14:20 run
drwxr-xr-x    2 root     root          4096 May 29 14:20 sbin
drwxr-xr-x    2 root     root          4096 May 29 14:20 srv
drwxr-xr-x    2 root     root          4096 May 29 14:20 sys
drwxrwxrwt    2 root     root          4096 May 29 14:20 tmp
drwxr-xr-x    7 root     root          4096 May 29 14:20 usr
drwxr-xr-x   12 root     root          4096 May 29 14:20 var
/ # sh --help
BusyBox v1.31.1 () multi-call binary.

Usage: sh [-/+OPTIONS] [-/+o OPT]... [-c 'SCRIPT' [ARG0 [ARGS]] / FILE [ARGS] / -s [ARGS]]

Unix shell interpreter
/ #
```
