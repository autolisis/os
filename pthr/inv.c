#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *runner(void *param);

double **A, **inv;
double del;

size_t n;
typedef struct matIndex {
	int i;
	int j;
} matIndex;

void initMatrix(double ***a, int m, int n);
void getMatrix(double ***a, int m, int n);
pthread_mutex_t lock;
pthread_attr_t attr;

double determinant(double **a, int n);
void inverse();

int main(int argc, char const *argv[]) {
	printf("Enter the dimensions of the matrix:\n");
	scanf("%lu", &n);

	initMatrix(&A, n, n);
	getMatrix(&A, n, n);

	printf("Determinant = %lf\n", determinant(A,n));
	inverse();
	printf("Matrix inv = inverse(A)\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%lf ", inv[i][j]);
		}
		printf("\n");
	}

	return 0;
}

double determinant(double **a, int n) {
	if (n == 1)
		return a[0][0];
	if (n == 2)
		return a[0][0] * a[1][1] - a[1][0] * a[0][1];
	int det = 0, sign=1;
	for (int j1 = 0; j1 < n; j1++) {
		double **m = calloc((n - 1), sizeof(double *));
		for (int i = 0; i < n - 1; i++)
			m[i] = calloc((n - 1), sizeof(double));
		for (int i = 1; i < n; i++) {
			int j2 = 0;
			for (int j = 0; j < n; j++) {
				if (j == j1)
					continue;
				m[i - 1][j2] = a[i][j];
				j2++;
			}
		}
		det += sign * a[0][j1] * determinant(m, n - 1);
		sign = -sign;
		for (int i = 0; i < n - 1; i++)
			free(m[i]);
		free(m);
	}
	return det;
}

void inverse() {
	del = determinant(A,n);
	if (del == 0)
		exit(0);

	initMatrix(&inv, n, n);

	pthread_attr_init(&attr);
	pthread_mutex_init(&lock, NULL);

	pthread_t **tidMat = calloc(sizeof(pthread_t *), n);
	for (int i = 0; i < n; i++) {
		tidMat[i] = calloc(sizeof(pthread_t), n);
	}
	matIndex curIndex = {.i = 0, .j = 0};
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			pthread_mutex_lock(&lock);
			curIndex.i = i; curIndex.j = j;
			pthread_create(&tidMat[i][j], &attr, runner, &curIndex);
		}
	}
}

void *runner(void *param) {
	matIndex *index = param;
	int indexI = index->i;
	int indexJ = index->j;
	pthread_mutex_unlock(&lock);

	double **B;
	initMatrix(&B, n - 1, n - 1);
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-1; j++) {
			B[i][j] = A[(i+indexI+1)%n][(j+indexJ+1)%n];
		}
	}
	double det = determinant(B, n-1);
	/* if ((indexI + indexJ) %2 != 0) */
	/* 	det = -det; */
	inv[indexJ][indexI] = det / del;

	pthread_exit(0);
}

void initMatrix(double ***a, int m, int n) {
	*a = calloc(sizeof(int *), m);
	for (int i = 0; i < m; i++) {
		(*a)[i] = calloc(sizeof(int), n);
	}
}

void getMatrix(double ***a, int m, int n) {
	printf("Input matrix\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%lf", &(*a)[i][j]);
		}
	}
}
