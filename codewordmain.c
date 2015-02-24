/* A spell checking program*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
char T[] = 'Test';

	if(argc-1 == 3)
		{
			fprintf(stderr, "Usage:\n");
			fprintf(stderr, "codeword.exe [-h/--help]				 : Print this message.\n");
			fprintf(stderr, "codeword.exe --spellcheck DICTFILE WORDS : Check spelling of words.\n");
			fprintf(stderr, "codeword.exe --anagram DICTFILE WORDS	 : Find anagrams of a word.\n");
		}
	else if(*argv == *T)
		fprintf(stderr, "Test\n");
}
