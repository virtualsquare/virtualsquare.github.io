# How to install µMPS

## Installation

µMPS was already packaged for the distros listed below.
If you can't find your distro here, you will have to [build from source](#Building_from_source) ([example](#Step-by-step)).

If you create a package for any other distribution, please consider contributing the template.

If you are using **Arch Linux**, you can install the AUR package [umps3-git](https://aur.archlinux.org/packages/umps3-git/) to get the latest version, or [umps3](https://aur.archlinux.org/packages/umps3/) for the latest stable release.

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

### Building from source

Please [report any problems](https://github.com/virtualsquare/umps3/issues/new) you run into when building the project.

Get the source code, from the root of the source tree run:
```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

By default, the software is installed locally in `/usr/local/`.
If you want to install it somewhere else (e.g. in `/usr/`) you can pass the path using `-DCMAKE_INSTALL_PREFIX:PATH=/usr`.

## Uninstallation

From the root of the binary tree run:
```sh
$ sudo make uninstall
```
N.B.: "install_manifest.txt" is generated during the installation process.

## Examples

### Step-by-step

Here is an example of how to [build from source](#Building_from_source) and install µMPS on **Debian** and derivatives (**Ubuntu**, **Pop!_OS**, etc.)

#### Install dependencies

```sh
$ sudo apt install git build-essential cmake qtbase5-dev libelf-dev libboost-dev libsigc++-2.0-dev gcc-mipsel-linux-gnu
```

#### Get the source code

```sh
$ git clone https://github.com/virtualsquare/umps3
```

#### Build and Install

```sh
$ cd umps3
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

#### Launch

You should now be able to launch µMPS via the application menu of your desktop environment, or by typing `umps3` at the command line.
