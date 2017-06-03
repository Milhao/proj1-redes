#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
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

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

void printMenu(){
	cout << "\t\tProjeto 1 - Redes de Computadores\n";
	cout << "Pressione:\n";
	cout << "\th -> para printar o menu novamente\n";
	cout << "\tc -> para conectar os sensores\n";
	cout << "\tp -> para printar a configuração das portas\n";
	cout << "\td -> para desconectar os sensores\n";
	cout << "\tl -> para limpar a tela\n";
	cout << "\tq -> para desconectar os sensores e sair do programa\n";
}

int main(int argc, char * argv[]) {
	Central c1;
	char cmd;

	printMenu();

	thread t1;
	while('q' != (cmd = getch())) {
		switch(cmd) {
			case 'h':
				printMenu();	
				break;
			case 'p':
				c1.printPortnos();
				break;
			case 'c':
				c1.connectSensors();
				break;
			case 'd':
				c1.disconnectSensors();
				printf("\033[H\033[J");
				break;
			case 'v': //Mostra os sensores virtuais, se possível
				printMenu();
				printf("\033[H\033[J");
				break;
			case 'l':
				
				break;
			default:
				cout << "Comando inválido. Pressione \"h\" para ajuda.\n";
				break;
		}
	}

	cout << "Fechando...\n";
	c1.disconnectSensors();
	cout << "Pronto.\n";

	return 0;
}
