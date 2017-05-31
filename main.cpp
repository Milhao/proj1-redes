#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string.h>
#include "./cpp/central.h"

using namespace std;

enum COMMAND {
	NOT_A_COMMAND,
	ENTER,
	HELP,
	CONFIG,
	CONNECT,
	DISCONNECT,
	VIRTUAL,
	QUIT
};

void strtolower(char * s) {
	for(int i=0; s[i]; i++)
		s[i] = tolower(s[i]);
}

int readstr(char * s, int n) {
	int i;
	for(i=0; i < n && EOF != (s[i] = fgetc(stdin)) && '\n' != s[i]; i++);
	if(i == n) {
		i--;
		while(EOF != (s[i] = fgetc(stdin)) && '\n' != s[i]);
	}
	s[i] = 0;
	return i;
}

enum COMMAND readCommand() {
	char s[11];

	readstr(s, 11);
	strtolower(s);

	if(!strlen(s))
		return ENTER;
	else if(!strcmp(s, "connect"))
		return CONNECT;
	else if(!strcmp(s, "config"))
		return CONFIG;
	else if(!strcmp(s, "disconnect"))
		return DISCONNECT;
	else if(!strcmp(s, "help"))
		return HELP;
	else if(!strcmp(s, "quit"))
		return QUIT;
	else if(!strcmp(s, "virtual"))
		return VIRTUAL;
	return NOT_A_COMMAND;
}

int main(int argc, char * argv[]) {
	Central c1;
	enum COMMAND cmd;

	while(QUIT != (cmd = readCommand())) {
		switch(cmd) {
			case HELP:
				cout << "HELP\t\tMostra esta ajuda.\n\nCONFIG\t\tConfiguração das portas.\n\nCONNECT\t\tConecta com sensores.\n\nDISCONNECT\tDesconecta dos sensores.\n\nVIRTUAL\t\tAtiva sensor virtual (os sensores físicos correspondentes devem estar conectados).\n\nQUIT\t\tDesconecta e sai.\n";
				   break;
			case CONFIG:
				c1.printPortnos();
				break;
			case CONNECT:
				c1.connectSensors();
				break;
			case DISCONNECT:
				c1.disconnectSensors();
				break;
			case VIRTUAL: //Mostra os sensores virtuais, se possível
			case NOT_A_COMMAND:
				cout << "Comando inválido. Digite \"help<ENTER>\" para ajuda.\n";
				break;
		}
	}

	cout << "Fechando...\n";
	c1.disconnectSensors();
	cout << "Pronto.\n";

	return 0;
}
