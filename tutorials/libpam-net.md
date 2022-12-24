libpam-net
====

Note: This tutorial requires that [libpam-net](https://github.com/rd235/libpam-net)
has been already installed in the system. If you have followed the [startup of this
tutorial](intro.md), `libpam-net` is already available.

## Create a net-less user

Log-in as root, Add a user namer `usernonet`.
```
# # adduser usernonet
Adding user `usernonet' ...
Adding new group `usernonet' (1002) ...
Adding new user `usernonet' (1002) with group `usernonet' ...
Creating home directory `/home/usernonet' ...
Copying files from `/etc/skel' ...
New password:
Retype new password:
passwd: password updated successfully
Changing the user information for usernonet
Enter the new value, or press ENTER for the default
        Full Name []:
        Room Number []:
        Work Phone []:
        Home Phone []:
        Other []:
Is the information correct? [Y/n] y
```

Create a group named `newnet` including the new user `usernonet`.
i.e. add the following line to `/etc/grooup`.
```
newnet:x:149:usernonet
````

Now configure PAM to test for the `libpamnet` module named `pam_newnet.so`.
i.e. add the following line at the end of /etc/pam.d/sshd
```
session   required  pam_newnet.so
```

Now log-in to the system as `usernonet` by ssh. In case you are using the virtual machine:
```
$ ssh -p 2222 usernonet@localhost
usernonet@localhost's password:
Linux V2-20200620-303 5.7.0-2-amd64 #1 SMP Debian 5.7.10-1 (2020-07-26) x86_64
...
$ ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host
       valid_lft forever preferred_lft forever
$
```

This user has only the localhost interface available. This user logged in to the
system by the network (via ssh) but it is not possible to use the network from the
resulting session.
