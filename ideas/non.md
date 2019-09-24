Network of Namespaces (NoN)
====

what
----
Namespaces can be seen as internet nodes. This is a way to implement the idea of [Internet of Threads](ioth.md).

why
----
Because through _Network of Namespaces_ it is possible to implement the idea of Internet of Threads 
in a way which preserves the backwards compatibility with all the server and client software running on Linux.

The networking stacks used by NoN are instances of the networking services provided by the kernel.
NoN has a performance comparable to the native networking support.


how
----
[vdens](https://github.com/rd235/vdens) create User Namespaces connected to VDE plugs.
This means that vdens namespaces can use all the plug-ins compatible with the
[vdeplug4](https://github.com/rd235/vdeplug4) project.

Examples:

* `vdens vde:///var/run/mynet`: NoN connected to a vde switch
* `vdens slirp://`: NoN connected to slirp
* `vdens vxvde://239.0.0.1`: NoN connected to a [local Area Cloud](lac.md)
* `vdens -m vxvde://239.0.0.1 vxvde://239.0.0.2`: NoN as a gateway between two [local Area Clouds](lac.md)

where
----
The idea is implemented in [vdens](https://github.com/rd235/vdens).

references:
----

* R. Davoli, _VXVDEX: Internet of threads and networks of namespaces,_ 2017 IEEE International Conference on Communications (ICC), Paris, 2017, pp. 1-6.
* [Presentation at LinuxLab 2017](https://2017.linux-lab.it/talks/network_of_namespaces_and_layer_2_local_area_clouds_2017-12-06)
