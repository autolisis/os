#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


void *runner(void *param);

int main(int argc, char const* argv[])
{
	pthread_t tid1;
	pthread_attr_t attr;

	if (argc !=2)
		return -1;
	/* if (atoi(argv[1]) < 0) */
	/* 	return -1; */
	int l = atoi(argv[1]);
	/* int l = 100; */

	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, runner, &l);

	pthread_join(tid1, NULL);

	return 0;
}

void *runner(void *param) {
	int *n = param;
	int *composite = calloc(sizeof(int), *n);
	for (int i=3; i<*n; i++) {
		for (int j=2; j<i; j++) {
			if (! composite[j])
				if (i % j == 0) {
					composite[i] = 1;
				}
		}
	}
	for (int i=0; i<*n; i++) {
		if (!composite[i])
			printf("%d ", i);
	}
}

