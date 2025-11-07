#ifndef INET_H
#define INET_H

#include <netinet/in.h>

typedef struct {
	int socket_fd;
	in_addr_t addr;
	in_port_t port;
} inet_info_t;

int inet_init(inet_info_t *info);
int inet_close(inet_info_t *info);

int inet_set_addr(inet_info_t *info, char *r_addr, int r_port);
int inet_listen(inet_info_t *server, int backlog);
inet_info_t inet_accept(inet_info_t *server);

int inet_send_to(inet_info_t *dst, char *str);
int inet_receive_from(inet_info_t *src, char *str, int size);

char *in_addr_to_str(in_addr_t addr);
char *in_port_to_str(in_port_t port);

#endif // INET_H
