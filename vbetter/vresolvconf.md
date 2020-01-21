/etc/resolv.conf is hardcoded in glibc
====

# The problem

`glibc` includes `libresolv` including functions for resolving host names
using the DNS service.

Unfortunately the path of the configuration file, i.e. `/etc/resolv.conf`
id hardcoded in the source and cannot be changed at run time.

In `resolv/resolv.h`:
```C
#define _PATH_RESCONF        "/etc/resolv.conf"
```
In` resolv/res_init.c`:
```C
  FILE *fp = fopen (_PATH_RESCONF, "rce");
```

When users define network namespaces (e.g. `vdens`) the DNS server for the
new address space can be (and most of the time is) different from the DNS
server off the host.

This is a security problem. A quite common workaound is to define in /etc/resolv.conf
a well known and _ubiquitus_ available server like 80.80.80.80 or 8.8.8.8.
This makes both the host and the namespace prone to DNS spoofing attacks and
to private information disclosure.

# The Workaroud

All the workarounds are based on bind-mounting a different file on "/etc/resolv.conf"
in a user namespace.

`vdens` has the options `-R` and `-r` to solve the problem.
```bash
$ vdens -R 192.168.254.1 vxvde://
$# cat /etc/resolv.conf 
nameserver 192.168.254.1
```

`userbindmount` and `libuserbindmount` is a general purpose solution to 
the redefinition of configuration files in user namespaces.

# Please

... add an environment variable to load a different resolv.conf file
(many other behaviors of glibc can be configured by envirnemnt variables, say `TZ` or `LOCALE`.
A user may want to use their own DNS server, even if they are not using any
namespace.

# Links:

* [Proposed patch](https://sourceware.org/ml/libc-alpha/2017-08/msg00742.html)
* [userbindmount](https://github.com/rd235/userbindmount)
