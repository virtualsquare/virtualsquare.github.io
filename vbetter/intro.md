We do V better
====

VirtualSquare tools can be seen as general purpose solutions,
Features currently provided by other projects can be regarded as
VirtualSquare use cases.

* [fakeroot](http://freshmeat.sourceforge.net/projects/fakeroot) vs.
[V² fakeroot](/tutorials/vu_uidgid.md#the_vuos_way_to_fakeroot):
It is implemented by VUOS, integrated with virtual file systems, virtual devices:
fake (or virtual) special file can have actual virtual drivers.
* [fakechroot](https://github.com/dex4er/fakechroot) vs. [V² fakechroot](/tutorials/vu_chroot.md):
It is integrated in VUOS' core hypervisor. There is no need to re-implement large chunks
of the glibc specifically for faking chroot.
Based on `ptrace`, in V² implementation it is (a bit) harder to exit from the _sandbox_.
* [slirp4netns](https://github.com/rootless-containers/slirp4netns).
vs [vdens + slirp plug-in](http://localhost:8000/#!tutorials/vde_slirp.md):
It is just a basic applicaiton of `vdens`. The syntax of `vdens` is simpler and
`vdens` enables many other uses of slirp. e.g. it is possible to create a
namespace providing user-mode networking
[of a remote host](tutorials/vde_slirp.md#A_foreign_namespace).
* [fuse](https://github.com/libfuse/libfuse) vs. [V² vufuse](/tutorials/vufuse.md):
V² implementation does not need any kernel support. The _visibility_ of the
mounted file system is limited to the processes running in the VUOS session.
* [overlay filesystem](https://www.kernel.org/doc/html/latest/filesystems/overlayfs.html?highlight=overlayfs)
vs. [V² vufs](/tutorials/vufs.md): vufs is entirely implemented in user space,
`vufs` supports many different merging abstractions: _merge_, _cow_, _mincow_.
* [libguestfs](https://www.libguestfs.org/) is a set of tools for accessing and modifying virtual machine (VM) disk images. [V² vudev](/tutorials/vudev.md) and [V² fuse](/tutorials/vudevfuse.md) implement the features of libguestfs as an application scenario of a wider virtualization infrastructure using a simpler syntax.
