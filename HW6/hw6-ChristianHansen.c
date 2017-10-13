//Christian Hansen

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_t tid[] = {100, 200, 300, 400};
pthread_mutex_t lock1, lock2, lock3, lock4;
int pages[5000][3]; //pages[x][0] - pid, pages[x][1] - R, pages[x][2] - M
int flag = 0;

void* thread1(void *arg)
{
	if(flag == 0)
	{
		flag++;
		while(1)
		{
			pthread_mutex_lock(&lock1);
			int randPage = rand() % 5000;
			int randOperation = rand() % 2;
		
			if(pages[randPage][0] == 0)
			{
				if(randOperation == 0)
				{printf("%d %d - 1\n", randPage, randOperation);
					pages[randPage][0] = 100;
					pages[randPage][1] = 1;
					pages[randPage][2] = 0;
				}
				else
				{
					pages[randPage][0] = 100;
					pages[randPage][1] = 1;
					pages[randPage][2] = 1;
				}
			}
			else if(pages[randPage][0] == 100 || pages[randPage][0] == 200 || pages[randPage][0] == 300)
				printf("Page fault\n");

			pthread_mutex_unlock(&lock2);
		}
	}
	return NULL;
}

void* thread2(void *arg)
{
	if(flag == 1)
	{
		flag++;
		while(1)
		{
			pthread_mutex_lock(&lock2);
			int randPage = rand() % 5000;
			int randOperation = rand() % 2;
			
			if(pages[randPage][0] == 0)
			{
				if(randOperation == 0)
				{printf("%d %d - 2\n", randPage, randOperation);
					pages[randPage][0] = 200;
					pages[randPage][1] = 1;
					pages[randPage][2] = 0;
				}
				else
				{
					pages[randPage][0] = 200;
					pages[randPage][1] = 1;
					pages[randPage][2] = 1;
				}
			}
			else if(pages[randPage][0] == 100 || pages[randPage][0] == 200 || pages[randPage][0] == 300)	
				printf("Page fault\n");

			pthread_mutex_unlock(&lock3);
		}
	}

	return NULL;
}

void* thread3(void *arg)
{
	if(flag == 2)
	{
		flag++;
		while(1)
		{
			pthread_mutex_lock(&lock3);
			int randPage = rand() % 5000;
			int randOperation = rand() % 2;
			
			if(pages[randPage][0] != 100 || pages[randPage][0] != 200 || pages[randPage][0] != 300)
			{
				if(randOperation == 0)
				{printf("%d %d - 3\n", randPage, randOperation);
					pages[randPage][0] = 300;
					pages[randPage][1] = 1;
					pages[randPage][2] = 0;
				}
				else
				{
					pages[randPage][0] = 300;
					pages[randPage][1] = 1;
					pages[randPage][2] = 1;
				}
			}
			else if(pages[randPage][0] == 100 || pages[randPage][0] == 200 || pages[randPage][0] == 300)
				printf("Page fault\n");
	
			pthread_mutex_unlock(&lock4);
		}
	}

	return NULL;
}

void* thread4(void *arg)
{
	if(flag == 3)
	{
		while(1)
		{
			int i = 0;
			pthread_mutex_lock(&lock4);
	
			for(i; i < 5000; i++)
			{
	
				if(pages[i][1] == 1)
				{
					printf("Resetting R\n");
					pages[i][1] = 0;
					if(pages[i][2] == 1)
					{
						pages[i][2] = 0;
						printf("Resetting M\n");
						printf("Simulating print\n");
						int wait = time(0) + 1;
						while(time(0) < wait);
					}
					
				}pages[i][0] = 0;
			}
	
			pthread_mutex_unlock(&lock1);
		}
	}
}

int main(void)
{
	int seed = time(NULL);
	srand(seed);

	int i, j;

	for(i = 0; i < 5000; i++)
	{
		for(j = 0; j < 3; j++)
		{
			pages[i][j] = 0;
		}
	}

	pthread_create(&(tid[100]), NULL, &thread1, NULL);
	pthread_create(&(tid[200]), NULL, &thread2, NULL);
	pthread_create(&(tid[300]), NULL, &thread3, NULL);
	pthread_create(&(tid[400]), NULL, &thread4, NULL);

	pthread_join(tid[100], NULL);
	pthread_join(tid[200], NULL);
	pthread_join(tid[300], NULL);
	pthread_join(tid[400], NULL);

	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);
	pthread_mutex_destroy(&lock3);
	pthread_mutex_destroy(&lock4);

	return 0;
}
