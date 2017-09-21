//Christian Hansen

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Character array containing our message
char* message[1000];
int switchingIndex = 0;

//Thread to read data from Person1.txt
void* readPerson1(void* arg)
{
	FILE *input = fopen("Person1.txt", "r");
	char tempChar;

	while(!feof(input))
	{
		fscanf(input, "%c", &tempChar);

		if(tempChar != '0')
		{
			//Adding the characters to the array isn't working for some reason
			//message[switchingIndex] = &tempChar;
			//switchingIndex++;

			//To show that the characters are being read correctly
			printf("%c", tempChar);
		}
	}
}

//Thread to read data from Person2.txt
void* readPerson2(void* arg)
{
	FILE *input = fopen("Person2.txt", "r");

	char tempChar;
			//To show that the characters are being read correctly
			printf("%c", tempChar);
		}
	}
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

	//Printing the message doesn't work
	/*int i = 0;

	while(message[i] != '\0')
	{
		printf("%c", *message[i]);
		i++;
	}*/

	return 0;
}
	while(!feof(input))
	{
		fscanf(input, "%c", &tempChar);

		if(tempChar != '0')
		{
			//Adding the characters to the array isn't working for some reason
			//message[switchingIndex] = &tempChar;
			//switchingIndex++;

			//To show that the characters are being read correctly
			printf("%c", tempChar);
		}
	}
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

	//Printing the message doesn't work
	/*int i = 0;

	while(message[i] != '\0')
	{
		printf("%c", *message[i]);
		i++;
	}*/

	return 0;
}
