all: mylab

mylab: mylab.o 
	gcc mylab.o -o mylab

mylab.o: mylab.c
	gcc -c mylab.c

clean:
	rm -rf *.o mylab
