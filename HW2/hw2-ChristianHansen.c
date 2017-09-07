//Christian Hansen
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t PID;
	PID = fork();

	if(PID == 0)
	{
		fork();
		execl("/usr/bin/xeyes", "xeyes");
		fork();
		execv("hw2-ChristianHansen", NULL);
		fork();
	}

	return 0;
}
