How to set up a host for the tutorials.
======

## step 0: take a spare host

Suggested architecture: x86\_64, 4GB RAM and a recent processor supporting the virtualization instructions.

## step 1: install Debian sid on it.

Follow the guides provided by Debian.

Edit the file `/etc/apt/sources.list`. It should be like the following:

```
deb http://deb.debian.org/debian unstable main contrib
deb-src http://deb.debian.org/debian unstable main contrib

deb http://security.debian.org/debian-security testing-security main contrib
deb-src http://security.debian.org/debian-security testing-security main contrib
```

## step 2: download and run the install scripts

The scripts are available [here](https://github.com/virtualsquare/virtualsquare.github.io/tree/master/archive/install_scripts)

Run the script as root as follows. 
```
# ./install_packets_for_v2.sh
.... 
# ./install_v2_projects.sh
.... 
```

The script `append_to.bashrc` can be appended to each user's `.bashrc` file.
```
$ cat append_to.bashrc >> ~/.bashrc
```
It provides users with a convenient shell prompt (including the id of the
		vuos environment and the current ambient capabilities).

## step3: enjoy

The host is ready.
