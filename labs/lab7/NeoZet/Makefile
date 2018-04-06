CC = gcc

all: lab7
lab7: lab7.o timsort.o
	$(CC) lab7.o timsort.o -o lab7

lab7.o: lab7.c
	$(CC) -c lab7.c

timsort.o: timsort.c
	$(CC) -c timsort.c

clean:
	rm *.o lab7 dl

debug:
	$(CC) -g lab7.c timsort.c -o dl
