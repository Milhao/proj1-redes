compile: central.cpp sensors.cpp
	g++ central.cpp -pthread -o central -std=c++0x -Wall
	g++ sensors.cpp -pthread -o sensors -std=c++0x -Wall