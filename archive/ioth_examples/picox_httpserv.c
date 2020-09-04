/*   
 *   vdestack_httpserv.c: IoTh tiny web server
 *   
 *   Copyright 2011-2020 Renzo Davoli - Virtual Square Team 
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
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <picoxnet.h>
#include <nlinline+.h>
NLINLINE_LIBMULTI(picox_)

#define BUFSIZE 10240

static char *http_head =  "HTTP/1.1 %d OK\r\n%sContent-Length: %d\r\n\r\n";
static char *ishtml = "Content-Type: text/html\r\n";

static char *html_head =  "<HTML>\n<HEAD>\n<TITLE>vdestack IoTh http server</TITLE>\n</HEAD>\n<BODY>\n<H1>%s</H1>\n";
static char *html_tail =  "</BODY></HTML>\n";

static void httpserv_senderr(int fd)
{
	char *msg, *header;
	size_t size;
	FILE *f = open_memstream(&msg, &size);
	fprintf(f, html_head, "404: File not Found");
	fprintf(f, html_tail);
	fclose(f);
	asprintf(&header, http_head, 404, ishtml, size);
	picox_write(fd, header, strlen(header));
	picox_write(fd, msg, size);
	free(header);
	free(msg);
}

static void httpserv_sendfile(int fd, char *path)
{
	char buf[BUFSIZE];
	int infd = open(path, O_RDONLY);
	if (infd > 0) {
		int n;
		char *header;
		struct stat statbuf;
		fstat(infd, &statbuf);
		if (strlen(path)>5 && strcmp(path+(strlen(path)-5), ".html") == 0)
			asprintf(&header, http_head, 200, ishtml, statbuf.st_size);
		else
			asprintf(&header, http_head, 200, "", statbuf.st_size);
		picox_write(fd, header, strlen(header));
		free(header);
		while ((n = read(infd, buf, BUFSIZE))>0) {
			picox_write(fd, buf, n);
		}
		close(infd);
	}
}

static void httpserv_senddir(int fd, char *path, char *webpath)
{ 
	int i,n;
	char *msg, *header, *lastslash;
	struct dirent **namelist;
	size_t size;
	FILE *f=open_memstream(&msg, &size);
	fprintf(f, html_head, (*webpath) ? webpath : "/ (root)");
	if (path == webpath) {
		lastslash = strrchr(webpath, '/');
		if (lastslash) {
			int len = lastslash - webpath;
			fprintf(f, "<p><a href=\"/%*.*s\"> .. </a></p>\n", len, len, webpath);
		} else
			fprintf(f, "<p><a href=\"/\"> .. </a></p>\n");
	}
	n = scandir(path, &namelist, NULL, alphasort);
	for (i = 0; i < n; i++) {
		if (namelist[i]->d_name[0] != '.') {
			fprintf(f,"<p><a href=\"%s/%s\"> %s </a></p>\n",
					webpath, namelist[i]->d_name, namelist[i]->d_name);
		}
		free(namelist[i]);
	}
	free(namelist);
	fprintf(f, html_tail);
	fclose(f);
	asprintf(&header, http_head, 200, ishtml, size);
	picox_write(fd, header, strlen(header));
	picox_write(fd, msg, size);
	free(header);
	free(msg);
}


void *handle(void *arg)
{
	int fd = (uintptr_t) arg;
	char buf[BUFSIZE];
	char *end;
	int  n = picox_read(fd, buf, BUFSIZE);
	if (n > 0) {
		if (strncmp(buf, "GET /", 5) == 0 && (end = strchr(buf+4, ' ')) != NULL){
			struct stat sbuf;
			*end = 0;
			if (buf[5] == 0)
				httpserv_senddir(fd, ".", buf+5);
			else if (buf[5] != '/' && strstr(buf+4, "/../") == NULL && stat(buf+5, &sbuf)==0) {
				if (S_ISREG(sbuf.st_mode))
					httpserv_sendfile(fd, buf+5);
				if (S_ISDIR(sbuf.st_mode))
					httpserv_senddir(fd, buf+5, buf+5);
			} else
				httpserv_senderr(fd);
		}
	}
	picox_close(fd);
	return NULL;
}

static void perror_exit(char *s) {
	perror(s);
	exit(1);
}

int main(int arg, char *argv[]) {
#define VDENET argv[1]
#define IPADDR argv[2]
#define PREFIX argv[3]
	int fd, connfd;
	struct picox *mystack = picox_newstack(VDENET);
	uint8_t ipaddr[16];
	int ifindex = picox_if_nametoindex(mystack, "vde0");
	unsigned long prefix = strtoul(PREFIX, NULL, 10);
	if (picox_linksetupdown(mystack, ifindex, 1) < 0)
		perror_exit("link up");
	if (inet_pton(AF_INET6, IPADDR, ipaddr) == 1) {
		struct sockaddr_in6 servaddr = {
			.sin6_family = AF_INET6,
			.sin6_port = htons(80),
			.sin6_addr = in6addr_any};
		if (picox_ipaddr_add(mystack, AF_INET6, ipaddr, prefix, ifindex) < 0)
			perror_exit(IPADDR);
		fd = picox_msocket(mystack, AF_INET6, SOCK_STREAM, 0);
		if (picox_bind(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
			perror_exit("bind");
	} else if (inet_pton(AF_INET, IPADDR, ipaddr) == 1) {
		struct sockaddr_in servaddr = {
			.sin_family = AF_INET,
			.sin_port = htons(80),
			.sin_addr.s_addr = htonl(INADDR_ANY)};
		if (picox_ipaddr_add(mystack, AF_INET, ipaddr, prefix, ifindex) < 0)
			perror_exit(IPADDR);
		fd = picox_msocket(mystack, AF_INET, SOCK_STREAM, 0);
		if (picox_bind(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
			perror_exit("bind");
	} else {
		errno = EPROTO;
		perror_exit("error");
	}

	picox_listen (fd, 5);

	for ( ; ; ) {
		pthread_t pt;
		connfd = picox_accept(fd, NULL, NULL);
		if (connfd < 0)
			break;
		pthread_create(&pt, NULL, handle, (void *) (uintptr_t)connfd);
		pthread_detach(pt);
	}
	picox_close(fd);
	picox_delstack(mystack);
}
