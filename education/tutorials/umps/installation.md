# How to install µMPS3

µMPS3 was already packaged for the distros listed below.
If you can't find your distro here, you will have to [build from source](#Building_from_source) ([example](#Step-by-step)).

If you create a package for any other distribution, please consider contributing the template.

## Ubuntu

If you are using **Ubuntu 20.04 Focal Fossa**, **18.04 Bionic Beaver** or **16.04 Xenial Xerus** ([Checking your Ubuntu Version](https://help.ubuntu.com/community/CheckingYourUbuntuVersion)) or [derivatives](https://wiki.ubuntu.com/DerivativeTeam/Derivatives) (e.g. **Linux Mint**), you need to:

1. enable [Universe](https://help.ubuntu.com/community/Repositories/Ubuntu)
```bash
$ sudo add-apt-repository universe
$ sudo apt update
```
2. add the [virtualsquare/umps PPA](https://launchpad.net/~virtualsquare/+archive/ubuntu/umps)
```bash
$ sudo add-apt-repository ppa:virtualsquare/umps
$ sudo apt update
```
3. install
```bash
$ sudo apt install umps3
```

## Debian

The [official µMPS3 package](https://ftp-master.debian.org/new/umps3_3.0.1-2.html) is currently waiting in the [NEW queue](https://wiki.debian.org/NewQueue).

In the meantime, you can install µMPS3 by manually adding the [virtualsquare/umps PPA](https://launchpad.net/~virtualsquare/+archive/ubuntu/umps) on your **Debian** system.

### Debian 10 Stable ("buster")

If you are using **Debian 10 ("buster")**, you need to:

1. add the [virtualsquare/umps PPA](https://launchpad.net/~virtualsquare/+archive/ubuntu/umps) for the [Ubuntu 18.04 (Bionic Beaver)](https://releases.ubuntu.com/18.04/) version to your [Apt sources configuration file](https://wiki.debian.org/SourcesList):
```bash
$ echo 'deb http://ppa.launchpad.net/virtualsquare/umps/ubuntu bionic main' | sudo tee /etc/apt/sources.list.d/virtualsquare-ubuntu-umps-bionic.list
```
2. import the [signing key](https://keyserver.ubuntu.com/pks/lookup?fingerprint=on&op=index&search=0xBB8957296BD01F6CA96B5C88046AB1F65C49333A):
```bash
$ sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 046AB1F65C49333A
```
3. re-synchronize the package index files:
```bash
$ sudo apt update
```
4. install
```bash
$ sudo apt install umps3
```

### Debian 11 Testing ("bullseye") and Unstable ("sid")

If you are using **Debian 11 Testing ("bullseye")** or **Unstable ("sid")**, you need to:

1. add the [virtualsquare/umps PPA](https://launchpad.net/~virtualsquare/+archive/ubuntu/umps) for the [Ubuntu 20.04 (Focal Fossa)](https://releases.ubuntu.com/focal/) version to your [Apt sources configuration file](https://wiki.debian.org/SourcesList):
```bash
$ echo 'deb http://ppa.launchpad.net/virtualsquare/umps/ubuntu focal main' | sudo tee /etc/apt/sources.list.d/virtualsquare-ubuntu-umps-focal.list
```
2. import the [signing key](https://keyserver.ubuntu.com/pks/lookup?fingerprint=on&op=index&search=0xBB8957296BD01F6CA96B5C88046AB1F65C49333A):
```bash
$ sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 046AB1F65C49333A
```
3. re-synchronize the package index files:
```bash
$ sudo apt update
```
4. install
```bash
$ sudo apt install umps3
```

## Arch Linux

If you are using **Arch Linux** or [derivatives](https://wiki.archlinux.org/index.php/Arch-based_distributions) (e.g. **Manjaro**), you can install the AUR package [umps3-git](https://aur.archlinux.org/packages/umps3-git/) to get the latest version, or [umps3](https://aur.archlinux.org/packages/umps3/) for the latest stable release.

- [AUR - Installing and upgrading packages](https://wiki.archlinux.org/index.php/Arch_User_Repository#Installing_and_upgrading_packages)
- [AUR helpers](https://wiki.archlinux.org/index.php/AUR_helpers)

## Building from source

Please [report any problems](https://github.com/virtualsquare/umps3/issues/new) you run into when building the project.

### Dependencies

A compiler with C++11 support ([clang-3.3+](https://llvm.org/releases/download.html), [gcc-4.8+](https://gcc.gnu.org/releases.html)), [cmake 3.5+](https://cmake.org/download/), [git](https://git-scm.com/downloads)

- `Qt 5.5+`
- `libelf`
- `boost 1.34+` (headers)
- `libsigc++ 2.0`

Apart from the dependencies listed above, you will also need a MIPS cross toolchain in your PATH.
CMakelists.txt will do its best to detect one; if that fails, you can pass the toolchain tool prefix to `cmake` using `-DMIPS_TOOL_PREFIX=PREFIX`.
Known prefixes are:

- `mips-sde-elf-`
- `mips(el)-elf-`
- `mips(el)-linux-`
- `mips(el)-linux-gnu-`

Get the source code, from the root of the source tree run:
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

By default, the software is installed locally in `/usr/local/`.
If you want to install it somewhere else (e.g. in `/usr/`) you can pass the path using `-DCMAKE_INSTALL_PREFIX:PATH=/usr`.

### Uninstallation

From the root of the binary tree run:
```bash
$ sudo make uninstall
```
N.B.: "install_manifest.txt" is generated during the installation process.

## Examples

### Step-by-step

Here is an example of how to [build from source](#Building_from_source) and install µMPS3 on **Debian** and [derivatives](https://www.debian.org/derivatives/) (e.g. **Ubuntu**, **Pop!_OS**)

#### Install dependencies

```bash
$ sudo apt install git build-essential cmake qtbase5-dev libelf-dev libboost-dev libsigc++-2.0-dev gcc-mipsel-linux-gnu
```

#### Get the source code

```bash
$ git clone https://github.com/virtualsquare/umps3
```

#### Build and Install

```bash
$ cd umps3
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

#### Launch

You should now be able to launch µMPS3 via the application menu of your desktop environment, or by typing `umps3` at the command line.
