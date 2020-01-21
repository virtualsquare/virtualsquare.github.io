the mount command is a *censor*
====

# The problem

The standard utility `mount`(8) as  well as the `mount` applet of busybox
deny the mount operation if the `euid` of the caller is not root.

Both tools do not run the `mount`(2) system call if started by a user 
(if there is the `-t` option).

Why? This is not a security feature, it is the system call which has to deny
the access to privileged operations. Any limitation based on checks in user
space code is easily circunventable by writing another program.

In the contrary this miopic implementation choice make `mount` unsuitable for
virtual mount in `umvu`.

The output of `mount` is:
```bash
$ mount -t vufuseext2 /tmp/linux.img /mnt
mount: only root can use "--types" option
```

instead `busybox mount` returns:
```bash
$ busybox mount -t vufuseext2 /tmp/linux.img /mnt
mount: permission denied (are you root?)
```

# Workaround

We had to implement a more *permissive* mount:
```
$ vumount -t vufuseext2 /tmp/linux.img /mnt
```
`vumount` can be used instead of `mount` (but it has less options).

Alternatively it if possible to *fake* root and use the standard tools:
```
$ vu_insmod unrealuidgid
$ vusu -
# mount -t vufuseext2 /tmp/linux.img /mnt
```

# Please

...avoid unnecessary preventive checks. Let the system calls do their job and decide
what is permitted and what is denied. 
