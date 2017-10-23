#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void * runner(void *param) {
	printf("%d", getpid());
	fflush(NULL);
	pthread_exit(0);
}

int main(int argc, char const* argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

	int scope;
	pthread_attr_getscope(&attr, &scope);
	if (scope == PTHREAD_SCOPE_PROCESS)
		printf("PTHREAD SCOPE PROCESS\n");
	if (scope == PTHREAD_SCOPE_SYSTEM)
		printf("PTHREAD SCOPE SYSTEM");

	scope = PTHREAD_SCOPE_PROCESS;
	pthread_attr_setscope(&attr, scope);
	int sched;

	pthread_attr_getschedpolicy(&attr, &sched);
	if (sched == SCHED_FIFO)
		printf("SCHED FIFO\n");
	if (sched == SCHED_RR)
		printf("SCHED RR\n");
	if (sched == SCHED_OTHER)
		printf("SCHED OTHER\n");

	sched = SCHED_RR;
	pthread_attr_setschedpolicy(&attr, sched);

	pthread_attr_getschedpolicy(&attr, &sched);
	if (sched == SCHED_FIFO)
		printf("SCHED FIFO\n");
	if (sched == SCHED_RR)
		printf("SCHED RR\n");
	if (sched == SCHED_OTHER)
		printf("SCHED OTHER\n");

	pthread_attr_getscope(&attr, &scope);
	if (scope == PTHREAD_SCOPE_PROCESS)
		printf("PTHREAD SCOPE PROCESS\n");
	if (scope == PTHREAD_SCOPE_SYSTEM)
		printf("PTHREAD SCOPE SYSTEM");

	pthread_create(&tid, NULL, runner, NULL);
	printf("%d", getpid());
	fflush(NULL);

	return 0;
}
