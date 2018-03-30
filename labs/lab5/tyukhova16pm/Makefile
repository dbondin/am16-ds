all: HASH
HASH: main.o 
	g++ main.o -o HASH

main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -rf *.o HASH
