Linux: dlmopen problems (dlclose does not work)
====

# The problems

* The manual says: "the glibc implementation supports a maximum of 16 namespaces".
In the reality less namespaces are available.

* Once a namespace is allocated by a dlmopen it is never de-allocated.
dlclose does not "close" the namespace.

The following source code shows the problems: 
```C
#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

#define LIB "libc.so.6"
#define N1 20
#define N2 10
int main(int argc, char *argv[]) {
	void *handler[N1];
	for (int i = 0; i < N1; i++) {
		handler[i] = dlmopen(LM_ID_NEWLM, LIB, RTLD_NOW);
		printf("open %d %p\n", i, handler[i]);
		if (handler[i] == NULL) {
			printf("%s", dlerror());
			break;
		}
	}
	for (int i = 0; i < N2; i++) {
		if (dlclose(handler[i]) < 0) {
			printf("close %d %p\n", i, handler[i]);
			printf("%s", dlerror());
			break;
		} else
			printf("close %d %p\n", i, handler[i]);
	}
	for (int i = 0; i < N2; i++) {
		handler[i] = dlmopen(LM_ID_NEWLM, LIB, RTLD_NOW);
		printf("reopen %d %p\n", i, handler[i]);
		if (handler[i] == NULL) {
			printf("%s", dlerror());
			break;
		}
	}
}
```

This code tries to allocate 20 (N1) namespaces. It will fail after 10 or
12 dlmopens, leaving the first loop. Then it should close 10 (N2) namespaces and
tries to dlmopen again 10 (N2) namespaces. Il will fail at the first attempt:
no namespaces are available although we've just dlclosed 10 libraries.

# Workaround

No workarounds are known at the moment. We just live with these limitations.

# Please

Dear glibc developers: 

* provide a more flexible support for dlmopen (more namespaces)
* Let dlclose de-allocate the namespace created by dlmopen.
