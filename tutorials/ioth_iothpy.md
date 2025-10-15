# iothpy : Python module for IoTh, iothconf and iothdns support


This module provides the creation and configuration of Internet of Threads stack and socket, with an additional support for clients who need to query DNS servers, using iothdns API.

## Classes
Iothpy module provides the classes to use IoTh in Python. The classes are Stack and Socket.

### Stack

#### Creation
To create a stack object, the constructor is:
```py
iothpy.Stack(stack_name, vdeurl = None, config_dns = None)
```
where:
* `stack_name` (required): it is the name of IoTh stack to be used (e.g. vdestack, picox, ...), or a string following newstackc configuration syntax.
* `vdeurl` (optional): can be a string or a list of strings representing the VDE URLs. The stack will have an interface for each vde.
* `config_dns` (optional): path or string for the configuration of iothdns descriptor, following /etc/resolv.conf syntax. Default value is "/etc/resolv.conf".

Note: if `stack_name` isn't a configuration and `vdeurl` is None, then the stack will be initialized with no interface. Vdestack doesn't support the addition of interface at runtime.

#### Configuration
To configure the stack you can use these functions:
    `linksetupdown`, `linkgetaddr`, `linksetaddr`, `iplink_add`, `iplink_del`, `linksetmtu`, `ipaddr_add`, `ipaddr_del`,`iproute_add`, `iproute_del`.

Or you can use a single method: `iothconfig(config)`.

To update the DNS, you can use `iothdns_update(config)`, where `config` follows the same principles of `config_dns` in stack initialization.

#### Other methods
```py
Stack.getaddrinfo(host, port, family=0, type=0, proto=0)
```
It translates the *host/port* argument in a sequence of 5-tuple containing all the info for create a socket connected to service.
This method has the same signature of built-in Python method `socket.getaddrinfo()`, but uses iothdns.


```py
Stack.socket(self, family=-1, type=-1, proto=-1, fileno=None)
```
Create and return a new socket on this stack.
This method takes the same parameters of the built-in Python method `socket.socket()`.

### Socket
This class has the main methods of the builtin socket module, like `bind`, `close`, `connect` , `send` and more.

## Installation
The following libreries are requested to use this module:
* [libioth](https://github.com/virtualsquare/libioth)
* [iothconf](https://github.com/virtualsquare/iothconf)
* [iothdns](https://github.com/virtualsquare/iothconf)

To install iothpy module, do:
```bash
pip install iothpy
```

To uninstall the library, do:
```bash
pip uninstall iothpy
```

## Examples

### Getting started
Here is an example of a basic creation and configuration of a networking stack connected to a VDE URL:

```python
import iothpy

# Create a new stack using vdestack connected to vde:///tmp/mysw
stack = iothpy.Stack("vdestack", "vde:///tmp/mysw")

# Get the index of the default interface vde0
if_index = stack.if_nametoindex("vde0")


# Enable the interface
stack.linksetupdown(if_index, 1)

# Set MAC address of the interface
stack.linksetaddr(if_index, "80:00:42:0e:e7:3a")

# Add IPv4 address and default gateway
stack.ipaddr_add(iothpy.AF_INET, "10.0.0.1", 24, if_index)
stack.iproute_add(iothpy.AF_INET, "10.0.0.254")

# Create a new socket on the stack
s = stack.socket(iothpy.AF_INET, iothpy.SOCK_STREAM)

```
The Stack constructor takes the name of a ioth plugin (`vdestack`, `picox`, ...) and one or a list of vde urls. The new stack has a virtual interface connected to each vde network identified by the VNL.

The stack object has methods for all the configuration options defined by libioth, for more details you can run `help("iothpy.Stack")` inside a python interpreter.

After the configuration you can create sockets using the `Stack.socket` method. The parameters and the API of the returned socket is the same as the Python built-in socket module.


### Server-client
Let's make a server-client communication:
#### `server.py`
```py
#!/usr/bin/python

import sys
import iothpy
import time
import threading

# Check arguments
if(len(sys.argv) != 2):
    name = sys.argv[0]
    print("Usage: {0} vdeurl\ne,g: {1} vxvde://234.0.0.1\n\n".format(name, name))
    exit(1)

# Create and configure stack
stack  = iothpy.Stack("vdestack", sys.argv[1])
ifindex = stack.if_nametoindex("vde0")
stack.linksetupdown(ifindex, 1)
stack.ipaddr_add(iothpy.AF_INET, "10.0.0.1", 24, ifindex)
stack.iproute_add(iothpy.AF_INET, "10.0.0.254")

# To create and configure stack, you can use also:
# stack = iothpy.Stack("stack=vdestack,vnl={0},eth, ip=10.0.0.1/24".format(sys.argv[1]))

# Create a tcp listening socket from
sock = stack.socket(iothpy.AF_INET, iothpy.SOCK_STREAM)

# From here on we can use the ioth socket as if we were using a python socket
sock.bind(('', 5000))
sock.listen(1)

# Handle incoming connection
def handle(conn, addr):
    while True:
        data = conn.recv(1024)
        if not data:
            print("Connection closed by", addr)
            break
        print("Got:", data.decode(), "from", addr)
        conn.send(data)

# Listen on the socket for a new connection
while True:
    conn, addr = sock.accept()
    print("New connection by {}".format((conn, addr)))
    # Create a new thread to handle multiple concurrent connections
    t = threading.Thread(target = handle, args=(conn, addr), daemon=True)
    t.start()
```

#### `client.py`

```py
# file client.py:

#!/usr/bin/python

import iothpy

import sys
import time
import select

# Check arguments
if(len(sys.argv) != 2):
    name = sys.argv[0]
    print("Usage: {0} vdeurl\ne,g: {1} vxvde://234.0.0.1\n\n".format(name, name))
    exit(1)

# Create and configure stack
stack  = iothpy.Stack("vdestack", sys.argv[1])
ifindex = stack.if_nametoindex("vde0")
stack.linksetupdown(ifindex, 1)
stack.ipaddr_add(iothpy.AF_INET, "10.0.0.2", 24, ifindex)
stack.iproute_add(iothpy.AF_INET, "10.0.0.254")

# To configure the stack, you can use the single function:
# stack.ioth_config("eth,ip=10.0.0.53/24,gw=10.0.0.1".format(sys.argv[1]))

# Create a tcp socket and connect to server
sock = stack.socket(iothpy.AF_INET, iothpy.SOCK_STREAM)

# From here on we can use the ioth socket as if we were using a python socket
sock.connect(("10.0.0.1", 5000))

print("Connected to server at", sock.getpeername())

# Create a poll object to wait for messsages from the server and stdin
poll_obj = select.poll()
poll_obj.register(sock, select.POLLIN)
poll_obj.register(sys.stdin, select.POLLIN)

while(True):
    events = poll_obj.poll()
    for fd, event in events:
        # Read messages from the server
        if(fd == sock.fileno()):
            message = sock.recv(1024)
            if(message):
                print(message.decode())
            else:
                break
        # Read from stdin
        if(fd == sys.stdin.fileno()):
            message = input().rstrip()
            if(message):
                sock.send(message.encode())
            else:
                break
```

### Getaddrinfo

Note: this example needs [`libvdeslirp`](https://github.com/virtualsquare/libvdeslirp)

```py
#file gai.py:

import iothpy

#create and configure stack
stack = iothpy.Stack("vdestack","slirp://")
stack.ioth_config("auto")

# host and port to connect to
host ="www.google.com"
port = 80

addrinfos = stack.getaddrinfo(host, port)

print(f"All addresses info of {host}, port {port}:\n\n{addrinfos}]\n")

family, type, proto, _, sockaddr = addrinfos[0]
print(f"Address 0 info, used as test:\n{addrinfos[0]}.\nSo the address to connect the socket is:\n{sockaddr}\n")

# create socket from the stack
socket = stack.socket(family, type, proto)

socket.connect(sockaddr)

print("Connection established to ", socket.getpeername())
```

### Other examples
You can find other examples in [iothpy repo](https://github.com/ramenguy99/iothpy) on GitHub.