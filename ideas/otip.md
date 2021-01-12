One Time IP addresses (OTIP)
====

what
----

The current IP address of a server is computed on the basis of some private
information shared by legitimate users and the server itself, like a password,
and the current time.  OTIP means that the current IP address of a
server changes periodically to prevent networking attacks.  This
method has mainly been designed for IPv6 networks.

why
----

Hosting servers use a finite number of IP addresses to connect on the net.
Attackers can collect those by wiretapping the network and create a catalog of
valid addresses and services in order to attack the servers.  OTIP can prevent
these attacks, or make them harder to succeed as the addresses collected by
network sniffers expire in a short time.  OTIP aims to provide one further
layer of protection for private services.

how
----

OTIP does require the Real Time Clocks (RTC) of servers and clients to be
reasonably synchronized, as the current time is a parameter to compute the
current address. One to some seconds drift is tolerated.  The current IP
address is the output of a computation based on the Fully Qualified Domain Name
(FQDN) of the server, a secret password and the current time.

OTIP has been implemented for both TCP and UDP connections:

- **TCP**: In order to support unmodified client programs the prototype uses an
OTIP enabled Domain Name Server (DNS) proxy which is installed on the user’s
computer where the client program is running. This DNS proxy transparently
forwards all the requests to the real DNS server except those matching the OTIP
syntax (The password is never sent along the network as the proxy is running in
the same host of the client process, thus it cannot be captured by an
attacker possibly tracing the network traffic).  On the server side either
an OTIP specific server program or a proxy interfacing an existing server
daemon, provide the connectivity for OTIP clients.  Each address continues to
be reachable only for the active connections (if any), even when expired. The
listening socket is open only on the current address.

- **UDP**: it is possible to implement OTIP UDP proxies which set up an OTIP UDP
tunnel between the client and the server. Each client uses a port on the local
host to exchange networking packets to the server. The local port is managed by
the local proxy, which forwards each packet to the OTIP dynamically changing
address of the proxy on the server side.  On the server side, the OTIP UDP
proxy forwards the packets to the OTIP unaware server using a local port.

where
----

The current description is a proof-of-concept, we're currently working on a new
version of *vde_dnsutils* which will be based on `libioth` and `iothdns`.

references:
----

Renzo Davoli, *OTIP : One Time IP Address*, in _International Conference on
Systems and Networks_, 2013.

#### acknowledgement
thanks to Francesco Cerio who contributed this page.
