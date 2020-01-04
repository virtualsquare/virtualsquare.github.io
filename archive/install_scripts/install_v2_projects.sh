#!/bin/bash
#set -x

# thanks to Giacomo Rizzi: some ideas have been taken from: https://github.com/gufoe/vuos-tutorial

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
	git clone $1
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
		cmake ..
	else
		echo UNKNOWN
		exit 1
	fi
	make
	make install
	ldconfig
	cd $PREWD
}

# Start installation
rm -rf gits
mkdir gits

install_repo https://github.com/rd235/s2argv-execs.git
install_repo https://github.com/rd235/strcase.git
install_repo https://github.com/virtualsquare/vde-2.git -enable-experimental
install_repo https://github.com/rd235/vdeplug4.git
install_repo https://github.com/virtualsquare/purelibc.git
install_repo https://github.com/rd235/libvolatilestream.git
install_repo https://github.com/rd235/libstropt.git
install_repo https://github.com/rd235/libfduserdata.git
install_repo https://github.com/rd235/libvpoll-eventfd.git
install_repo https://github.com/rd235/libvdestack.git
install_repo https://github.com/rd235/vdeplug_vlan.git
install_repo https://github.com/virtualsquare/libvdeslirp.git
install_repo https://github.com/virtualsquare/vdeplug_slirp.git
install_repo https://github.com/rd235/cado.git
install_repo https://github.com/alperakcan/fuse-ext2.git
install_repo https://github.com/rd235/vdeplug_agno.git
install_repo https://github.com/rd235/vdeplug_pcap.git
install_repo https://github.com/rd235/userbindmount.git
install_repo https://github.com/rd235/vdens.git
install_repo https://github.com/virtualsquare/vuos.git
install_repo https://github.com/virtualsquare/nlinline.git
install_repo https://github.com/virtualsquare/libnlq.git

rm -f /usr/local/lib/vu/modules/vufuseext2.so
ln -s  /usr/local/lib/umview/modules/umfuseext2.so /usr/local/lib/vu/modules/vufuseext2.so

echo 'Installation completed'
