all: lab3

lab3: main.o process.o queue_work.o symb_oper.o
	g++ main.o process.o queue_work.o symb_oper.o -o lab3
 
main.o: main.cpp
	g++ -c main.cpp 

process.o: process.cpp
	g++ -c process.cpp 

queue_work.o: queue_work.cpp
	g++ -c queue_work.cpp 

symb_oper.o: symb_oper.cpp
	g++ -c symb_oper.cpp 
 
clean:
	rm -rf *.o lab3
