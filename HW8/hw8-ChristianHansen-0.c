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
	pid_t child1;
	pid_t child2;
	pid_t child3;
	int child1Done = 0;
	int child2Done = 0;
	int child3Done = 0;

	int id = semget(SEMKEY, 1, 0666 | IPC_CREAT);
	semctl(id, 0, SETVAL, 0);
	int semID = semctl(id, 0, GETVAL);

	child1 = fork();
	child2 = fork();

	if(child1 < 0 && child2 < 0) {
		printf("Fork error\n");
	}

	if(child1 == 0 && child1Done == 0) {
		if(semID == 0) {
			semctl(id, 0, SETVAL, 1);
			int run1 = system("./hw8-ChristianHansen-1");
		}
		child1Done = 1;
	}

	if(child2 == 0 && child1Done == 1 && child2Done == 0) {
		int run2 = system("./hw8-ChristianHansen-2");
		child2Done = 1;
	}

	child3 = fork();

	if(child3 < 0) {
		printf("Fork error\n");
	}
	if(child3 == 0 && child1Done == 1 && child2Done == 1 && child3Done == 0) {
		int run3 = system("./hw8-ChristianHansen-3");
		child3Done = 1;
	}

	if(child1Done == 1 && child2Done == 1 && child3Done == 1) {
		kill(child1, SIGTERM);
		kill(child2, SIGTERM);
		kill(child3, SIGTERM);
	}

	return 0;
}
