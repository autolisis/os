#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct limit {
	int min;
	int max;
} limit;

int sum;

void *runner(void *param);

int main(int argc, char const* argv[])
{
	pthread_t tid1;
	pthread_attr_t attr;

	/* if (argc !=2) */
	/* 	return -1; */
	/* if (atoi(argv[1]) < 0) */
	/* 	return -1; */
	int l = atoi(argv[1]);
	sum = 0;
	/* int l = 100; */
	limit limit1 = {.min = 1, .max = l};
	int scope;
	pthread_attr_getscope(&attr, &scope);
	if (scope == PTHREAD_SCOPE_PROCESS)
		printf("scope = %d\n", scope);

	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, runner, &limit1);

	pthread_join(tid1, NULL);

	printf("Sum = %d\n", sum);
	return 0;
}

void *runner(void *param) {
	limit *lim = param;

	for (int i=lim->min; i<=lim->max; i++) {
		sum += i;
	}
	pthread_exit(0);
}
