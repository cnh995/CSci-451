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
	if(argc < 2) {
		printf("***** Too few arguments supplied *****\n");
		return 0;
	}
	else if(argc > 2) {
		printf("***** Too many arguments supplied *****\n");
		return 0;
	}

	int output = creat("hw11.out", 0666);
	char buffer[21];

	int semID = semget(SEMKEY, 1, 0666 | IPC_CREAT);
	semctl(semID, 0, SETVAL, 99999);

	if(semID < 0) {
		printf("Error obtaining semaphore.\n");
		return 0;
	}

	int pipeID[9][2];
	int i = 0;

	for(i; i < 9; i++) {
		pipe(pipeID[i]); //0 - out, 1 - in
	}

	int shmid = shmget(5757, sizeof(int), 0666 | IPC_CREAT);

	i = 0;

	for(i; i < 9; i++) {
		pid_t _p = fork();

		if(_p == 0) {
			close(*pipeID[0]);
			char semIDString[8];
			sprintf(semIDString, "%d", semID);
			char pipeIn[9];
			sprintf(pipeIn, "%d", pipeID[i][1]);
			char sharedMem[9];
			sprintf(sharedMem, "%d", shmid);
			char reindeerID[2];
			sprintf(reindeerID, "%d", i + 1);
			char* arg[] = {argv[0], argv[1], pipeIn, semIDString, sharedMem, reindeerID, (char*)NULL};
			execvp("./p", arg);
			return 0;
		}
	}

	semctl(semID, 0, SETVAL, 1);

	while(1) {
		int processID = semctl(semID, 0, GETVAL, 0);
		if(processID >= 100 && processID <= 110) {
			read(pipeID[processID - 101][0], buffer, sizeof(buffer));
			write(output, buffer, strlen(buffer));
			semctl(semID, 0, SETVAL, 1);
		} else if(processID >= 200 && processID <= 210) {
			read(pipeID[processID - 201][0], buffer, sizeof(buffer));
			write(output, buffer, strlen(buffer));
			semctl(semID, 0, SETVAL, 300);
			break;
		}
	}

	while(1) {
		int processID = semctl(semID, 0, GETVAL, 0);
		if(processID >= 309) {
			break;
		}
	}

	i = 0;

	for(i; i < 9; i++) {
		close(pipeID[i][0]);
		close(pipeID[i][1]);
	}

	close(output);
	semctl(semID, 0, IPC_RMID, 0);
	semctl(shmid, 0, IPC_RMID, 0);
	return 0;
}
