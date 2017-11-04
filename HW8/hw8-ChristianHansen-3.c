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

	if(semID == 3) {
		FILE* input = fopen("temp2.data", "r");
		FILE* input2 = fopen("shared1.dat", "r");
		FILE* input3 = fopen("shared2.dat", "r");
		FILE* output = fopen("temp3.data", "w");
		char tempLine[101];
		int tempInt;
		int i = fscanf(input, "%s\n", tempLine);
		fscanf(input2, "%i\n", &tempInt);
		printf("Type 1: %d\n", tempInt);
		fscanf(input3, "%i\n", &tempInt);
		printf("Type 2: %d\n", tempInt);

		while(i == 1) {
			fprintf(output, "%s ", tempLine);
			i = fscanf(input, "%s\n", tempLine);
		}

		fclose(input);
		fclose(input2);
		fclose(input3);
		fclose(output);
		semctl(id, 0, IPC_RMID);
	}

	return 0;
}
