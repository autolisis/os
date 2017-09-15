#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>

int startsWith(const char *a, const char *b) {
	if(strncmp(a, b, strlen(b)) == 0)
		return 1;
	else
		return 0;
}

void parse(char *line, char **argv) {
	while (*line != '\0') {
		while (*line == ' ' || *line == '\t' || *line == '\n')
			*line++ = '\0';
		*argv++ = line;
		while (*line != '\0' && *line != ' ' &&
			*line != '\t' && *line != '\n')
		line++;
	}
	*argv = '\0';
}

void execute(char **argv) {
	pid_t pid;
	int status;

	if ((pid = fork()) < 0) {
		printf("*** ERROR: forking child process failed\n");
		exit(1);
	}
	else if (pid == 0) {
		if (execvp(*argv, argv) < 0) {
			printf("*** ERROR: exec failed\n");
			exit(1);
		}
	}
	else {
		while (wait(&status) != pid)
		;
	}
}

char * executeNthCommand(char *line) {
	int val = atol(line+1);
	int savedPos = where_history();
	HIST_ENTRY *nthElement = history_get(savedPos - val);
	return nthElement->line;
}

int main(void) {
	char *argv[64];

	using_history();
	read_history(".gshist");
	while (1) {
		char *line = readline("$ ->\t");
		if (startsWith(line, "!"))
			line = executeNthCommand(line);
		if (line)
			add_history(line);
		parse(line, argv);
		if (strcmp(argv[0], "exit") == 0) {
			write_history(".gshist");
			exit(0);
		}
		execute(argv);
		free(line);
	}
}
