CC=gcc
CF=-c -g
LF=

all: brainfuck.o
	$(CC) $(LF) brainfuck.o -o brainfuck
brainfuck.o: brainfuck.c
	$(CC) $(CF) brainfuck.c -o brainfuck.o
clean:
	rm *.o brainfuck
