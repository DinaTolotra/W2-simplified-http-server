#include <unistd.h>
#include "io.h"

ssize_t _strlen(const char *str) {
	ssize_t index;

	index = 0;
	while (str[index]) {
		index++;
	}
	return index;
}

ssize_t io_putchar(int fd, const char c) {
	return write(fd, &c, 1);
}

ssize_t io_putstr(int fd, const char *str) {
	ssize_t index;

	index = 0;
	while (str[index]) {
		io_putchar(fd, str[index]);
		index++;
	}
	return index;
}

ssize_t io_putnchar(int fd, const char *str, unsigned int n) {
	ssize_t index;

	index = 0;
	while (index < n) {
		io_putchar(fd, str[index]);
		index++;
	}
	return index;
}

ssize_t _putnb(int fd, unsigned int lnb) {
	ssize_t count;

	count = 0;
	if (lnb >= 10)
		count = _putnb(fd, lnb / 10);
	io_putchar(fd, (lnb % 10) + '0');
	return count + 1;
}

ssize_t io_putnb(int fd, int nb) {
	ssize_t count;
	long lnb;

	lnb = nb;
	count = 0;
	if (lnb < 0) {
		lnb = -lnb;
		io_putchar(fd, '-');
		count++;
	}
	return count + _putnb(fd, (unsigned int)lnb);
}

ssize_t io_getchar(int fd, char *c) {
	ssize_t count;

	if (c == 0) {
		count = -1;
	} else {
		count = read(fd, c, 1);
	}
	return count;
}
