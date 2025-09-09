#!/bin/bash

apt-get --yes install git python3 build-essential cmake make autogen \
	autoconf libtool libcap-dev libattr1-dev libfuse-dev libwolfssl-dev \
	libexecs-dev libmhash-dev libpam0g-dev libssl-dev netcat-openbsd netcat-traditional \
	libfuse3-dev e2fsprogs comerr-dev e2fslibs-dev xterm libglib2.0-dev \
	udhcpc x11-utils libpcap-dev libslirp-dev vim gzip \
	vde2 vdetelweb archivemount libarchive-dev sshfs fuse2fs uuid-dev libblkid-dev

ln -sf /bin/false /bin/nologin
echo 'kernel.unprivileged_userns_clone=1' > /etc/sysctl.d/00-local-userns.conf
service procps restart
