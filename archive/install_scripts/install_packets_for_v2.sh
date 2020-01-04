#!/bin/bash

apt-get install git python3 build-essential cmake make autogen \
	autoconf libtool libcap-dev libattr1-dev libfuse-dev \
	libexecs-dev libmhash-dev libpam0g-dev libssl-dev \
	libfuse-dev e2fsprogs comerr-dev e2fslibs-dev xterm \
	x11-utils libslirp-dev vim vde2 vdetelweb

echo 'kernel.unprivileged_userns_clone=1' > /etc/sysctl.d/00-local-userns.conf
service procps restart
