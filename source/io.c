#include <unistd.h>
#include "io.h"

ssize_t _strlen(char *str) {
	ssize_t index;

	index = 0;
	if (str == 0) {
		index = -1;
	}
	while (index >= 0 && str[index]) {
		index++;
	}
	return index;
}

ssize_t io_putchar(int fd, char c) {
	return write(fd, &c, 1);
}

ssize_t io_putstr(int fd, char *str) {
	ssize_t index;

	index = 0;
	if (str == 0) {
		index = -1;
	}
	while (index >= 0 && str[index]) {
		io_putchar(fd, str[index]);
		index++;
	}
	return index;
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
