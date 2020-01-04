#!/bin/bash

apt-get install git python3 build-essential cmake make autogen \
	autoconf libtool libcap-dev libattr1-dev libfuse-dev \
	libexecs-dev libmhash-dev libpam-dev libssl-dev \
	libfuse-dev e2fsprogs comerr-dev e2fslibs-dev xterm \
	x11-utils libslirp vim vde2 vdetelweb

echo 'kernel.unprivileged_userns_clone=1' > /etc/sysctl.d/00-local-userns.conf
service procps restart
