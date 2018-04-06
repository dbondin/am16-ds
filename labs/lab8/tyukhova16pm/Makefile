all: lb8
lb8: Sokoban.o
	g++ Sokoban.o -o Sokoban
Sokoban.o: Sokoban.cpp
	g++ -c Sokoban.cpp
clean:
	rm -rf *.o lb8
