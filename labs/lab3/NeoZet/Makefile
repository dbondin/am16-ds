all: lab3
lab3: lab3.o stack.o queue.o calculator.o
	gcc lab3.o stack.o queue.o calculator.o -o lab3 -lm

lab3.o: lab3.c
	gcc -c lab3.c

stack.o: stack.c
	gcc -c stack.c

queue.o: queue.c
	gcc -c queue.c

calculator.o: calculator.c
	gcc -c calculator.c

clean:
	rm -rf *.o lab3

debug:
	gcc -g lab3.c stack.c queue.c calculator.c -o dl -lm
