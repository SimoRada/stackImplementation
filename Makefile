main.exe: main.o 
	g++ main.o -o main.exe

main.o: main.cpp stack.hpp
	g++ -c main.cpp -o main.o

	