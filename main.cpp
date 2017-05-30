#include <stdio.h>
#include <iostream>
#include "./cpp/central.h"

using namespace std;

int main() {
	int a;
	Central c1;
	enum COMMAND cmd;

	while(QUIT != (cmd = c1.getCommand())) {
		switch(cmd) {
			case HELP:
				cout << "HELP\t\tMostra este manual.\n\nCONFIG\t\tConfiguração de porta de conexão.\n\tALL\t\tMostra a configuração de todas as portas.\n\nCONNECT\t\tConecta com sensor.\n\tALL\t\tConecta com todos os sensores.\n\nDISCONNECT\tDesconecta de sensor.\n\tALL\t\tDesconecta de todos os senores.\n\nVIRTUAL\t\tAtiva sensor virtual (os sensores físicos correspondentes devem estar conectados).\n\tALL\t\tAtiva todos os sensores virtuais.\n\nQUIT\t\tDesconectar tudo e sair.\n";
				   break;
			case CONFIG:
				cmd = c1.getCommand();
				switch(cmd) {
					case ALL: for(int i = 0; i < 10; i++)
							cout << "portno[" << i << "] = " << c1.getPortno(i) << "\n";
					default: break;
				 }
				 break;
			case CONNECT:
				cmd = c1.getCommand();
				switch(cmd) {
					case ALL: //std::thread s (sensor, portno[0]);
						  //Criar threads e conectar sensores
					default: break;
				}
				break;
			case DISCONNECT:
				cmd = c1.getCommand();
				switch(cmd) {
					case ALL: cout << "Desconectando...\n";
						  //Desconectar
					default: break;
				}
				break;
			case VIRTUAL: //Mostrar os sensores virtuais, se possivel
			default:
				cout << "Comando inválido. Digite \"help<ENTER>\" para ajuda.\n";
				break;
		}
	}

	cout << "Fechando...\n";
	//Desconectar
	//
	//
	//
	cout << "Pronto.\n";

	return 0;
}