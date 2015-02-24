/* A spell checking program*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
int i;
char *filename = argv[1];
int count = 0;
int maxlength = 256;
char line[maxlength];
char *ret;
for(i = 1; i < argc; i++)
{
	if(strcmp(argv[i], "-h")  == 0)
		{
			fprintf(stderr, "Usage:\n");
			fprintf(stderr, "codeword.exe [-h/--help]		 : Print this message.\n");
			fprintf(stderr, "codeword.exe --spellcheck DICTFILE WORDS : Check spelling of words.\n");
			fprintf(stderr, "codeword.exe --anagram DICTFILE WORDS	 : Find anagrams of a word.\n");
		}
		
	if(strcmp(argv[i], "--help")  == 0)
	{
		fprintf(stderr, "Usage:\n");
		fprintf(stderr, "codeword.exe [-h/--help]		 : Print this message.\n");
		fprintf(stderr, "codeword.exe --spellcheck DICTFILE WORDS : Check spelling of words.\n");
		fprintf(stderr, "codeword.exe --anagram DICTFILE WORDS	 : Find anagrams of a word.\n");
	}
}

FILE *fp = fopen(filename, "r");
	if(fp == NULL)
	{
		fprintf(stderr, "Unable to open \"%s\"\n", filename);
		return -1;
	}
	
const char *word = line;	
const char *entered = argv[2];

while(fgets(line, maxlength, fp) != NULL)
{
if(fgets(line, maxlength, fp) != NULL)
{
	printf("%s", line);
	ret = strstr(word, entered);
	
	printf("The  word is spelt correctly. %s\n", ret);
	
	count++;
}
else
{
	printf("end of the line");
}
	
}	
printf("There were %d lines in that file.\n", count);
	
fclose(fp);

getchar();
}

