#include "inet.h"
#include "io.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define ERR_PREF "[ERR]"

#define FAMILY AF_INET
#define TYPE SOCK_STREAM

int inet_init(inet_info_t *info) {
	int ret;

	ret = 0;
	info->socket_fd = socket( FAMILY, TYPE, 0);
	if (info->socket_fd == -1) {
#ifdef LOG
		io_putstr(STDERR_FILENO, ERR_PREF " ");
		io_putstr(STDERR_FILENO, strerror(errno));
		io_putstr(STDERR_FILENO, " Failed to create socket\n");
#endif
		ret = -1;
	}
	return ret;
}

int inet_close(inet_info_t *info) {
	int ret;

	ret = close(info->socket_fd);
	if (ret == 0) {
		info->socket_fd = -1;
	} else {
#ifdef LOG
		io_putstr(STDERR_FILENO, ERR_PREF " ");
		io_putstr(STDERR_FILENO, strerror(errno));
		io_putstr(STDERR_FILENO, " Failed to close socket\n");
#endif
		ret = -1;
	}
	return ret;
}

int inet_set_addr(inet_info_t *info, char *r_addr, int r_port) {
	struct sockaddr_in _addr;
	int ret;

	_addr.sin_family = FAMILY;
	_addr.sin_addr.s_addr = inet_addr(r_addr);
	_addr.sin_port = htons(r_port);
	ret = bind(
		info->socket_fd,
		(struct sockaddr*)&_addr,
		sizeof(struct sockaddr_in));
#ifdef LOG
	if (ret == -1) {
		io_putstr(STDERR_FILENO, ERR_PREF " ");
		io_putstr(STDERR_FILENO, strerror(errno));
		io_putstr(STDERR_FILENO, " Failed to set address and port\n");
	}
#endif
	return ret;
}

int inet_listen(inet_info_t *server, int backlog) {
	int ret;

	ret = listen(server->socket_fd, backlog);
#ifdef LOG
	if (ret == -1) {
		io_putstr(STDERR_FILENO, ERR_PREF " ");
		io_putstr(STDERR_FILENO, strerror(errno));
		io_putstr(STDERR_FILENO, " Failed to set socket as listening\n");
	}
#endif
	return ret;
}

inet_info_t inet_accept(inet_info_t *server) {
	inet_info_t client;
	struct sockaddr_in _addr;
	socklen_t _len;

	_len = sizeof(struct sockaddr_in);
	client.socket_fd = accept(
		server->socket_fd,
		(struct sockaddr*)&_addr,
		&_len);
	if (client.socket_fd != -1) {
		client.addr = _addr.sin_port;
		client.addr = _addr.sin_addr.s_addr;
	}
#ifdef LOG
	else {
		io_putstr(STDERR_FILENO, ERR_PREF " ");
		io_putstr(STDERR_FILENO, strerror(errno));
		io_putstr(STDERR_FILENO, " Failed accept client connection\n");
	}
#endif
	return client;
}

int inet_send_to(inet_info_t *dst, char *str) {
	int ret;

	ret = io_putstr(dst->socket_fd, str);
	if (ret == -1) {
#ifdef LOG
		io_putstr(STDERR_FILENO, ERR_PREF " ");
		io_putstr(STDERR_FILENO, strerror(errno));
		io_putstr(STDERR_FILENO, " Failed to send data to client\n");
#endif
	}
	return ret;
}

int inet_receive_from(inet_info_t *src, char *str, int size) {
	int ret;

	ret = read(src->socket_fd, str, size);
	if (ret == -1) {
#ifdef LOG
		io_putstr(STDERR_FILENO, ERR_PREF " ");
		io_putstr(STDERR_FILENO, strerror(errno));
		io_putstr(STDERR_FILENO, " Failed to receive data to client\n");
#endif
	}
	return ret;
}

void in_addr_to_readable(in_addr_t addr, char *r_addr) {
	struct in_addr _addr;

	_addr.s_addr = addr;
	inet_ntop(FAMILY, &_addr, r_addr, INET_ADDRSTRLEN);
	r_addr[INET_ADDRSTRLEN] = 0;
}

int in_port_to_readable(in_port_t port) {
	return ntohs(port);
}
