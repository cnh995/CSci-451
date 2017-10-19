//Christian Hansen

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

pthread_t tid[10];
pthread_mutex_t lock1, lock2, lock3, lock4, lock5, lock6, lock7, lock8, lock9, lock10;
int globalIndex = 0;
int mutexMode = 0;
int state = 1;
FILE *files[2];

void* thread1(void *arg)
{
	char* tempWord;
	tempWord = malloc(sizeof(char) * 51);
	int i = 1;

	while(!feof(files[0]) && i == 1 && state != 0)
	{
		if(mutexMode == 1)
		{
			pthread_mutex_lock(&lock1);

			if(state == 1)
			{
				i = fscanf(files[0], "%s\n", tempWord);
				if(i != -1)
				{
					fprintf(files[1], "%s\tThread 1\n", tempWord);
					state = 2;
				}
				if(feof(files[0]))
				{
					state = 0;
					free(tempWord);
					pthread_mutex_unlock(&lock2);
					return NULL;
				}
			}

			
			pthread_mutex_unlock(&lock2);
		}
		else if(mutexMode == 0)
		{
			i = fscanf(files[0], "%s\n", tempWord);
			if(i == -1)
			{
				break;
			}

			fprintf(files[1], "%s\tThread 1\n", tempWord);
			sleep(1);
		}
		if(state == 0)
		{
			free(tempWord);
			pthread_mutex_unlock(&lock2);
			return NULL;
		}
	}

	free(tempWord);

	return NULL;
}

void* thread2(void *arg)
{
	char* tempWord;
	tempWord = malloc(sizeof(char) * 51);
	int i = 1;

	while(!feof(files[0]) && i == 1 && state != 0)
	{
		if(mutexMode == 1)
		{
			pthread_mutex_lock(&lock2);

			if(state == 2)
			{
				i = fscanf(files[0], "%s\n", tempWord);
				if(i != -1)
				{
					fprintf(files[1], "%s\tThread 2\n", tempWord);
					state = 3;	
				}
				if(feof(files[0]))
				{
					state = 0;
					free(tempWord);
					pthread_mutex_unlock(&lock3);
					return NULL;
				}
			}

			
			pthread_mutex_unlock(&lock3);
		}
		else if(mutexMode == 0)
		{
			i = fscanf(files[0], "%s\n", tempWord);
			if(i == -1)
			{
				break;
			}

			fprintf(files[1], "%s\tThread 2\n", tempWord);
			sleep(1);
		}
		if(state == 0)
		{
			free(tempWord);
			pthread_mutex_unlock(&lock3);
			return NULL;
		}
	}

	free(tempWord);

	return NULL;
}

void* thread3(void *output)
{
	char* tempWord;
	tempWord = malloc(sizeof(char) * 51);
	int i = 1;

	while(!feof(files[0]) && i == 1 && state != 0)
	{
		if(mutexMode == 1)
		{
			pthread_mutex_lock(&lock3);

			if(state == 3)
			{
				i = fscanf(files[0], "%s\n", tempWord);
				if(i != -1)
				{
					fprintf(files[1], "%s\tThread 3\n", tempWord);
					state = 4;
				}
				if(feof(files[0]) || i == -1)
				{
					state = 0;
					free(tempWord);
					pthread_mutex_unlock(&lock4);
					return NULL;
				}
			}
			
			pthread_mutex_unlock(&lock4);
		}
		else if(mutexMode == 0)
		{
			i = fscanf(files[0], "%s\n", tempWord);
			if(i == -1)
			{
				break;
			}

			fprintf(files[1], "%s\tThread 3\n", tempWord);
			sleep(1);
		}
		if(state == 0)
		{
			free(tempWord);
			pthread_mutex_unlock(&lock4);
			return NULL;
		}
	}

	free(tempWord);

	return NULL;
}

void* thread4(void *output)
{
	char* tempWord;
	tempWord = malloc(sizeof(char) * 51);
	int i = 1;

	while(!feof(files[0]) && i == 1 && state != 0)
	{
		if(mutexMode == 1)
		{
			pthread_mutex_lock(&lock4);

			if(state == 4)
			{
				i = fscanf(files[0], "%s\n", tempWord);
				if(i != -1)
				{
					fprintf(files[1], "%s\tThread 4\n", tempWord);
					state = 5;
				}
				if(feof(files[0]))
				{
					state = 0;
					free(tempWord);
					pthread_mutex_unlock(&lock5);
					return NULL;
				}
			}
			
			pthread_mutex_unlock(&lock5);
		}
		else if(mutexMode == 0)
		{
			i = fscanf(files[0], "%s\n", tempWord);
			if(i == -1)
			{
				break;
			}

			fprintf(files[1], "%s\tThread 4\n", tempWord);
			sleep(1);
		}
		if(state == 0)
		{
			free(tempWord);
			pthread_mutex_unlock(&lock5);
			return NULL;
		}
	}

	free(tempWord);

	return NULL;
}

void* thread5(void *output)
{
	char* tempWord;
	tempWord = malloc(sizeof(char) * 51);
	int i = 1;

	while(!feof(files[0]) && i == 1 && state != 0)
	{
		if(mutexMode == 1)
		{
			pthread_mutex_lock(&lock5);

			if(state == 5)
			{
				i = fscanf(files[0], "%s\n", tempWord);
				if(i != -1)
				{
					fprintf(files[1], "%s\tThread 5\n", tempWord);
					state = 6;
				}
				if(feof(files[0]))
				{
					state = 0;
					free(tempWord);
					pthread_mutex_unlock(&lock6);
					return NULL;
				}
			}
			
			pthread_mutex_unlock(&lock6);
		}
		else if(mutexMode == 0)
		{
			i = fscanf(files[0], "%s\n", tempWord);
			if(i == -1)
			{
				break;
			}

			fprintf(files[1], "%s\tThread 5\n", tempWord);
			sleep(1);
		}
		if(state == 0)
		{
			free(tempWord);
			pthread_mutex_unlock(&lock6);
			return NULL;
		}
	}

	free(tempWord);

	return NULL;
}

void* thread6(void *output)
{
	char* tempWord;
	tempWord = malloc(sizeof(char) * 51);
	int i = 1;

	while(!feof(files[0]) && i == 1 && state != 0)
	{
		if(mutexMode == 1)
		{
			pthread_mutex_lock(&lock6);

			if(state == 6)
			{
				i = fscanf(files[0], "%s\n", tempWord);
				if(i != -1)
				{
					fprintf(files[1], "%s\tThread 6\n", tempWord);
					state = 7;
				}
				if(feof(files[0]))
				{
					state = 0;
					free(tempWord);
					pthread_mutex_unlock(&lock7);
					return NULL;
				}
			}
			
			pthread_mutex_unlock(&lock7);
		}
		else if(mutexMode == 0)
		{
			i = fscanf(files[0], "%s\n", tempWord);
			if(i == -1)
			{
				break;
			}

			fprintf(files[1], "%s\tThread 6\n", tempWord);
			sleep(1);
		}
		if(state == 0)
		{
			free(tempWord);
			pthread_mutex_unlock(&lock7);
			return NULL;
		}
	}

	free(tempWord);

	return NULL;
}

void* thread7(void *output)
{
	char* tempWord;
	tempWord = malloc(sizeof(char) * 51);
	int i = 1;

	while(!feof(files[0]) && i == 1 && state != 0)
	{
		if(mutexMode == 1)
		{
			pthread_mutex_lock(&lock7);

			if(state == 7)
			{
				i = fscanf(files[0], "%s\n", tempWord);
				if(i != -1)
				{
					fprintf(files[1], "%s\tThread 7\n", tempWord);
					state = 8;
				}
				if(feof(files[0]))
				{
					state = 0;
					free(tempWord);
					pthread_mutex_unlock(&lock8);
					return NULL;
				}
			}
			
			pthread_mutex_unlock(&lock8);
		}
		else if(mutexMode == 0)
		{
			i = fscanf(files[0], "%s\n", tempWord);
			if(i == -1)
			{
				break;
			}

			fprintf(files[1], "%s\tThread 7\n", tempWord);
			sleep(1);
		}
		if(state == 0)
		{
			free(tempWord);
			pthread_mutex_unlock(&lock8);
			return NULL;
		}
	}

	free(tempWord);

	return NULL;
}

void* thread8(void *output)
{
	char* tempWord;
	tempWord = malloc(sizeof(char) * 51);
	int i = 1;

	while(!feof(files[0]) && i == 1 && state != 0)
	{
		if(mutexMode == 1)
		{
			pthread_mutex_lock(&lock8);

			if(state == 8)
			{
				i = fscanf(files[0], "%s\n", tempWord);
				if(i != -1)
				{
					fprintf(files[1], "%s\tThread 8\n", tempWord);
					state = 9;
				}
				if(feof(files[0]))
				{
					state = 0;
					free(tempWord);
					pthread_mutex_unlock(&lock9);
					return NULL;
				}
			}
			
			pthread_mutex_unlock(&lock9);
		}
		else if(mutexMode == 0)
		{
			i = fscanf(files[0], "%s\n", tempWord);
			if(i == -1)
			{
				break;
			}

			fprintf(files[1], "%s\tThread 3\n", tempWord);
			sleep(1);
		}
		if(state == 0)
		{
			free(tempWord);
			pthread_mutex_unlock(&lock9);
			return NULL;
		}
	}

	free(tempWord);

	return NULL;
}

void* thread9(void *output)
{
	char* tempWord;
	tempWord = malloc(sizeof(char) * 51);
	int i = 1;

	while(!feof(files[0]) && i == 1 && state != 0)
	{
		if(mutexMode == 1)
		{
			pthread_mutex_lock(&lock9);

			if(state == 9)
			{
				i = fscanf(files[0], "%s\n", tempWord);
				if(i != -1)
				{
					fprintf(files[1], "%s\tThread 9\n", tempWord);
					state = 10;
				}
				if(feof(files[0]))
				{
					state = 0;
					free(tempWord);
					pthread_mutex_unlock(&lock10);
					return NULL;
				}
			}
			
			pthread_mutex_unlock(&lock10);
		}
		else if(mutexMode == 0)
		{
			i = fscanf(files[0], "%s\n", tempWord);
			if(i == -1)
			{
				break;
			}

			fprintf(files[1], "%s\tThread 9\n", tempWord);
			sleep(1);
		}
		if(state == 0)
		{
			free(tempWord);
			pthread_mutex_unlock(&lock10);
			return NULL;
		}
	}

	free(tempWord);

	return NULL;
}

void* thread10(void *output)
{
	char* tempWord;
	tempWord = malloc(sizeof(char) * 51);
	int i = 1;

	while(!feof(files[0]) && i == 1 && state != 0)
	{
		if(mutexMode == 1)
		{
			pthread_mutex_lock(&lock10);

			if(state == 10)
			{
				i = fscanf(files[0], "%s\n", tempWord);
				if(i != -1)
				{
					fprintf(files[1], "%s\tThread 10\n", tempWord);
					state = 1;
				}
				if(feof(files[0]))
				{
					state = 0;
					free(tempWord);
					pthread_mutex_unlock(&lock1);
					return NULL;
				}
			}
			
			pthread_mutex_unlock(&lock1);
		}
		else if(mutexMode == 0)
		{
			i = fscanf(files[0], "%s\n", tempWord);
			if(i == -1)
			{
				break;
			}

			fprintf(files[1], "%s\tThread 10\n", tempWord);
			sleep(1);
		}
		if(state == 0)
		{
			free(tempWord);
			pthread_mutex_unlock(&lock1);
			return NULL;
		}
	}

	free(tempWord);

	return NULL;
}

int main(int argv, char **argc)
{
	if(argv > 2)
	{
		printf("*** Too many arguments given ***\n");
		return 0;
	}

	if(argv < 2)
	{
		printf("*** No argument given ***\n");
		return 0;
	}

	files[0] = fopen("hw7.data", "r");

	if(strcmp(argc[1], "nomutex") == 0)
	{
		mutexMode = 0;
		printf("No mutex mode\n");
		files[1] = fopen("hw7.nomutex", "w");
	}
	else if(strcmp(argc[1], "mutex") == 0)
	{
		mutexMode = 1;
		printf("Mutex mode\n");
		files[1] = fopen("hw7.mutex", "w");
	}
	else
	{
		printf("*** Unrecognized argument ***\n");
		return 0;
	}

	pthread_create(&(tid[0]), NULL, &thread1, NULL);
	pthread_create(&(tid[1]), NULL, &thread2, NULL);
	pthread_create(&(tid[2]), NULL, &thread3, NULL);
	pthread_create(&(tid[3]), NULL, &thread4, NULL);
	pthread_create(&(tid[4]), NULL, &thread5, NULL);
	pthread_create(&(tid[5]), NULL, &thread6, NULL);
	pthread_create(&(tid[6]), NULL, &thread7, NULL);
	pthread_create(&(tid[7]), NULL, &thread8, NULL);
	pthread_create(&(tid[8]), NULL, &thread9, NULL);
	pthread_create(&(tid[9]), NULL, &thread10, NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);
	pthread_join(tid[3], NULL);
	pthread_join(tid[4], NULL);
	pthread_join(tid[5], NULL);
	pthread_join(tid[6], NULL);
	pthread_join(tid[7], NULL);
	pthread_join(tid[8], NULL);
	pthread_join(tid[9], NULL);

	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);
	pthread_mutex_destroy(&lock3);
	pthread_mutex_destroy(&lock4);
	pthread_mutex_destroy(&lock5);
	pthread_mutex_destroy(&lock6);
	pthread_mutex_destroy(&lock7);
	pthread_mutex_destroy(&lock8);
	pthread_mutex_destroy(&lock9);
	pthread_mutex_destroy(&lock10);

	printf("Complete\n");

	fclose(files[0]);
	fclose(files[1]);

	return 0;
}
