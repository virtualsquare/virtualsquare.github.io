/*   
 *   tinychat.c: mini chat
 *   
 *   Copyright 2020 Renzo Davoli - Virtual Square Team 
 *   University of Bologna - Italy
 *   
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License along
 *   with this program; if not, write to the Free Software Foundation, Inc.,
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#include <picoxnet.h>
#include <nlinline+.h>

NLINLINE_LIBMULTI(picox_)

#define MAXFD 10
#define BUFSIZE 1024

static void perror_exit(char *s) {
	perror(s);
	exit(1);
}

int main(int arg, char *argv[]) {
#define VDENET argv[1]
#define IPADDR argv[2]
#define PREFIX argv[3]
#define PORT argv[4]
	unsigned long prefix = strtoul(PREFIX, NULL, 10);
	unsigned long port = strtoul(PORT, NULL, 10);
	struct picox *mystack = picox_newstack(VDENET);
	int ifindex = picox_if_nametoindex(mystack, "vde0");
	uint8_t ipaddr[16];
	struct pollfd pfd[MAXFD] = { [0 ... MAXFD-1] = {-1, POLLIN, 0} };
	char buf[BUFSIZE];
	if (picox_linksetupdown(mystack, ifindex, 1) < 0)
		perror_exit("link up");
	// is IPADDR (argv[2])  a IPv6 address? 
	if (inet_pton(AF_INET6, IPADDR, ipaddr) == 1) {
		struct sockaddr_in6 servaddr = {
			.sin6_family = AF_INET6,
			.sin6_port = htons(port),
			.sin6_addr = in6addr_any};
		if (picox_ipaddr_add(mystack, AF_INET6, ipaddr, prefix, ifindex) < 0)
			perror_exit(IPADDR);
		pfd[0].fd = picox_msocket(mystack, AF_INET6, SOCK_STREAM, 0);
		if (picox_bind(pfd[0].fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
			perror_exit("bind");
		// is IPADDR (argv[2])  a IPv4 address? 
	} else if (inet_pton(AF_INET, IPADDR, ipaddr) == 1) {
		struct sockaddr_in servaddr = {
			.sin_family = AF_INET,
			.sin_port = htons(port),
			.sin_addr.s_addr = htonl(INADDR_ANY)};
		if (picox_ipaddr_add(mystack, AF_INET, ipaddr, prefix, ifindex) < 0)
			perror_exit(IPADDR);
		pfd[0].fd = picox_msocket(mystack, AF_INET, SOCK_STREAM, 0);
		if (picox_bind(pfd[0].fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
			perror_exit("bind");
	} else {
		errno = EPROTO;
		perror_exit("error");
	}

	picox_listen (pfd[0].fd, 5);

	for ( ; ; ) {
		int i;
		if (poll(pfd, MAXFD, -1) < 0)
			break;

		// pfd[0].fd is the socket for accept
		if (pfd[0].revents) {
			int connfd;
			connfd = picox_accept (pfd[0].fd, NULL, NULL);
			for (i = 1; i < MAXFD; i++) {
				if (pfd[i].fd == -1)
					break;
			}
			if ( i < MAXFD)
				pfd[i].fd = connfd;
			else
				picox_close(connfd);
		}
		// pfd[i].fd, i > 0, connected sockets
		for (i = 1; i < MAXFD; i++) {
			if (pfd[i].revents) {
				int n = picox_read(pfd[i].fd, buf, BUFSIZE);
				if (n <= 0) {
					picox_close(pfd[i].fd);
					pfd[i].fd = -1;
				} else {
					int j;
					// copy the message to all the other connected sockets
					for (j = 1; j < n; j++) {
						if (i != j && pfd[j].fd != -1)
							picox_write(pfd[j].fd, buf, n);
					}
				}
			}
		}
	}
	picox_close(pfd[0].fd);
	picox_delstack(mystack);
}
