all: l3
l3: stek.h sdl3.o calc.o
	g++ stek.h sdl3.o calc.o -o sdl3
sdl3.o: sdl3.cpp
	g++ -c sdl3.cpp 
calc.o: calc.cpp
	g++ -c calc.cpp  

