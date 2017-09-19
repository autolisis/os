#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>

void wordCount() {

}

int main(int argc, char *argv[]) {
	if (argc > 2 || argc == 1) {
		printf("Incorrect usage.");
		exit(0);
	}
	char *filename = strdup(argv[1]);
	int fd = open(filename, O_RDONLY);
	dup2(fd, 0);
	/* execlp("wc", "wc", NULL); */
}
