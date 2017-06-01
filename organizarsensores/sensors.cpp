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

double aleatorio() {
    return rand() / rand();
}

void Sensors :: gps() {
    s[1] = thread(&Sensors :: sensor_socket, this, "GPS", portno[1], aleatorio);
}

void Sensors :: variometer() {
    s[2] = thread(&Sensors :: sensor_socket, this, "Variometro", portno[2], aleatorio);
}

void Sensors :: pitot() {
    s[3] = thread(&Sensors :: sensor_socket, this, "Pitot", portno[3], aleatorio);
}

void Sensors :: gyroscope() {
	s[4] = thread(&Sensors :: sensor_socket, this, "Giroscopio", portno[4], aleatorio);
}

void Sensors :: fuel() {
    s[5] = thread(&Sensors :: sensor_socket, this, "Combustivel", portno[5], aleatorio);
}

void Sensors :: laser() {
    s[6] = thread(&Sensors :: sensor_socket, this, "Laser", portno[6], aleatorio);
}

void Sensors :: barometer() {
    s[7] = thread(&Sensors :: sensor_socket, this, "Barometro", portno[7], aleatorio);
}

void Sensors :: cardiac() {
    s[8] = thread(&Sensors :: sensor_socket, this, "Cardiaco", portno[8], aleatorio);
}

Sensors :: Sensors(){
	run = 1;
	portno.assign(PORTS);
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

void Sensors :: sensor_socket(char * name, int portno, double (*sensor)()) {
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
	serv_addr.sin_port = htons(portno);

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
					n = write(newsockfd, name, strlen(name));
					break;
				case NEXT:
					*buffer = sensor();
				case RESEND:
					n = write(newsockfd, buffer, sizeof(double));
					break;
				case CLOSE:
					*buffer = CONFIRM;
					n = write(newsockfd, buffer, sizeof(enum MESSAGE));
				default:
					break;
			}
		} while(msg != CLOSE);
		close(newsockfd);
	}

	close(sockfd);
	return;
}