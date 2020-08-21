How to install V2 tools
====

Virtualsquare tools and libraries are currently available from their source [repositories](repos.md).
The packets currently available in Debian (stable, testing and unstable) are maintained but refer to the
old codebase.

We are currently working to create and upload new Debian packets and we are managing the smooth transition from
the old the the new packets.

The new code has many  new features and implements a lot of new [ideas](ideas/intro.md).

If you want to give a try to VirtualSquare we provides two recipes: some scripts to install V2 on a clean Debian
unstable (sid) or a tutorial disk image for qemu/kvm.

## Install V2 on Debian sid

### step one: set up the environment

Install the packets needed to compile and install all the tools from their repos.

This is the list of the packets:
```
git python3 build-essential cmake make autogen
autoconf libtool libcap-dev libattr1-dev libfuse-dev libwolfssl-dev
libexecs-dev libmhash-dev libpam0g-dev libssl-dev netcat
libfuse-dev e2fsprogs comerr-dev e2fslibs-dev xterm
udhcpc libpcap-dev libslirp-dev
```

Some more packets are userful for some tests, or include some tools which have not yet been rewritten like
the vde\_switch:

```
xterm x11-utils vim vde2 vdetelweb
```

Some tools need to define user name space. This feature is disabled by default in Debian. The commands
to enable it (permanently) are:

```bash
echo 'kernel.unprivileged_userns_clone=1' > /etc/sysctl.d/00-local-userns.conf
service procps restart
```

[install\_packets\_for\_v2.sh](/archive/install_scripts/install_packets_for_v2.sh) is a script that runs all the commands required for
this _step one_. You can run it, adapt it to your needs or simply cut/paste the commands.


### step two: install the projects

All the projects provide specific installation instructions in the README of their [repositories](repos.md).

We have set up a script named [install\_v2\_projects.sh](/archive/install_scripts/install_v2_projects.sh). It downloads, compiles and installs
a quite complete collection of VirtualSquare tools. It must run as root.

## Run a VM using the Tutorial disk

We have set up a hard disk image to boot a qemu or kvm virtual machine.

A step by step guide on how to set up a VM in this way is provided in the [tutorials](tutorials/setup_the_vm.md) section.

