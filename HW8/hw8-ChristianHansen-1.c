//Christian Hansen

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#include<errno.h>
#include<semaphore.h>

#define SEMKEY 5555

int main(void) {
	
	int id = semget(SEMKEY, 1, 0666);
	int semID = semctl(id, 0, GETVAL);

	if(semID == 1) {
		FILE* input = fopen("input.data", "r");
		FILE* output = fopen("temp1.data", "w");
		char tempLine[101];
		int i = fscanf(input, "%s ", tempLine);

		while(i == 1) {
			fprintf(output, "%s\n", tempLine);
			i = fscanf(input, "%s ", tempLine);
		}

		fclose(input);
		fclose(output);
		semctl(id, 0, SETVAL, 2);
	}

	return 0;
}
