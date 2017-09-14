//Christian Hansen

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Character array containing our message


char** message;
int switchingIndex = 0;

//Thread to read data from Person1.txt
void* readPerson1(void* arg)
{
	FILE *input1 = fopen("Person1.txt", "r");
	char tempChar;
	int i = 0;

	while(!feof(input1))
	{
		fscanf(input1, "%c", tempChar);

		if(tempChar == '0')
			switchingIndex = i;
		else
			message[i] = tempChar;

		i++;
	}
}

//Thread to read data from Person2.txt
void* readPerson2(void* arg)
{
	FILE *input1 = fopen("Person2.txt", "r");
}

int main(void)
{
	pthread_t tid1;
	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_create(&tid1, &attr1, readPerson1, &switchingIndex);
	pthread_join(tid1, NULL);

	pthread_t tid2;
	pthread_attr_t attr2;
	pthread_attr_init(&attr2);
	pthread_create(&tid2, &attr2, readPerson2, &switchingIndex);
	pthread_join(tid2, NULL);

	printf("%s\n", message);

	return 0;
}
