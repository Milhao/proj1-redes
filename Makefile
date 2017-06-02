compile: central.o main.o ./cpp/sensors.cpp ./cpp/sensors.h ./cpp/main.cpp
	g++ central.o main.o -o central -pthread -std=c++0x -Wall
	g++ ./cpp/sensors.cpp ./cpp/main.cpp -o sensors -pthread -std=c++11

central.o: ./cpp/central.cpp ./cpp/central.h ./cpp/conn.h
	g++ ./cpp/central.cpp -c -pthread -std=c++0x -Wall

main.o: main.cpp
	g++ main.cpp -c -pthread -std=c++0x -Wall
