compile: central.o main.o
	g++ central.o main.o -o central -pthread -std=c++0x -Wall

central.o: ./cpp/central.cpp ./cpp/central.h ./cpp/conn.h
	g++ ./cpp/central.cpp -c -pthread -std=c++0x -Wall

main.o: main.cpp
	g++ main.cpp -c -pthread -std=c++0x -Wall
