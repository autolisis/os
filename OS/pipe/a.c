#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>


int main() {
	/* pid_t pid; */

	/* if ( (pid = fork()) > (pid_t) 0) */
	fflush(stdout);
	for (int i=0; i<3; i++)	{
		fflush(stdout);
		fork();
		printf("*\n");
		fflush(stdout);
	}
	fflush(stdout);
	return 0;
}
