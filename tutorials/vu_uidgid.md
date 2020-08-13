VUOS virtual user/group ids
====

The module `unrealuidgid` implements the virtualization of user and group identification.

Once the module is loaded it is possible to pretend to be root or any other user.

## the vuos way to fakeroot

The following sequence of commands starts a shell which fakes root privileges.
The key command is `vusu`.
```bash
$$ vu_insmod unrealuidgid vufs
$$ mkdir /tmp/root
$$ vumount -t vufs /tmp/root /root
$$ vusu
## whoami
root
##
```
Note: The commands `mkdir /tmp/root` and `vumount -t vufs /tmp/root /root` create
a virtual home directory for the `root` user. This operation is not strictly needed for
`vusu`; if skipped `bash` just complains that some startup files are not accessible
(`bash: /root/.bashrc: Permission denied`) but the operation succeeds.
Without a virtual home directory some features of bash are disabled, e.g. the command
history.

Note: the command prompts might be different. 
The prompt `## ` as shown in the example for the `vusu` session can be configured running
the command
`echo 'PS1="\\\$\\\$ "' > /tmp/root/.bashrc`
just before `vumount`.

Warning: All the processes running in the VUOS session can see the  new _identity_ given 
by `unrealuidgid`. (system calls like `getuid`, `getgid`, `geteuid`, ecc return the
virtual identity). New files created on virtual file systems (e.g. `vufs` or `vufuse`)
will be owned by the current virtual user/group. When new files are creates on a
non-virtual area of the file system, the ownership cannot be virtualized.

## create a tar of alien files

The goal of this example is to create a `tar` file which includes files and
directories owned by root or other users/groups.

This is possible in VUOS by combining `unrealuidgid` and `vufs`

For example let us create a `tar` file containing:

* a directory `dir` owned by root
* a file `dir/rootfile` owned by root
* a file `dir/file2000 owned by the user 2000 group 4000
* an unbuffered (char) device special file `dir/device` major 42 minor 44

```
## mkdir /tmp/alientar
## vumount -t vufs -o cow /tmp/alientar /tmp/alientar
## cd /tmp/alientar/
## mkdir dir
## echo ciao > dir/rootfile
## echo 20004000 > dir/file2000
## chown 2000:4000 dir/file2000
## mknod dir/device c 42 44
## ls -l dir
total 8
crw-r--r-- 1 root root 42, 44 Aug 13 15:40 device
-rw-r--r-- 1 2000 4000      9 Aug 13 15:39 file2000
-rw-r--r-- 1 root root      5 Aug 13 15:39 rootfile
## tar zcvf /tmp/dir.tgz dir
dir/
dir/rootfile
dir/file2000
dir/device
## tar tvf /tmp/dir.tgz
drwxr-xr-x root/root         0 2020-08-13 15:40 dir/
-rw-r--r-- root/root         5 2020-08-13 15:39 dir/rootfile
-rw-r--r-- 2000/4000         9 2020-08-13 15:39 dir/file2000
crw-r--r-- root/root     42,44 2020-08-13 15:40 dir/device
## cd /tmp
## vuumount /tmp/alientar/
```
