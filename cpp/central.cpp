#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "central.h"

using namespace std;

Central :: Central(){
	int port = 51711;
	for(int i = 0; i < 8; i++, port++)
		portno[i] = port;
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

void strtolower(char * s) {
	for(int i=0; s[i]; i++)
		s[i] = tolower(s[i]);
}

int getWord(char * s, int n) {
	int i;
	for(i=0; i < n && EOF != (s[i] = fgetc(stdin)) && '\n' != s[i] && ' ' != s[i]; i++);
	if(i == n) {
		i--;
		while(EOF != (s[i] = fgetc(stdin)) && '\n' != s[i] && ' ' != s[i]);
	}
	s[i] = 0;
	return i;
}

enum COMMAND Central :: getCommand() {
	char s[11];

	getWord(s, 11);
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