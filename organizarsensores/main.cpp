#include <iostream>
#include "sensors.h"

using namespace std;

int main() {
	//Inicia as threads
	Sensors s;
	int in;
	while(in = s.getRun()) {
		cout << "Digite 0 para fechar tudo e sair.\n";
		cin >> in;
		s.setRun(in);
	}
	//shutdown_socket();
	return 0;
}