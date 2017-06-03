#ifndef __CENTRAL_H__
#define __CENTRAL_H__

#include <string>
#include <vector>
#include <thread>

using namespace std;

class Central {
private:
	int conn;
	vector<int> portno;
	vector<thread> s;
	vector<double> sensorValue;
	vector<string> names;
	void error(const char *msg);
	void virtualSensor1();
	void virtualSensor2();
	void virtualSensor3();
	void virtualSensor4();
	void sensor(int i);
public:
	Central();
	void setPortno(int port, int ind);
	int getPortno(int ind);
	void connectSensors();
	void disconnectSensors();
	void printPortnos();
	void showValues();
};

#endif
