all: cats
cats: main.o
	g++ main.o -o cats
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -rf *.o cats
