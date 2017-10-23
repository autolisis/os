#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define THREADS 2

/* typedef (void*)(*runFunction)( void* ); */
typedef void* (*runFunction)( void * );

typedef struct limit{
	int l;
	int h;
	int p;
}limit;

runFunction runner[THREADS];

int *arr;
pthread_mutex_t lock;

void * quickSort(void *);
int choosePivot(void *);
int * makeLTArray(limit *lim);

void runnerInit() {
	runner[0] = &quickSort;
}


int main(int argc, char const* argv[])
{
	pthread_t tid[THREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_mutex_init(&lock, NULL);
	printf("Enter size of array:");
	int n; scanf("%d", &n);
	arr = calloc(sizeof(int), n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	limit lim = {.l=0, .h=n, .p=-1};

	runnerInit();
	/* void *a = &(struct {int a; int b};); */
	pthread_create(&tid[0], &attr, runner[0], &lim);

	pthread_join(tid[0], NULL);
	return 0;
}

void * quickSort(void *param) {
	limit *lim = param;
	lim->p = choosePivot(lim);
	int *lessThanSum = makeLTArray(lim);
	pthread_exit(0);
}

int *sumarr;
int * makeSumArray(int *LTarr, limit *lim) {
	int lg = 0, tem = lim->h;
	while (tem >>= 1) { ++lg; };
	for (int i = 0; i < lg; i++) {
	}
}
int * makeLTArray(limit *lim) {
	int *LTarr = calloc(sizeof(int), lim->h);
	*sumarr = calloc(sizeof(int), lim->h);
	for (int i = 0; i < lim->h; i++)
		LTarr[i] = (arr[i] <= arr[lim->p])? 1 : 0;
	makeSumArray(LTarr, lim);

}

void * partition(void *param) {
	pthread_exit(0);
}
