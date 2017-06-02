#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "conn.h"
#include "sensors.h"

using namespace std;

double Sensors :: aleatorio() {
    return ((double)rand()) / rand();
}

void Sensors :: gps() {
    s[0] = thread(&Sensors :: sensor_socket, this, 0);
}

void Sensors :: variometer() {
    s[1] = thread(&Sensors :: sensor_socket, this, 1);
}

void Sensors :: pitot() {
    s[2] = thread(&Sensors :: sensor_socket, this, 2);
}

void Sensors :: gyroscope() {
	s[3] = thread(&Sensors :: sensor_socket, this, 3);
}

void Sensors :: fuel() {
    s[4] = thread(&Sensors :: sensor_socket, this, 4);
}

void Sensors :: laser() {
    s[5] = thread(&Sensors :: sensor_socket, this, 5);
}

void Sensors :: barometer() {
    s[6] = thread(&Sensors :: sensor_socket, this, 6);
}

void Sensors :: cardiac() {
    s[7] = thread(&Sensors :: sensor_socket, this, 7);
}

Sensors :: Sensors(){
	run = 1;
	portno.assign(PORTS);
	names.assign(NAMES);
	s.resize(portno.size());
	gps();
	variometer();
	pitot();
	gyroscope();
	fuel();
	laser();
	barometer();
	cardiac();
}

void Sensors :: setPortno(int port, int ind){
	portno[ind] = port;
}

int Sensors :: getPortno(int ind){
	return portno[ind];
}

void Sensors :: setRun(int run){
	this->run = run;
}

int Sensors :: getRun(){
	return run;
}

void Sensors :: showNames(){
	for(int i = 0; i < 8; i++)
		cout << names[i];
}

void Sensors :: sensor_socket(int ind) {
	int sockfd, newsockfd;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int i, n;
	enum MESSAGE msg;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("ERRO ao abrir socket");
		exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno[ind]);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERRO ao associar");
		exit(1);
	}
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	while(run) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) {
			cout << "ERRO ao aceitar";
			continue;
		}

		do {
			//Erros de leitura ou escrita não estão sendo tratados
			bzero(buffer, 256);
			n = read(newsockfd, buffer, 255);
			msg = *((enum MESSAGE *) buffer);
			switch(msg) {
				case IDENTIFY:
					n = write(newsockfd, names[ind], strlen(names[ind]));
					break;
				case NEXT:
					*((double *)buffer) = aleatorio();
				case RESEND:
					n = write(newsockfd, buffer, sizeof(double));
					break;
				case CLOSE:
					*buffer = CONFIRM;
					n = write(newsockfd, buffer, sizeof(enum MESSAGE));
				default:
					break;
			}
		} while(run && msg != CLOSE);
		close(newsockfd);
	}

	close(sockfd);
	return;
}