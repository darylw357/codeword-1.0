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
	
	
	if(argc <= 1)
	{
		fprintf(stderr, "Please enter some arguments.\n");
		return 1;
	}
	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-h" )  == 0)
		{
			fprintf(stderr, "Usage:\n");
			fprintf(stderr, "codeword.exe [-h/--help]		 : Print this message.\n");
			fprintf(stderr, "codeword.exe --spellcheck DICTFILE WORDS : Check spelling of words.\n");
			fprintf(stderr, "codeword.exe --anagram DICTFILE WORDS	 : Find anagrams of a word.\n");
			return 1;
		}
			
		else if(strcmp(argv[i], "--help")  == 0)
		{
			fprintf(stderr, "Usage:\n");
			fprintf(stderr, "codeword.exe [-h/--help]		 : Print this message.\n");
			fprintf(stderr, "codeword.exe --spellcheck DICTFILE WORDS : Check spelling of words.\n");
			fprintf(stderr, "codeword.exe --anagram DICTFILE WORDS	 : Find anagrams of a word.\n");
			return 1;
		}
		else if(strcmp(argv[i], "--spellcheck") == 0)
		{
			if(argv[2] == 0)
			{
				fprintf(stderr, "Please enter a filename.\n");
				return 1;
			}
			else
			{
				FILE *fp = fopen(filename, "r");
					if(fp == NULL)
					{
						fprintf(stderr, "Unable to open \"%s\"\n", filename);
						return 1;
					}
					char *word = line;	
					 char *entered = argv[3];
					if(argv[3] != 0)
						{
							while(fgets(line, maxlength, fp) != NULL)
							{
							*ret = strstr(word, entered);
							printf("entered %s\n", entered);
							printf("dict %s\n", word);
							printf("%s\n", ret);
							if(strcmp(entered, *ret != 0) 
							{
								printf("The  word %s is spelt correctly.\n", ret);
							}

							}
						}
					else
						{
							fprintf(stderr, "Please enter a word to check.\n");
							return 1;
						}
			}
		}	
		else if(strcmp(argv[i], "--spellcheck") != 0)
		{
			fprintf(stderr, "Please enter --spellcheck as the first argument.\n");
			return 1;
		}
		
		}	
		
	
}	

	
	
/*	
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
*/
