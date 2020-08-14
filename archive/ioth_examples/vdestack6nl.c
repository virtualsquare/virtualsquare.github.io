#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <vdestack.h>
#include <nlinline+.h>
NLINLINE_LIBMULTICOMP(vde_)

static void getstatus(int signo) {
	int status;
	wait(&status);
}

void server(struct vdestack *mystack) {
	struct sockaddr_in6 servaddr, cliaddr;
	int fd, connfd;
	char buf[BUFSIZ];

	signal(SIGCHLD, getstatus);
	fd = vde_msocket(mystack, AF_INET6, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port = htons(5000);
	servaddr.sin6_addr = in6addr_any;

	if (bind(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		exit(1);

	listen (fd, 5);

	for ( ; ; ) {
		int n;
		socklen_t clilen = sizeof(cliaddr);
		connfd = accept (fd, (struct sockaddr *) &cliaddr, &clilen);

		switch (fork()) {
			case 0:
				close(fd);
				printf("new conn %d pid %d\n", connfd, getpid());
				while ( (n = recv(connfd, buf, BUFSIZ, 0)) > 0)  {
					printf("pid %d GOT: %*.*s",getpid(),n,n,buf);
					send(connfd, buf, n, 0);
				}
				printf("close conn %d pid %d\n", connfd, getpid());
				close(connfd);
				exit(0);
			default:
				close(connfd);
				break;
			case -1:
				exit(1);
		}
	}
	close(fd);
}

struct vdestack *net_setup(void) {
	struct vdestack *mystack;
	uint8_t ipv4addr[] = {10,0,0,60};
	uint8_t ipv4gw[] = {10,0,0,1};
	uint8_t ipv6addr[16] = {0xfc, 0x00, [13] = 0x1, [15] = 0x60};
	uint8_t ipv6gw[16] = {0xfc, 0x00, [13] = 0x1, [15] = 0x1};
	int ifindex;

	mystack = vde_addstack("vxvde://234.0.0.1", NULL);
	ifindex = vde_if_nametoindex(mystack, "vde0");
	if (ifindex < 0) {
		perror("nametoindex");
		exit(1);
	}

	if (vde_linksetupdown(mystack, ifindex, 1) < 0)
		perror("link up");
	if (vde_ipaddr_add(mystack, AF_INET, ipv4addr, 24, ifindex) < 0)
		perror("addr ipv4");
	if (vde_iproute_add(mystack, AF_INET, NULL, 0, ipv4gw) < 0)
		perror("route ipv4");
	if (vde_ipaddr_add(mystack, AF_INET6, ipv6addr, 64, ifindex) < 0)
		perror("addr ipv6");
	if (vde_iproute_add(mystack, AF_INET6, NULL, 0, ipv6gw) < 0)
		perror("route ipv6");

	return mystack;
}

int main(int arg, char *argv[]) {
	struct vdestack *mystack = net_setup();
	server(mystack);
	vde_delstack(mystack);
}
