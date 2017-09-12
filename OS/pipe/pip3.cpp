#include <sys/types.h>
#include <unistd.h>
// #include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

/* Read characters from the pipe and echo them to stdout. */

void
read_from_pipe (int file) {
	FILE *stream;
	int c;
	stream = fdopen (file, "r");
	while ((c = fgetc (stream)) != EOF)
		putchar (c);
	fclose (stream);
}

/* Write some random text to the pipe. */

void
write_to_pipe (int file) {
	file = 0;
	FILE *stream;
	stream = fdopen (file, "w");
	fprintf (stream, "goodbye, world!\n");
	fclose (stream);
}

int
main (void) {
	pid_t pid;
	int mypipe[2];

	/* Create the pipe. */
	if (pipe (mypipe)) {
		cerr << "Pipe failed.\n";
		return EXIT_FAILURE;
	}

	/* Create the child process. */
	pid = fork();
	if (pid == (pid_t) 0) {
		/* This is the child process.
			 Close other end first. */
		close (mypipe[1]);
		dup2(mypipe[0], 0);
		read_from_pipe (mypipe[0]);
		return EXIT_SUCCESS;
	}
	else if (pid < (pid_t) 0) {
		/* The fork failed. */
		cerr << "Fork failed\n";
		return EXIT_FAILURE;
	}
	else {
		/* This is the parent process.
			 Close other end first. */
		close (mypipe[0]);
		write_to_pipe (mypipe[1]);
		return EXIT_SUCCESS;
	}
}
