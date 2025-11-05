#include <unistd.h>

int main(void) {
	write(STDOUT_FILENO, "Hello world", 11);
	return 0;
}
