#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <thread>

#define HOSTNAME ""

enum MESSAGE {
	CONFIRM = 1,
	IDENTIFY,
	NEXT,
	RESEND,
	CLOSE
};

enum COMMAND {
	NOT_A_COMMAND,
	HELP,
	CONFIG,
	CONNECT,
	DISCONNECT,
	VIRTUAL,
	ALL,
	QUIT
};

int portno[10] = {51717, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int getstr(char * s, int n, FILE * fp) {
	int i;
	for(i=0; i < n && EOF != (s[i] = fgetc(fp)) && '\n' != s[i] && ' ' != s[i]; i++);
	if(i == n) {
		i--;
		while(EOF != (s[i] = fgetc(fp)) && '\n' != s[i] && ' ' != s[i]);
	}
	s[i] = 0;
	return i;
}

void strtolower(char * s) {
	for(int i=0; s[i]; i++)
		s[i] = tolower(s[i]);
}

enum COMMAND getCommand(FILE * fp) {
	char s[11];

	getstr(s, 11, stdin);
	strtolower(s);

	if(!strcmp(s, "all"))
		return ALL;
	else if(!strcmp(s, "conect"))
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

void error(const char *msg) {
	perror(msg);
	exit(1);
}

/*void sensor(int portno_i) {
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname(HOSTNAME);
	if(server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
	(char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
	serv_addr.sin_port = htons(portno[portno_i]);
	if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
}*/

int main(int argc, char *argv[]) {
	int i;
	enum COMMAND cmd;

	while(QUIT != (cmd = getCommand(stdin))) {
		switch(cmd) {
			case HELP:
				printf("HELP\t\tMostra este manual.\n\nCONFIG\t\tConfiguração de porta de conexão.\n\tALL\t\tMostra a configuração de todas as portas.\n\nCONNECT\t\tConecta com sensor.\n\tALL\t\tConecta com todos os sensores.\n\nDISCONNECT\tDesconecta de sensor.\n\tALL\t\tDesconecta de todos os senores.\n\nVIRTUAL\t\tAtiva sensor virtual (os sensores físicos correspondentes devem estar conectados).\n\tALL\t\tAtiva todos os sensores virtuais.\n\nQUIT\t\tDesconectar tudo e sair.\n");
				   break;
			case CONFIG:
				cmd = getCommand(stdin);
				switch(cmd) {
					case ALL: for(i=0; i<10; i++)
							printf("portno[%d] = %d\n", i, portno[i]);
					default: break;
				 }
				 break;
			case CONNECT:
				cmd = getCommand(stdin);
				switch(cmd) {
					case ALL: //std::thread s (sensor, portno[0]);
						  //Criar threads e conectar sensores
					default: break;
				}
				break;
			case DISCONNECT:
				cmd = getCommand(stdin);
				switch(cmd) {
					case ALL: printf("Desconectando...\n");
						  //Desconectar
					default: break;
				}
				break;
			case VIRTUAL: //Mostrar os sensores virtuais, se possivel
			default:
				printf("Comando inválido. Digite \"help<ENTER>\" para ajuda.\n");
				break;
		}
	}

	printf("Fechando...\n");
	//Desconectar
	//
	//
	//
	printf("Pronto.\n");

	return 0;
}
