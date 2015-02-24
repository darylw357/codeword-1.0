FLAGS = -std=c99 -Wall

all: codeword.exe

codeword.exe: codewordmain.c
	gcc $(FLAGS) codewordmain.c -o codeword.exe