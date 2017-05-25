compile: sensores.cpp
	g++ sensores.cpp -pthread -std=c++11 -o sensores

run:
	./sensores

all: sensores.cpp client.c
	gcc client.c -o client
	g++ sensores.cpp -pthread -std=c++11 -o sensores
	./sensores