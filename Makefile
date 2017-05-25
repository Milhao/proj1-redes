compile: sensores.cpp
	g++ sensores.cpp -pthread -std=c++11 -o sensores

run:
	./sensores

all: sensores.cpp
	g++ sensores.cpp -pthread -std=c++11 -o sensores
	./sensores