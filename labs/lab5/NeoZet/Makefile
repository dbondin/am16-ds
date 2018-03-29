CC=gcc

all: lab5
lab5: lab5.o rb_tree.o hash_map.o list.o
	$(CC) lab5.o rb_tree.o hash_map.o list.o -o lab5

lab5.o: lab5.c
	$(CC) -c lab5.c

rb_tree.o: rb_tree.c
	$(CC) -c rb_tree.c

hash_map.o: hash_map.c
	$(CC) -c hash_map.c

list.o: list.c
	$(CC) -c list.c

clean:
	rm -rf *.o lab5 dl

debug:
	$(CC) -g lab5.c rb_tree.c hash_map.c list.c -o dl
