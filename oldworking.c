/* A spell checking program*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i;
	char *filename = argv[2];
	int maxlength = 256;
	char line[maxlength];
	char *ret;
	const char *word = line;	
	const char *entered = argv[3];
	
	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-h")  == 0)
		{
			fprintf(stderr, "Usage:\n");
			fprintf(stderr, "codeword.exe [-h/--help]		 : Print this message.\n");
			fprintf(stderr, "codeword.exe --spellcheck DICTFILE WORDS : Check spelling of words.\n");
			fprintf(stderr, "codeword.exe --anagram DICTFILE WORDS	 : Find anagrams of a word.\n");
			return 1;
		}
			
		if(strcmp(argv[i], "--help")  == 0)
		{
			fprintf(stderr, "Usage:\n");
			fprintf(stderr, "codeword.exe [-h/--help]		 : Print this message.\n");
			fprintf(stderr, "codeword.exe --spellcheck DICTFILE WORDS : Check spelling of words.\n");
			fprintf(stderr, "codeword.exe --anagram DICTFILE WORDS	 : Find anagrams of a word.\n");
			return 1;
		}
		if(strcmp(argv[i], "--spellcheck") == 0)
		{
			fprintf(stderr, "codeword.exe --spellcheck DICTFILE WORDS : Check spelling of words.\n");
			return 1;
		}
	}
//Opens the file.
	if(argv[3] == 0)
	{
		fprintf(stderr, "Please enter a filename.\n");
		return 1;
	}	
	printf("Entered value: %s\n", entered);
//Runs until the end of the dictionary file.
	if(strcmp(argv[2], "--spellcheck")  == 0)
	{
		if((argv[3] == 0)
		{
			fprintf(stderr, "Please enter a filename.\n");
			return 1;
		}
		else
		{
			FILE *fp = fopen(filename, "r");
				while(fgets(line, maxlength, fp) != NULL)
				{
					ret = strstr(word, entered);
					if(ret) printf("The  word is spelt correctly. %s\n", ret);
					return 0;
				}
		}	
		if(fp == NULL)
		{
			fprintf(stderr, "Unable to open \"%s\"\n", filename);
			return 1;
		}
	}

	
	printf("End of the file.\n");
	fclose(fp);
	return 0;
}
	



