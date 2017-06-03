#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <netdb.h>
#include <sstream>
#include "conn.h"
#include "central.h"

using namespace std;

Central :: Central(){
	conn = 0;
	portno.assign(PORTS);
	s.resize(portno.size() + 1);
	sensorValue.resize(portno.size());
}

void Central :: setPortno(int port, int ind){
	portno[ind] = port;
}

int Central :: getPortno(int ind){
	return portno[ind];
}

void Central :: error(const char *msg){
	perror(msg);
	exit(1);
}

void Central :: showValues(){
	int first = 1;
	while(conn){
		if(first){
			sleep(1);
			cout << "\033[2J\033[0;0f";
			first = 0;
		} else {
			sleep(1);
			cout << "\033[2A\033[1J\033[0;0f";	
		}
		for(int i = 0; i < 8; i++)
			cout << names[i] << ": " << sensorValue[i] << "\n";
		cout << "\033[u";
	}
}

void Central :: sensor(int i) {
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[BUFFER_SIZE];
	char * name;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) 
		error("ERRO ao abrir socket.\n");
	server = gethostbyname(HOSTNAME);
	if(server == NULL) {
		fprintf(stderr,"ERRO, host inexistente.\n");
		return;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno[i]);

	while(connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		if(!conn) {
			cout << "s" << i << " fechado.\n";
			return;
		}
	}

	bzero(buffer, BUFFER_SIZE);
	*((int *) buffer) = IDENTIFY;
	n = write(sockfd, buffer, sizeof(enum MESSAGE));

	bzero(buffer, BUFFER_SIZE);
	n = read(sockfd, buffer, BUFFER_SIZE);
	name = (char *) malloc((strlen(buffer)+1)*sizeof(char));
	strcpy(name, buffer);
	cout << "Sensor "<< name <<" conectado.\n";
	names.push_back(name);

	int out = 0;
	do {
		if(!conn) {
			bzero(buffer, BUFFER_SIZE);
			*((int *) buffer) = CLOSE;
			n = write(sockfd, buffer, sizeof(enum MESSAGE));
			bzero(buffer, BUFFER_SIZE);
			n = read(sockfd, buffer, BUFFER_SIZE);
			if(*((int *) buffer) == CONFIRM)
				continue;
			else if((*((int *) buffer) != CONFIRM) || out > 10){
				cout << out;
				break;
			}
			out++;
		}
		bzero(buffer, BUFFER_SIZE);
		*((int *) buffer) = NEXT;
		n = write(sockfd, buffer, sizeof(enum MESSAGE));

		bzero(buffer, BUFFER_SIZE);
		n = read(sockfd, buffer, BUFFER_SIZE);
		sensorValue[i] = *((double *) buffer);
		//precisa concertar http://www.termsys.demon.co.uk/vtansi.htm#cursor
		//cout << "\033[" << i << ";0H\033[1K" << name << *((double *) buffer) << "\n";
		//cout << name << sensorValue[i] << "\n";
	} while(n > 0);

	close(sockfd);
	cout << "Sensor "<< name << " desconectado.\n";
	free(name);
}

void Central :: connectSensors() {
	if(!conn) {
		conn = 1;
		for(int i=0; i<(int) s.size() - 1; i++)
			s[i] = thread(&Central::sensor, this, i);
		s[s.size() - 1] = thread(&Central::showValues, this);
	}
}

void Central :: disconnectSensors() {
	if(conn) {
		conn = 0;
		for(int i = (int) s.size() - 1; i >= 0; i--)
			s[i].join();
		vector<char *> names;
	}
}

void Central :: printPortnos() {
	for(int i=0; i<(int) portno.size(); i++)
		cout << "s" << i << " = " << portno[i] << "\n";
}
