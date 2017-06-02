#ifndef __CENTRAL_H__
#define __CENTRAL_H__

#include <vector>
#include <thread>

using namespace std;

class Central {
private:
	int conn;
	vector<int> portno;
	vector<thread> s;
	void error(const char *msg);
	void sensor(int i);
public:
	Central();
	void setPortno(int port, int ind);
	int getPortno(int ind);
	void connectSensors();
	void disconnectSensors();
	void printPortnos();
};

#endif
