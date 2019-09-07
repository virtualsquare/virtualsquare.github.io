if command -v vuname &> /dev/null; then
	vuname=$(vuname -P)
else
	vuname=$(hostname)
fi

if command -v caprint &> /dev/null; then
	ambient=$(caprint -p)
else
	ambient=""
fi

PS1='${debian_chroot:+($debian_chroot)}\u@$vuname:\w\$$ambient '
