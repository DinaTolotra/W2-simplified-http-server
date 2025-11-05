#ifndef IO_H
#define IO_H

#include <unistd.h>

ssize_t io_putchar(int fd, char c);
ssize_t io_putstr(int fd, char *str);

ssize_t io_getchar(int fd, char *c);

#endif // IO_H
