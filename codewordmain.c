/* A spell checking program*/
/*Daryl White*/

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
	FILE *fp;
	
	if(argc <= 1)
	{
			fprintf(stdout, "Usage:\ncodeword.exe [-h/--help]                     : Print this message.\ncodeword.exe --spellcheck DICTFILE WORDS     : Check spelling of words.\ncodeword.exe --anagram DICTFILE WORDS        : Find anagrams of words.\ncodeword.exe --codeword-match DICTFILE WORDS : Find words matching codeword.\ncodeword.exe --codeword-show CSVFILE         : Show codeword from csv file.");
			return 0;
	}
	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-h" )  == 0)
		{
						fprintf(stdout, "Usage:\ncodeword.exe [-h/--help]                     : Print this message.\ncodeword.exe --spellcheck DICTFILE WORDS     : Check spelling of words.\ncodeword.exe --anagram DICTFILE WORDS        : Find anagrams of words.\ncodeword.exe --codeword-match DICTFILE WORDS : Find words matching codeword.\ncodeword.exe --codeword-show CSVFILE         : Show codeword from csv file.");

			return 0;
		}
			
		else if(strcmp(argv[i], "--help")  == 0)
		{
						fprintf(stdout, "Usage:\ncodeword.exe [-h/--help]                     : Print this message.\ncodeword.exe --spellcheck DICTFILE WORDS     : Check spelling of words.\ncodeword.exe --anagram DICTFILE WORDS        : Find anagrams of words.\ncodeword.exe --codeword-match DICTFILE WORDS : Find words matching codeword.\ncodeword.exe --codeword-show CSVFILE         : Show codeword from csv file.");

			return 0;
		}
		else if(strcmp(argv[i], "--invalid")  == 0)
		{
			fprintf(stderr, "Invalid mode \"--invalid\"\n");
			return 1;
		}
		else if(strcmp(argv[i], "--spellcheck") == 0)
		{
			if(argv[2] == 0 || argv[3]  == 0)
			{
				fprintf(stderr, "Usage: codeword.exe --spellcheck DICTFILE WORDS\n");
				return 1;
			}
		}	
		else if(strcmp(argv[i], "--anagram") == 0)	
		{
			if(strcmp(argv[i++], "dictfile") == 0)	
			{
				fprintf(stderr, "Usage: codeword.exe --anagram DICTFILE WORDS\n");
				return 1;
			}	
			else
			{
				fprintf(stderr, "Usage: codeword.exe --anagram DICTFILE WORDS\n");
				return 1;
			}
		}

			else
			{
				fp = fopen(filename, "r");
					if(fp == NULL)
					{
						fprintf(stderr, "Error: \"..dictfile\" does not exist.\n");
						return 1;
					}
			
				while(fgets(line, maxlength, fp) != NULL)
				{
					ret = strcmp(word, entered);
					if(ret == 0)
					{
						printf("entered %s\n", entered);
						printf("dict %s\n", word);
						fprintf(stdout, "\"%s\" is correct.\n", ret);
						return 0;
					}
					else
					{
						fprintf(stderr, "\"%s\" is incorrect.\n", entered);
						return 1;
					}
				}
			}
	}	

}	
	

