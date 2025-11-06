#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include "io.h"

#define stdio_putchar(c) io_putchar(STDOUT_FILENO, c)
#define stdio_putstr(str) io_putstr(STDOUT_FILENO, str)
#define stderr_putstr(str) io_putstr(STDERR_FILENO, str)
#define stdio_getchar(c) io_getchar(STDIN_FILENO, c)

int main(void) {
	struct sockaddr_in addr, cli_addr;
	socklen_t len;
	int sockfd;
	int cli_sockfd;
	int fd;
	char buf[1024];
	int ret;

	addr.sin_port = htons(3000);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");

	sockfd = socket(addr.sin_family,
					SOCK_STREAM,
					0);
	if (sockfd == -1) {
		stderr_putstr("[ERR] Socket call error\n");
		return errno;
	} else {
		stdio_putstr("Socket created\n");
	}

	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	if (ret == -1) {
		stderr_putstr("[ERR] Bind call error\n");
		close(sockfd);
		return errno;
	} else {
		stdio_putstr("Socket binded to address\n");
	}

	stdio_putstr("Listening...\n");
	ret = listen(sockfd, 10);
	if (ret == -1) {
		stderr_putstr("[ERR] Listen call error\n");
		close(sockfd);
		return errno;
	}

	cli_sockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &len);
	if (cli_sockfd == -1) {
		stderr_putstr("[ERR] Listen call error\n");
		close(sockfd);
		return errno;
	} else {
		stdio_putstr("Client connected\n");
	}

	read(cli_sockfd, buf, 1024);
	stdio_putstr(buf);
	fd = open("asset/index.html", O_RDONLY);
	io_putstr(cli_sockfd,
			"HTTP/1.1 200 OK\n"
			"content-type: text/html\n"
			"\n"
	);
	while ((ret = read(fd, buf, 1024))) {
		write(cli_sockfd, buf, ret);
	}

	ret = close(sockfd);
	if (ret == -1) {
		stderr_putstr("[ERR] Close call error\n");
		return errno;
	} else {
		stdio_putstr("Socket closed\n");
	}
	return 0;
}
