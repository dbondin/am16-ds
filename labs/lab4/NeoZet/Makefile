CC=gcc
FLAGS=-std=c99

all: lab4
lab4: lab4.o huff.o
	gcc lab4.o huff.o -o lab4

lab4.o: lab4.c
	gcc -c lab4.c

huff.o: huff.c
	gcc -c huff.c

clean:
	rm -rf *.o lab4

debug:
	gcc -g lab4.c huff.c -o dl 
