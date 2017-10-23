#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct limit {
	int min;
	int max;
} limit;

pthread_mutex_t *lock;
int *count; char *str; int max = 0;
size_t l = 0;

void getString();

void * runner(void *param);

int main(int argc, char const* argv[])
{
	getString();
	l = strlen(str);
	count = calloc(26, sizeof(int));
	pthread_t tid[4];

	lock = malloc(sizeof(pthread_mutex_t) * 26);
	for (int i = 0; i < 26; i++) {
		pthread_mutex_init(&lock[i], NULL);
	}
	limit limit0 = {.min = 0, .max = l/4};
	limit limit1 = {.min = l/4 + 1, .max = l/2};
	limit limit2 = {.min = l/2 + 1, .max = 3*l/4};
	limit limit3 = {.min = 3*l/4 + 1, .max = l};

	pthread_create(&tid[0], NULL, runner, &limit0);
	pthread_create(&tid[1], NULL, runner, &limit1);
	pthread_create(&tid[2], NULL, runner, &limit2);
	pthread_create(&tid[3], NULL, runner, &limit3);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

	printf("Entered string is: %s\n", str);
	int norm = log(max)*3;
	for (int i = 0; i < 26; i++) {
		if (count[i] == 0)
			continue;
		printf("%c\t(%d)\t|", 'A'+i, count[i]);

		for (int equal = 0; equal < count[i]/norm; equal++) {
			printf("=");
		}
		if (count[i]%norm != 0)
			printf("-");
		printf("\n");
	}
	printf("\n1 equal = %d\n", norm);

	for (int i = 0; i < 26; i++) {
		pthread_mutex_destroy(&lock[i]);
	}
}
void * runner(void *param) {
	limit *lim = param;
	for (int i = lim->min; i <= lim->max; i++) {
		if (isalpha(str[i])) {
			pthread_mutex_lock(&lock[tolower(str[i]) - 'a']);
			count[tolower(str[i]) - 'a']++;
			pthread_mutex_unlock(&lock[tolower(str[i]) - 'a']);
			if (count[tolower(str[i]) - 'a'] > max)
				max = count[tolower(str[i]) - 'a'];
		}
	}
	pthread_exit(0);
}

void getString() {
	size_t size = 100;
	int ch;
	size_t len = 0;
	str = realloc(NULL, sizeof(char)*size);//size is start size
	while(EOF!=(ch=getc(stdin))){
		str[len++]=ch;
		if(len==size){
			str = realloc(str, sizeof(char)*(size+=16));
		}
	}
	str[len++]='\0';
}
