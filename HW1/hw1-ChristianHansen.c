//Christian Hansen
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int file_size(FILE *inputFile)
{
	int size = 0;
	char temp = fgetc(inputFile);

	//Increment size for each line break until the end of the file
	while(temp != EOF)
	{
		if(temp == '\n')
			size++;
		
		temp = fgetc(inputFile);
	}

	return size;	
}

static char *extract_link(char string[])
{
        static char url[256];
        int length;
        char *tempString1;
        char *tempString2;
        url[0] = '\0';
        tempString1 = strstr(string, "http://");
        if (!(tempString1) || (*(tempString1) == '\0'))
                goto https;
        if (((tempString1) || (*(tempString1) == '\0')) && strchr(tempString1, ' '))
        {
                tempString2 = strstr(tempString1, " ");
                length = strlen(tempString1) - strlen(tempString2);
                strncpy(url, tempString1, length);
                return url;
        }
        else
                return tempString1;
	https:
		tempString1 = strstr(string, "https://");
		if(!(tempString1) || (*(tempString1) == '\0'))
			goto www;
		if(((tempString1) || (*(tempString1) == '\0')) && strchr(tempString1, ' '))
		{
			tempString2 = strstr(tempString1, " ");
                        length = strlen(tempString1) - strlen(tempString2);
                        strncpy(url, tempString1, length);
                        return url;
                }
                else
                        return tempString1;
        www:
                tempString1 = strstr(string, "www.");
                if (!(tempString1) || (*(tempString1) == '\0'))
                        return NULL;
                if(((tempString1) || (*(tempString1) == '\0')) && strchr(tempString1, ' '))
                {
                        tempString2 = strstr(tempString1, " ");
                        length = strlen(tempString1) - strlen(tempString2);
                        strncpy(url, tempString1, length);
                        return url;
                }
                else
                        return tempString1;
}

int main(void)
{
	//Part 1
	system("wget --quiet --output-document input.txt http://www.senate.gov/general/contact_information/senators_cfm.cfm");

	//Part 2
	FILE *input = fopen("input.txt", "r");
	int i, j;
	int size = file_size(input);
	char *temp;
	int xSize;

	fseek(input, 0, SEEK_SET);

	for(i = 0; i < size; i++)
	{
		fscanf(input, "%s", &*temp);
		char *x = extract_link(temp);
		if(x != NULL)
		{
			xSize = strlen(x);
			for(j = 0; j < xSize; j++)
			{
				if(x[j] == '"')
				{
					x[j] = '\0';
					break;
				}
			}
			printf("\n%s", x);
		}
	}

	printf("\n");

	//Part 3
	//system("unlink input.txt");

	return 0;
}
