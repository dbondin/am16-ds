all: calc
 calc: calc.o
 	g++ calc.o -o calc
 
 calc.o: calc.cpp
 	g++ -c calc.cpp
 
 clean:
 	rm -rf *.o calc
