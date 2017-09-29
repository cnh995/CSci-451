//Christian Hansen

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int globalInt;
enum {state1, state2} state = state1;
pthread_t tid[2];
pthread_mutex_t lock;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

void* thread1(void *arg)
{
	int i = 0;
	int tempInt;
	FILE *input = fopen("hw4.in", "r");

	while(!feof(input))
	{
		pthread_mutex_lock(&lock);

		while(state != state1)
			pthread_cond_wait(&cond1, &lock);


		fscanf(input, "%d\n", &globalInt);
		printf("%d\n", globalInt);

		//pthread_mutex_lock(&lock);
		state = state2;
		pthread_cond_signal(&cond2);
		pthread_mutex_unlock(&lock); printf("\nnow\n");
	}

	fclose(input);
	return NULL;
}

void* thread2(void *output)
{
	pthread_mutex_lock(&lock);

	while(state != state2)
		pthread_cond_wait(&cond2, &lock);

	if(2 % 2 == 0)
		printf("\n%d", globalInt);

	if(globalInt % 2 != 0)
	{printf("\nhere\n");
		fprintf(output, "%d\n", globalInt);
	}
	else
	{
		fprintf(output, "%d\n", globalInt);
		fprintf(output, "%d\n", globalInt);
	}

	state = state1;
	pthread_cond_signal(&cond1);
	pthread_mutex_unlock(&lock);

	return NULL;
}

int main(void)
{
	FILE* output = fopen("hw4.out", "w");

	pthread_create(&(tid[0]), NULL, &thread1, NULL);
	pthread_create(&(tid[1]), NULL, &thread2, (void*)output);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	pthread_mutex_destroy(&lock);

	fclose(output);

	return 0;
}
