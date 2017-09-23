//Christian Hansen

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct
{
	char *message;
}MESSAGE;

MESSAGE myMessage;
pthread_t tid[2];
int messageIndex;
pthread_mutex_t lock;

void* readPerson1(void *arg)
{
	int i = 0;
	char tempChar;
	FILE *input = fopen("Person1", "r");
	tempChar = getc(input);

	while (tempChar != EOF)
	{
		pthread_mutex_lock(&lock);
		for(i; i < messageIndex; i++)
		{
			tempChar = fgetc(input);
			if(tempChar == '\n')
				tempChar = fgetc(input);
			if(tempChar == EOF)
				break;
		}

		while((tempChar != EOF) && (tempChar != '0'))
		{
			if(tempChar != '\n')
			{
				myMessage.message[messageIndex] = tempChar;
				tempChar = getc(input);
				i++;

				if(tempChar != '0')
					messageIndex++;
			}
			else
				tempChar = getc(input);
		}
		pthread_mutex_unlock(&lock);
	}

	fclose(input);
	return NULL;
}

void* readPerson2(void *arg)
{
	int i = 0;
	char tempChar;
	FILE *input = fopen("Person2", "r");
	tempChar = getc(input);

	while (tempChar != EOF)
	{
		pthread_mutex_lock(&lock);
		for(i; i < messageIndex; i++)
		{
			tempChar = fgetc(input);
			if(tempChar == '\n')
				tempChar = fgetc(input);
			if(tempChar == EOF)
				break;
		}

		while((tempChar != EOF) && (tempChar != '0'))
		{
			if(tempChar != '\n')
			{
				myMessage.message[messageIndex] = tempChar;
				tempChar = getc(input);
				i++;

				if(tempChar != '0')
					messageIndex++;
			}
			else
				tempChar = getc(input);
		}
		pthread_mutex_unlock(&lock);
	}

	fclose(input);
	return NULL;
}

int main(void)
{
	myMessage.message = (char*)malloc(501*sizeof(char));
	messageIndex = 0;

	pthread_create(&(tid[0]), NULL, &readPerson1, NULL);
	pthread_create(&(tid[1]), NULL, &readPerson2, NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_mutex_destroy(&lock);

	printf("%s\n", myMessage.message);

	return 0;
}
