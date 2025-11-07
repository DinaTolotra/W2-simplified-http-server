#ifndef IO_H
#define IO_H

#include <unistd.h>

ssize_t io_putchar(int fd, const char c);
ssize_t io_putstr(int fd, const char *str);
ssize_t io_putnchar(int fd, const char *str, unsigned int n);
ssize_t io_putnb(int fd, const int nb);

ssize_t io_getchar(int fd, char *c);

#endif // IO_H
