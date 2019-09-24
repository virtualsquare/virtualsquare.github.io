Ambient Capability DO (cado)
====

what
----
Cado permits to delegate capabilities to users. (like a sudo providing users with just the capabilities they need).

why
----
Because for the principle of least privilege a system is safer when users/processes are granted only the rights they need.

Cado is more selective than sudo, users can be authorized to have only specific [linux capabilities](http://man7.org/linux/man-pages/man7/capabilities.7.html) (and not others).

how
----
Cado uses ambient capabilities.

where
----
There is a [specific project](https://github.com/rd235/cado)

<!-- references:
-->
