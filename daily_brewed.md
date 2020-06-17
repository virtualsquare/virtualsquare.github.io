Daily brewed Debian disk images for VirtualSquare
=====

From this page it is possible to download disk images for Qemu/KVM ready to run
virtual machines suitable for VirtualSquare experimentation.

This images provide an updated Debian SID installation including:

* `root` user access (password `virtualsquare`)
* in root's home directory: `get_v2all` script. It downloads and installs all the 
packages needed by the V2 projects as well as
it gets, builds and installs all the V2 projects at their latest version
* a user account `user` (password `virtualsquare`)

You can download the latest images from here:

 * [daily images](daily_brewed/daily.html)
 * [weekly images](daily_brewed/weekly.html)
 * [monthly images](daily_brewed/monthly.html)

Images has names like:
```
debian-sid-v2-amd64-daily-YYYYMMDD-NNN.qcow2.bz2
```
where YYYYMMDD is the image creation date and NNN is the sequence number. e.g.
```
debian-sid-v2-amd64-daily-20200610-292.qcow2.bz2
```
is  the image #292 generated on June 10th 2020.

Further explanation on how to use these images to run a tutorial on the VirtualSquare projects
can be found in [this](tutorials/setup_the_vm.md) page.

This service has been implemented using the 
[freshly brewed VirtualSquare](https://github.com/virtualsquare/freshly_brewed_virtualsquare)
project. Interested users can generate their images themselves using this project.
