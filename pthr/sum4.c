#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct limit {
	int min;
	int max;
} limit;

pthread_mutex_t lock;
int sum;

void *runner(void *param);

int main(int argc, char const* argv[])
{
	pthread_t tid[4];
	pthread_attr_t attr;
	pthread_mutex_init(&lock, NULL);

	/* if (argc !=2) */
	/* 	return -1; */
	/* if (atoi(argv[1]) < 0) */
	/* 	return -1; */
	int l = atoi(argv[1]);
	sum = 0;
	/* int l = 1000000000; */
	/* int l = 100; */
	limit limit0 = {.min = 1, .max = l/4};
	limit limit1 = {.min = l/4 + 1, .max = l/2};
	limit limit2 = {.min = l/2 + 1, .max = 3*l/4};
	limit limit3 = {.min = 3*l/4 + 1, .max = l};

	pthread_attr_init(&attr);
	pthread_create(&tid[0], &attr, runner, &limit0);
	pthread_create(&tid[1], &attr, runner, &limit1);
	pthread_create(&tid[2], &attr, runner, &limit2);
	pthread_create(&tid[3], &attr, runner, &limit3);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

	printf("Sum = %d\n", sum);
	pthread_mutex_destroy(&lock);
	return 0;
}

void *runner(void *param) {
	limit *lim = param;
	int Sum = 0;
	for (int i=lim->min; i<=lim->max; i++) {
		Sum += i;
	}
	/* pthread_mutex_lock(&lock); */
	sum += Sum;
	/* pthread_mutex_unlock(&lock); */
	pthread_exit(0);
}
