#include <iostream>
#include "sensors.h"

using namespace std;

int main() {
	//Inicia as threads
	Sensors s;
	int in = 1;
	while(in != 0) {
		cout << "Digite 0 para fechar tudo e sair.\n";
		cin >> in;
	}
	s.closeSensors();
	//shutdown_socket();
	return 0;
}