#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *runner(void *param);

int **A, **B, **C;
size_t m1, n1, m2, n2;
typedef struct matIndex { int i; int j; }matIndex;

void initMatrix(int ***a, int m, int n);
void getMatrix(int ***a, int m, int n);
pthread_mutex_t lock;
pthread_mutex_t threadLock;

int THREADS = 4;


int main(int argc, char const* argv[])
{
	printf("Enter the dimensions of matrix 1:\n");
	scanf("%lu", &m1);
	scanf("%lu", &n1);
	printf("Enter the dimensions of matrix 2:\n");
	scanf("%lu", &m2);
	scanf("%lu", &n2);
	if (n1 != m2){
		perror("Not multipliable");
		exit(EXIT_FAILURE);
	}
	initMatrix(&A, m1, n1);
	getMatrix(&A, m1, n1);

	initMatrix(&B, m2, n2);
	getMatrix(&B, m2, n2);

	initMatrix(&C, m1, n2);

	pthread_t **tidMat = calloc(sizeof(pthread_t *), m1);
	for (int i = 0; i < m1; i++) {
		tidMat[i] = calloc(sizeof(pthread_t), n2);
	}

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_init(&threadLock, NULL);
	matIndex curIndex = {.i=0, .j=0};

	for (int i = 0; i < m1; i++) {
		for (int j = 0; j < n2; j++) {
			printf("THREADS = %d", THREADS);
			pthread_mutex_lock(&lock);
			curIndex.i = i; curIndex.j = j;
			pthread_create(&tidMat[i][j], &attr, runner, &curIndex);
			pthread_mutex_lock(&threadLock);
			THREADS--;
			pthread_mutex_unlock(&threadLock);
			while (THREADS == 0);
			printf("THREADS = %d", THREADS);
			pthread_join(tidMat[i][j], NULL);
		}
	}

	for (int i = 0; i < m1; i++) {
		for (int j = 0; j < n2; j++) {
			pthread_join(tidMat[i][j], NULL);
		}
	}
	printf("Matrix C = A x B\n");
	for (int i = 0; i < m1; i++) {
		for (int j = 0; j < n2; j++) {
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}
	/* pthread_join(tid1, NULL); */
	return 0;
}

void *runner(void *param) {
	matIndex *index = param;
	int indexI = index->i;
	int indexJ = index->j;
	pthread_mutex_unlock(&lock);

	for (int k = 0; k < m2; k++) {
		C[indexI][indexJ] += A[indexI][k] * B[k][indexJ];
	}


	pthread_mutex_lock(&threadLock);
	THREADS++;
	pthread_mutex_unlock(&threadLock);
	pthread_exit(0);
}

void initMatrix(int ***a, int m, int n) {
	*a = calloc(sizeof(int *), m);
	for (int i = 0; i < m; i++) {
		(*a)[i] = calloc(sizeof(int), n);
	}
}

void getMatrix(int ***a, int m, int n) {
	printf("Input matrix\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &(*a)[i][j]);
		}
	}
}
