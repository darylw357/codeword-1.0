/* A spell checking program*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
int i;
char *filename = argv[2];
int count = 0;
int maxlength = 100;
char line[maxlength];

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

FILE *fp = fopen(filename, "words");
	if(fp == NULL)
	{
		fprintf(stderr, "Unable to open \"%s\"\n", filename);
		return -1;
	}
while(fgets(line, maxlength, fp) != NULL)
{
	count++;
}	
	
fclose(fp);


}
