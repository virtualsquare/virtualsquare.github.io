About the Tutorials
======

A tutorial is a journey, a course build on experiments that can be
replicated by the interested readers.

This tutorial aims to be a simple way to understand the potentialities
of many virtualsquare projects.

A tutorial is not a manual and does not introduce all the available options
and details of the tools. The reader can refer to the [man pages](#!/man/index.md)
for a detailed description of each command or API.

Users may download, configure and install all the software components they need to run the experiments here
described. We have tried to make this phase as simple as possible providing two ways to set up
a complete environment, i.e. two procedures to install all the virtualsquare tools needed. 

The two scenarios are:

* [Run the tutorial in a virtual machine.](setup_the_vm.md)
* [Install all the required software on a Debian/Sid host.](setup_a_host.md)

The Virtual machine approach is the less _invasive_ option. It requires a hosting system powerful
enough to run `kvm` and an appropriate amount of available primary and secondary memory available.
The disadvantage of this approach is that the virtual services provided by VirtualSquare will be
implemented upon another layer of virtualizaition. This may impact on the performance.

The second option provides a more realistic environment for the exercises of the tutorial.
If you have one spare `x86_64` host (or even two or more) than can be dedicated to the tutorial,
install on it (them) a clean Debian/Sid. There are scripts available to install all the Debian
packages and the Virtualsquare tools required for this Tutorial (as explained in the
["How to set up a host for the tutorials"](setup_a_host.md) page).

All the code of the projects will be installed at the latest
version available on the development repositories.

We will do our best to update this tutorial to keep the consistency with the code. Should you
find difficulties or errors, please let us know [by mail](/contacts.md), Thank you in advance.
