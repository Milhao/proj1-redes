compile: sensores.cpp
	g++ sensores.cpp -pthread -std=c++11 -o sensores

run:
	./client localhost 51717 s1.txt&
	./client localhost 51717 s2.txt&
	./client localhost 51717 s3.txt&

all: sensores.cpp client.c
	gcc client.c -o client
	g++ sensores.cpp -pthread -std=c++11 -o sensores
	./sensores