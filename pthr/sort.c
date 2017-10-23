#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define THREADS 2

typedef struct state{
	int *Copy;
	int *LTarr;
	int l;
	int h;
	int n;
	int pinitial;
	int pfinal;
	int pivot;
}state;

int *arr;

void quickSort(state *cur);
void choosePivot(state *cur);
int * makeLTArray(state *cur);
void * leftRunner(void *param);
void * pivotRunner(void *param);
void * rightRunner(void *param);

int main(int argc, char const* argv[])
{
	printf("Enter size of array:");
	int n; scanf("%d", &n);
	arr = calloc(sizeof(int), n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	state cur = {.l=0, .h=n, .n=n, .pinitial=-1, .pfinal = -1};
	quickSort(&cur);
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}

void * putLTPart(void *param) {
	state *cur = param;
	int *LTarr = cur->LTarr;
	int lindex = cur->l;
	for (int i = 0; i < cur->h-cur->l; i++) {
		if (LTarr[i]) {
			arr[lindex++] = cur->Copy[cur->l + i];
		}
	}
	state Left = {.n=cur->n, .l = cur->l, .h = cur->pfinal, .pfinal = -1};
	quickSort(&Left);
	return NULL;
}

void * putPivot(void *param) {
	state *cur = param;
	arr[cur->pfinal] = cur->pivot;
	return NULL;
}

void * putGTPart(void *param) {
	state *cur = param;
	int *LTarr = cur->LTarr;
	int lindex = cur->pfinal + 1;
	for (int i = 0; i < cur->h-cur->l; i++) {
		if (i==cur->pinitial-cur->l)
			continue;
		if (!LTarr[i]) {
			arr[lindex++] = cur->Copy[cur->l + i];
		}
	}
	state Right = {.n=cur->n, .l = cur->pfinal + 1, .h = cur->h, .pfinal = -1};
	quickSort(&Right);
	return NULL;
}

void choosePivot(state *cur) {
	cur->pinitial = (cur->h - cur->l)/2;
	if (arr[cur->h-1] > arr[cur->l]) {
		if (arr[cur->l] > arr[cur->pinitial])
			cur->pinitial = cur->l;
	}
	else {
		if (arr[cur->pinitial] > arr[cur->l])
			cur->pinitial= cur->l;
		else
			cur->pinitial = cur->h-1;
	}
	cur->pivot = cur->Copy[cur->pinitial];
}
void quickSort(state *cur) {
	if (cur->h - cur->l <= 1)
		return;
	cur->Copy = calloc(1, (cur->h - cur->l) * sizeof(int));
	memcpy(cur->Copy, arr+cur->l, sizeof(int)*(cur->h-cur->l));
	/* for (int i = cur->l; i < cur->h; i++) { */
	/* 	cur->Copy[i] = arr[i]; */
	/* } */
	choosePivot(cur);
	cur->LTarr = makeLTArray(cur);

	pthread_t tid[3];

	pthread_create(&tid[0], NULL, putLTPart, cur);
	/* printf("Thread Created\n"); */
	pthread_create(&tid[1], NULL, putPivot, cur);
	/* printf("Thread Created\n"); */
	pthread_create(&tid[2], NULL, putGTPart, cur);
	/* printf("Thread Created\n"); */

	for (int i = 0; i < 3; i++) {
		pthread_join(tid[i], NULL);
		/* printf("Thread Exited\n"); */

	}
	free(cur->LTarr);

	free(cur->Copy);
}

int * makeLTArray(state *cur) {
	int *LTarr = calloc(sizeof(int), cur->h - cur->l);
	int sum = 0;
	for (int i = 0; i < cur->h-cur->l; i++) {
		LTarr[i] = (cur->Copy[cur->l + i] < cur->pivot)? 1 : 0;
		sum+=LTarr[i];
	}
	cur->pfinal = sum+cur->l;
	return LTarr;
}
