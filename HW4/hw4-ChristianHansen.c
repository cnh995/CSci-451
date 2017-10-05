//Christian Hansen

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int globalInt;
int state;
pthread_t tid[2];
pthread_mutex_t lock1, lock2;

void* thread1(void *arg)
{
	int i = 1;
	int tempInt;
	FILE *input = fopen("hw4.in", "r");

	while(i == 1)
	{
		pthread_mutex_lock(&lock1);

		if(state == 0)
			state++;

		i = fscanf(input, "%d\n", &globalInt);

		pthread_mutex_unlock(&lock2);
	}

	state++;

	fclose(input);
	return NULL;
}

void* thread2(void *output)
{
	while(state <= 1)
	{
		pthread_mutex_lock(&lock2);
		if(state == 1)
		{
			if(globalInt % 2 != 0)
			{
				fprintf(output, "%d\n", globalInt);
			}
			else
			{
				fprintf(output, "%d\n", globalInt);
				fprintf(output, "%d\n", globalInt);
			}
		}

		pthread_mutex_unlock(&lock1);
	}

	return NULL;
}

int main(void)
{
	state = 0;

	FILE* output = fopen("hw4.out", "w");

	pthread_create(&(tid[0]), NULL, &thread1, NULL);
	pthread_create(&(tid[1]), NULL, &thread2, (void*)output);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);

	fclose(output);

	return 0;
}
