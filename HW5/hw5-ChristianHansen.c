//Christian Hansen

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

char globalChar;
int state = 0;
int globalFlag = 0;
int printFlag = 0;
pthread_t tid[3];
pthread_mutex_t lock1, lock2, lock3, lockMain;

void* thread1(void *arg)
{
	int i = 1;
	int tempInt;
	FILE *input = fopen("hw5-1.in", "r");
printf("\nhere1\n");
	while(i == 1 && globalFlag == 0)
	{
		pthread_mutex_lock(&lock1);

		if(state == 1)
		{
			i = fscanf(input, "%c\n", &globalChar);

			if(i == 0 || globalChar == '\0')
				globalFlag = 1;
			else
			{
				printFlag = 1;
				pthread_mutex_unlock(&lockMain);
			}

			printf("1 %c\n", globalChar);
		}
	}

	state++;

	fclose(input);
	return NULL;
}

void* thread2(void *output)
{
	int i = 1;
	int tempInt;
	FILE *input = fopen("hw5-2.in", "r");
printf("\nhere2\n");
	while(i == 1 && globalFlag == 0)
	{
		pthread_mutex_lock(&lock2);

		if(state == 2)
		{
			i = fscanf(input, "%c\n", &globalChar);

			if(i == 0 || globalChar == '\0')
				globalFlag = 1;
			else
			{
				printFlag = 1;
				pthread_mutex_unlock(&lockMain);
			}

			printf("2 %c\n", globalChar);
		}
	}

	state++;

	fclose(input);
	return NULL;
}

void* thread3(void *output)
{
	int i = 1;
	int tempInt;
	FILE *input = fopen("hw5-3.in", "r");
printf("\nhere3\n");
	while(i == 1 && globalFlag == 0)
	{
		pthread_mutex_lock(&lock3);

		if(state == 3)
		{
			i = fscanf(input, "%c\n", &globalChar);

			if(i == 0 || globalChar == '\0')
				globalFlag = 1;
			else
			{
				printFlag = 1;
				pthread_mutex_unlock(&lockMain);
			}

			printf("3 %c\n", globalChar);
		}
	}

	state++;

	fclose(input);
	return NULL;
}

int main(void)
{
	FILE* output = fopen("hw5.out", "w");

	pthread_create(&(tid[0]), NULL, &thread1, NULL);
	pthread_create(&(tid[1]), NULL, &thread2, NULL);
	pthread_create(&(tid[2]), NULL, &thread3, NULL);

	while(globalFlag == 0)
	{
		pthread_mutex_lock(&lockMain);

		if(printFlag == 1)
		{
			if(globalChar == '\0')
				break;

			fprintf(output, "%c\n", globalChar);printf("\nhere print\n");

			printFlag = 0;
		}

		if(state == 1)
		{
			state = 2;
			pthread_mutex_unlock(&lock2);
		}
		else if(state == 2)
		{
			state = 3;
			pthread_mutex_unlock(&lock3);
		}
		else if(state == 3 || state == 0)
		{
			state = 1;
			pthread_mutex_unlock(&lock1);
		}
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);

	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);
	pthread_mutex_destroy(&lock3);
	pthread_mutex_destroy(&lockMain);

	fclose(output);

	return 0;
}
