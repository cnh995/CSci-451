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

char vowels[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
char symbols[] = {'.', ',', '!', ';', '\'', '\"', '(', ')'};

int main(void) {
	int id = semget(SEMKEY, 1, 0666);
	int semID = semctl(id, 0, GETVAL);

	if(semID == 2) {
		FILE *input = fopen("temp1.data", "r");
		FILE *output = fopen("temp2.data", "w");
		FILE *shared1 = fopen("shared1.dat", "w");
		FILE *shared2 = fopen("shared2.dat", "w");

		char tempLine[101];
		char newLine[101];
		char tempChar;
		char tempChar2;
		int i = 1;
		int j = 0;
		int k = 0;
		int l = 0;
		int vowelStart = 0;
		int consonantStart = 0;
		semctl(id, 0, SETVAL, 0);

		while(fscanf(input, "%s\n", tempLine) == 1) {
			for(j; j < 10; j++) {
				if(vowels[j] == tempLine[0]) {
					vowelStart++;

					k = strlen(tempLine);

					for(l; l < 8; l++) {
						if(symbols[l] == tempLine[k - 1]) {
							tempChar = tempLine[k - 1];
							tempLine[k - 1] = 'r';
							tempLine[k] = 'a';
							tempLine[k + 1] = 'y';
							tempLine[k + 2] = tempChar;
							tempLine[k + 3] = '\0';
							break;
						} else if(l == 7) {
							tempLine[k] = 'r';
							tempLine[k + 1] = 'a';
							tempLine[k + 2] = 'y';
							tempLine[k + 3] = '\0';
						}
					}
			
					break;

				} else if(j == 9) {
					consonantStart++;

					k = strlen(tempLine);

					for(l; l < 8; l++) {
						if(symbols[l] == tempLine[k - 1]) {
							tempChar = tempLine[k - 1];
							tempChar2 = tempLine[0];
							l = 0;

							for(l; l < strlen(tempLine); l++) {
								if(l < strlen(tempLine) - 1) {
									tempLine[l] = tempLine[l + 1];
								} else {
									tempLine[l - 1] = tempChar2;
								}
							}

							tempLine[k - 1] = 'a';
							tempLine[k] = 'y';
							tempLine[k + 1] = tempChar;
							tempLine[k + 2] = '\0';
							break;
						} else if(l == 7) {
							tempChar2 = tempLine[0];
							l = 0;

							for(l; l < strlen(tempLine); l++) {
								if(l < strlen(tempLine) - 1) {
									tempLine[l] = tempLine[l + 1];
								} else {
									tempLine[l] = tempChar2;
								}
							}
							tempLine[k] = 'a';
							tempLine[k + 1] = 'y';
							tempLine[k + 2] = '\0';
							break;
						}
					}
				}
			}
			l = 0;
			j = 0;
			fprintf(output, "%s\n", tempLine);
		}

		fprintf(shared1, "%d\n", vowelStart);
		fprintf(shared2, "%d\n", consonantStart);

		fclose(shared1);
		fclose(shared2);
		fclose(input);
		fclose(output);
		semctl(id, 0, SETVAL, 3);
	}

	return 0;
}
