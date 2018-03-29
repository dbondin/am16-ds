all: HUFF

HUFF: main.o huf.o
	g++ main.o huf.o -o HUFF
main.o: main.cpp
	g++ -c main.cpp
huf.o: huf.cpp
	g++ -c huf.cpp
clean:
	rm -rf *.o HUFF

