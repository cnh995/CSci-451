//Christian Hansen

#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<time.h>

#define SEMKEY 5555

int main(int argc, char **argv) {
	char* fileName = argv[1];
	int pipeIn = atoi(argv[2]);
	int semID = atoi(argv[3]);
	int shmid = atoi(argv[4]);
	int meID = atoi(argv[5]);
	int i = 0;
	int *sharedMem = (int*)shmat(shmid, (void *)0, 0);
	int charsRead;
	int charsToRead;
	char charID[2];
	char buffer[11];
	char outputBuffer[21];
	char charCount[8];
	char name[4];
	strcpy(name, "_p");
	sprintf(charID, "%d", meID);
	strcat(name, charID);
	name[4] = '\0';

	int input = open(fileName, O_RDONLY, 0);

	*sharedMem = -1;

	while(semctl(semID, 0, GETVAL, 0) != 1) {
	}

	if(*sharedMem < 0) {
		*sharedMem = 0;
	}

	srand(time(0) + meID);

	while(1) {
		usleep(rand() % 50000);
		int tempSemValue = semctl(semID, 0, GETVAL, 0);
		if(tempSemValue == 1) {
			semctl(semID, 0, SETVAL, 10);
			lseek(input, (long)*sharedMem, 0);
			charsToRead = (rand() % 10) + 1;
			charsRead = read(input, buffer, charsToRead);
			*sharedMem += charsRead;
			strcpy(outputBuffer, name);
			if(charsRead == charsToRead) {
				buffer[charsRead] = '\0';
				strcat(outputBuffer, buffer);
				buffer[0] = '\0'; ////////////////////////////
				write(pipeIn, outputBuffer, strlen(outputBuffer) + 1);
				semctl(semID, 0, SETVAL, 100 + meID);
			} else {
				sprintf(charCount, "%d", *sharedMem);
				strcat(outputBuffer, buffer);printf("%s\n", buffer);
				strcat(outputBuffer, charCount);
				outputBuffer[strlen(outputBuffer)] = '\0';
				write(pipeIn, outputBuffer, strlen(outputBuffer) + 1);
				semctl(semID, 0, SETVAL, 200 + meID);
			}
		} else if(tempSemValue >= 300) {
			close(input);
			close(pipeIn);
			shmdt(sharedMem);
			semctl(semID, 0, SETVAL, tempSemValue + 1);
			return 0;
		}
	}

	close(input);
	close(pipeIn);
	shmdt(sharedMem);
	return 0;
}
