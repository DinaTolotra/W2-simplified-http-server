#include "io.h"
#include "inet.h"

#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 1024
#define NOT_FOUND_HEADER "HTTP/1.1 404 NOT FOUND\n" "\n"
#define HEADER "HTTP/1.1 200 OK\n" "Content-type: application/octet-stream\n" "\n"

void cycle_addr(inet_info_t *server, char *r_addr, int *r_port);
void send_file(inet_info_t *dst, char *file_name);

void log_error();

int main(int ac, char **av) {
	inet_info_t server;
	inet_info_t client;
	char buf[BUF_SIZE];
	char *file_name;
	char *r_addr;
	int r_port;
	int ret;

	r_port = 3000;
	r_addr = "0.0.0.0";
	file_name = av[ac != 1];

	ret = inet_init(&server);
	if (ret == -1) {
		log_error();
		return errno;
	}
	cycle_addr(&server, r_addr, &r_port);

	io_putstr(STDOUT_FILENO, "Server started at ");
	io_putstr(STDOUT_FILENO, r_addr);
	io_putchar(STDOUT_FILENO, ':');
	io_putnb(STDOUT_FILENO, r_port);
	io_putchar(STDOUT_FILENO, '\n');
	ret = inet_listen(&server, 1);
	if (ret == -1) {
		log_error();
		inet_close(&server);
		return errno;
	}

	client = inet_accept(&server);

	inet_receive_from(&client, buf, BUF_SIZE);
	send_file(&client, file_name);

	inet_close(&client);
	inet_close(&server);
	return 0;
}

void cycle_addr(inet_info_t *server, char *r_addr, int *r_port) {
	ssize_t ret;
	int stop;

	stop = 0;
	while (!stop) {
		ret = inet_set_addr(server, r_addr, *r_port);
		if (ret == -1) (*r_port)++;
		else stop = 1;
	}
}

void send_file(inet_info_t *dst, char *file_name) {
	char buf[BUF_SIZE];
	int ret;
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1) {
		log_error();
		inet_send_to(dst, NOT_FOUND_HEADER);
		return ;
	}
	inet_send_to(dst, HEADER);
	while ((ret = read(fd, buf, BUF_SIZE))) {
		write(dst->socket_fd, buf, ret);
	}
}

void log_error() {
	io_putstr(STDERR_FILENO, "[ERR ");
	io_putnb(STDERR_FILENO, errno);
	io_putchar(STDERR_FILENO, ']');
	io_putstr(STDERR_FILENO, strerror(errno));
	io_putchar(STDERR_FILENO, '\n');
}
