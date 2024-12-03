#!/bin/bash
#set -x

# thanks to Giacomo Rizzi: some ideas have been taken from: https://github.com/gufoe/vuos-tutorial

export CMAKE_INSTALL_ALWAYS=1

BASE="$(dirname "$0")"
cd $BASE
BASE=$(pwd)
echo "BASE: $BASE"

# User friendly messages on error
set -E
set -o functrace
function handle_error {
    local retval=$?
    local line=${last_lineno:-$1}
    echo "Failed at $line: $BASH_COMMAND"
    echo "Trace: " "$@"
    exit $retval
}
if (( ${BASH_VERSION%%.*} <= 3 )) || [[ ${BASH_VERSION%.*} = 4.0 ]]; then
	trap '[[ $FUNCNAME = handle_error ]] || { last_lineno=$real_lineno; real_lineno=$LINENO; }' DEBUG
fi
trap 'handle_error $LINENO ${BASH_LINENO[@]}' ERR

function install_repo {
	REPO=$1
	REPOBASE=${REPO##*/}
	REPOBASE=${REPOBASE%%.*}
	PREWD=$(pwd)
	echo installing $1
	cd  "$BASE"/gits
	git clone --recurse-submodules $1
	cd $REPOBASE
	if [ -f configure.ac ]
	then
		echo AUTOCONF
#autoreconf -if || (libtoolize; autoreconf -if) # WTF is this not compiling at first?
		autoreconf -vif
		./configure $2
	elif [ -f CMakeLists.txt ] 
	then
		echo CMAKE
		mkdir -p build
		cd build
		cmake .. $2
	else
		echo UNKNOWN
		exit 1
	fi
	make
	make install
	ldconfig
	cd $PREWD
}

function install_picotcp {
	REPO=$1
	REPOBASE=${REPO##*/}
	REPOBASE=${REPOBASE%%.*}
	PREWD=$(pwd)
	echo installing $1
	cd  "$BASE"/gits
	git clone --recurse-submodules $1
	cd $REPOBASE
	make gnulib
	PREFIX=/usr/local
	make GNULIB_INSTALL_PREFIX=${PREFIX} gnulib-install
	ldconfig
	cd $PREWD
}

# Start installation
rm -rf gits
mkdir gits

install_repo https://github.com/virtualsquare/s2argv-execs.git
install_repo https://github.com/rd235/strcase.git
install_repo https://github.com/virtualsquare/vde-2.git -enable-experimental
install_repo https://github.com/rd235/vdeplug4.git
install_repo https://github.com/virtualsquare/purelibc.git
install_repo https://github.com/rd235/libvolatilestream.git
install_repo https://github.com/rd235/libstropt.git
install_repo https://github.com/rd235/libfduserdata.git
install_repo https://github.com/rd235/libvpoll-eventfd.git
install_repo https://github.com/rd235/libvdestack.git
install_repo https://github.com/virtualsquare/vdeplug_vlan.git
install_repo https://github.com/virtualsquare/libvdeslirp.git
install_repo https://github.com/virtualsquare/vdeplug_slirp.git
install_repo https://github.com/rd235/cado.git
install_repo https://github.com/alperakcan/fuse-ext2.git
install_repo https://github.com/virtualsquare/vdeplug_agno.git
install_repo https://github.com/virtualsquare/vdeplug_pcap.git
install_repo https://github.com/virtualsquare/vdeplug_vdesl.git
install_repo https://github.com/rd235/userbindmount.git
install_repo https://github.com/rd235/vdens.git
install_repo https://github.com/virtualsquare/vuos.git
install_repo https://github.com/virtualsquare/nlinline.git
install_repo https://github.com/virtualsquare/libioth.git
install_repo https://github.com/virtualsquare/libnlq.git
install_repo https://github.com/virtualsquare/randmac.git
install_repo https://github.com/rd235/libpam-net.git -DLIBSECURITYDIR=/lib/x86_64-linux-gnu/security/
install_repo https://github.com/virtualsquare/vufusearchive.git
install_repo https://github.com/virtualsquare/fusefatfs.git
install_repo https://github.com/virtualsquare/iothconf.git
install_repo https://github.com/virtualsquare/iothdns.git
install_repo https://github.com/virtualsquare/iothnamed.git
install_repo https://github.com/virtualsquare/namedhcp.git
install_repo https://github.com/virtualsquare/otip-utils.git
install_repo https://github.com/virtualsquare/iothradvd.git
install_picotcp https://github.com/virtualsquare/picotcp.git
install_repo https://github.com/virtualsquare/picoxnet.git
# vunetpicox deprecated. there are still examples in the tutorial
# it will be removed as soon as the tutorial pages have been updated
install_repo https://github.com/virtualsquare/vunetpicox.git
install_repo https://github.com/virtualsquare/vunetioth.git
install_repo https://github.com/virtualsquare/ioth_picox.git

rm -f /usr/local/lib/vu/modules/vufuseext2.so /usr/local/lib/vu/modules/vufuseext2.re
# ln -s /usr/local/lib/umview/modules/umfuseext2.so /usr/local/lib/vu/modules/vufuseext2.so
# touch /usr/local/lib/vu/modules/vufuseext2.re

echo 'Installation completed'
