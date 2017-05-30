#ifndef CENTRAL_H
#define CENTRAL_H

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

class Central {	
	int portno[8];
public:
	Central();
	void setPortno(int port, int ind);
	int getPortno(int ind);
	void error(const char *msg);
	enum COMMAND getCommand();
};

#endif