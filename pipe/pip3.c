#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/* #include <fstream> */
/* #include <iostream> */
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
// #include <cstdio>

/* using namespace std; */

int mypipe[2];
/* Read characters from the pipe and echo them to stdout. */

void closeFD(int dummy) {
	printf("CLOSING FD");
	fflush(NULL);
	close (mypipe[1]);
	exit(0);
}

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
	FILE *stream;
	stream = fdopen (file, "w");

	char str[100];
	gets(str);
	/* fflush(stdin); */
	/* fflush(stdout); */
	while (strlen(str) >0) {
		fprintf(stream, "%s\n", str);
		gets(str);
		/* fflush(stdin); */
		/* fflush(stdout); */
	}
	// scanf("%s", &str);
	/* fflush(stdin); */
	/* fflush(stdout); */
	fflush(stream);
	fclose (stream);
}

int
main (void) {
	pid_t pid;
	int sav = dup(mypipe[0]);

	/* Create the pipe. */
	if (pipe (mypipe)) {
		perror("Pipe failed.\n");
		return EXIT_FAILURE;
	}

	/* Create the child process. */
	pid = fork();
	if (pid == (pid_t) 0) {
		/* This is the child process.
		Close other end first. */
		close (mypipe[1]);
		close(STDIN_FILENO);
		/* dup2(mypipe[0], 0); */
		/* open(mypipe[0]); */
		read_from_pipe (sav);
		return EXIT_SUCCESS;
	}
	else if (pid < (pid_t) 0) {
		/* The fork failed. */
		perror("Fork failed\n");
	}
	else {
		/* This is the parent process.
		Close other end first. */
		close (mypipe[0]);
		signal(SIGINT, closeFD);
		write_to_pipe (mypipe[1]);
		wait(NULL);
		return EXIT_SUCCESS;
	}
}
