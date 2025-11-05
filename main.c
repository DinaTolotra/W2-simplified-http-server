#include "io.h"

#define stdio_putchar(c) io_putchar(STDOUT_FILENO, c)
#define stdio_putstr(str) io_putstr(STDOUT_FILENO, str)
#define stdio_getchar(c) io_getchar(STDIN_FILENO, c)

int main(void) {
	stdio_putstr("Hello world");
	return 0;
}
