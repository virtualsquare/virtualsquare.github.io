# VirtualSquare in Debian

The [Debian VirtualSquare Team](https://salsa.debian.org/virtualsquare-team) is actively working to bring new VirtualSquare projects to the Debian distribution and to update the [already available packages](https://qa.debian.org/developer.php?login=virtualsquare%40cs.unibo.it).

VirtualSquare's repositories for Debian packaging are on [Salsa](https://salsa.debian.org/virtualsquare-team).

## Structure of VirtualSquare repositories on Salsa

The repo has two types of branches: _upstream_ and _debian_ (some repos have also a _pristine-tar_ branch).

The _upstream_ branch is synchronized with the repo we use for the project development (generally on [GitHub](https://github.com/virtualsquare) for VirtualSquare's projects).

Warning: never commit changes to this branch! Changes should be proposed, tested and committed on the development repo, then exported/pushed to the packaging repo.

The _debian/sid_ branch is the default branch of the repository on Salsa (to ease the clone/buildpackage process).
This branch adds the `debian` directory to the contents of _upstream_.

We use [git tags](https://git-scm.com/book/en/v2/Git-Basics-Tagging) to label the source and Debian snapshots:
* `upstream/0.1` is the tag of the code for `xxxxx_0.1.orig.tar.gz`
* `debian/0.2-1` is the tag of the snapshot to generate `xxxxx_0.2-1_yyy.deb` and `xxxxx_0.2-1.debian.tar.xz`.

[Learn more about PackagingWithGit](https://wiki.debian.org/PackagingWithGit)

## How to build packages from Salsa

Create a directory and `cd` into it (just to avoid spreading files in the current dir):
```bash
$ mkdir xxxxx
$ cd xxxxx
```

Clone the repo using https:
```bash
$ git clone https://salsa.debian.org/virtualsquare-team/xxxxx.git
```
or ssh:
```bash
$ git clone git@salsa.debian.org:virtualsquare-team/xxxxx.git
```
or git:
```bash
$ git clone git://salsa.debian.org/virtualsquare-team/xxxxx.git
```

Enter the just cloned repo:
```bash
cd xxxxx
```

and use [_git-buildpackage_](https://packages.debian.org/sid/git-buildpackage) to build the package:
```bash
$ gbp buildpackage -us -uc
```
Note: `-us` ("_Do not sign the source package._") and `-uc` ("_Do not sign the .changes file._") are _dpkg-buildpackage_ flags which are passed from _debuild_ to _dpkg-buildpackage_.

The source and binary packages are ready in the parent directory.

## VirtualSquare tutorial for Debian packaging

The following recipe for Debian packaging is just a hint. All the process should be applied _cum grano salis_ and paying attention to _mutadis mutandis_.

### Create the project repo on Salsa

Make it public and do not add a README (create an empty project).

### Push the development repo

`cd` to the dir where you have your local copy of the development repo (or clone the repo from GitHub).
In this example the local copy of the project `xxxxx` is in `~/GITHUB/xxxxx/xxxxx`:

```bash
$ cd ~/GITHUB/xxxxx/xxxxx
$ git checkout master
$ git remote add salsa git@salsa.debian.org:virtualsquare-team/xxxxx.git
$ git push -u salsa master:upstream
```
and create a tag for the `watch` file (0.1 is just an example):

```bash
$ git tag 0.1
$ git push --tags
```

### Clone the Salsa repo

```bash
$ mkdir ~/SALSA/xxxxx
$ cd ~/SALSA/xxxxx
$ clone git@salsa.debian.org:virtualsquare-team/xxxxx.git
$ cd xxxxx
```

### Create a tag for the source version

```bash
$ git tag upstream/0.1
$ git push --tags
```

### Create a `debian/sid` branch and check it out

```bash
$ git branch debian/sid
$ git checkout debian/sid
```

### Add the debian dir

Files required in the debian dir:

* `changelog`
* `control`
* `copyright`
* `rules`
* `source/format`

For each binary package xxxbin:

* `xxxbin_install`

Virtualsquare repos include _git-buildpackage_ configuration:

* `gbp.conf`

and a watch file to check the synchronization with new releases on GitHub.

* `watch`

The file [`debian_xxxxx.tgz`](https://raw.githubusercontent.com/virtualsquare/virtualsquare.github.io/master/archive/debian/debian_xxxxx.tgz)
(click on it to download) contains an example of `debian` dir contents to be customized for the actual repository.

The timestamp in the `changelog` file can be updated by adding a fake entry using `dch` and the editing the `changelog` file (or create a new `changelog` by `dch --create`).

```bash
$ git add debian
$ git commit
```

The standard comment for this commit is "_Add Debian Packaging support_".

### Test the packaging process

```bash
$ gbp buildpackage -us -uc
```

Check the packages and read carefully the comments from lintian.

### Clean the repo contents

```bash
$ debuild -- clean
```

In case byproducts of packaging has been left around:
```bash
$ git reset --hard
$ git clean -f -d
```

### In case something is wrong

Change the contents of debian directory files:
```bash
$ git add -u
```
.... `git add`/`git rm`/`git mv`... whatever needed
```bash
$ git commit --amend
```
and jump back to [Test the packaging process](#Test_the_packaging_process).

### Push the `debian/sid` branch on Salsa
```bash
$ git push -u origin debian/sid
```
### (optional) Create the pristine-tar
```bash
$ gbp pristine-tar commit ../xxxxx_0.1.orig.tar.gz
$ git push origin -u pristine-tar:pristine-tar
```

### Set `debian/sid` as the default branch on Salsa

From the project homepage: _Settings-->Repository-->Default Branch_.

## Debian Packaging on Arch Linux

As mentioned in the [Packaging/Pre-Requisites](https://wiki.debian.org/Packaging/Pre-Requisites) section of the Debian Wiki, you need a [Debian unstable](https://wiki.debian.org/DebianUnstable) environment to create packages suitable for uploading to Debian, but you don't have to maintain a whole Debian system to achieve this.

The ArchWiki gives us some tips at [_Creating packages for other distributions_](https://wiki.archlinux.org/index.php/Creating_packages_for_other_distributions).

Here is an example of how to reproduce the VirtualSquare's Debian Packaging workflow on Arch-based systems.

### Setting up the environment

To set up a minimal working Debian Packaging environment you need at least [build-essential](https://packages.debian.org/sid/build-essential), [devscripts](https://packages.debian.org/sid/devscripts) and [debhelper](https://packages.debian.org/sid/debhelper) on your system.

On Arch Linux, you can obtain these tools by installing:

* [base-devel](https://www.archlinux.org/groups/x86_64/base-devel/)
* [debian-archive-keyring](https://www.archlinux.org/packages/community/any/debian-archive-keyring/)
* [devscripts](https://aur.archlinux.org/packages/devscripts/)
* [dh-autoreconf](https://aur.archlinux.org/packages/dh-autoreconf/)

As previously mentioned, VirtualSquare uses [git-buildpackage](https://packages.debian.org/sid/git-buildpackage) to integrate the package build system with Git.

Furthermore, we will test the package against [pbuilder](https://packages.debian.org/sid/pbuilder), since building it inside a clean-room environment ensure us that it will build properly in most Debian installations.

You can obtain both tools by installing:

* [git-buildpackage](https://aur.archlinux.org/packages/git-buildpackage/)
* [pbuilder-ubuntu](https://aur.archlinux.org/packages/pbuilder-ubuntu/)

### Building the package

While the packaging process remains [the same](#VirtualSquare_tutorial_for_Debian_packaging), on Arch Linux [we are forced](https://wiki.archlinux.org/index.php/Creating_packages_for_other_distributions#Override_dependency_handling) to use the `-d` ("_Do not check build dependencies and conflicts_") flag while building the package because _dpkg_ does not recognize dependencies installed by [pacman](https://wiki.archlinux.org/index.php/Pacman).

The [_Test the packaging process_](#Test_the_packaging_process) step will become:
```bash
$ gbp buildpackage -us -uc -d
```

### Testing the package

Since we used the `-d` flag, our newly built package is far from being foolproof.

_Pbuilder_ comes to our rescue, allowing us to build the package inside a clean Debian chroot environment.
You can learn more about its usage [here](https://wiki.ubuntu.com/PbuilderHowto) and [here](https://pbuilder-team.pages.debian.net/pbuilder/).

#### Creating the chroot image

First of all you must create a base tarball that will contain your chroot environment to build packages with.
All other commands will operate on the resulting `base.tgz`.
```bash
$ sudo pbuilder create --distribution sid --mirror http://ftp.us.debian.org/debian/ --debootstrapopts "--keyring=/usr/share/keyrings/debian-archive-keyring.gpg"
```
Note: choose an appropriate `--mirror` from [here](https://www.debian.org/mirror/list).

#### Building the package using the `base.tgz`

To build the package inside the chroot, invoke `pbuilder build /path/to/xxxxx.dsc`.
From inside the project directory:
```bash
$ sudo pbuilder build ../xxxxx.dsc
```

#### Updating the `base.tgz`

Sometimes, remember to update the chroot environment with:
```bash
$ sudo pbuilder update
```
