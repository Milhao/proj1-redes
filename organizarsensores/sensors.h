#ifndef SENSORS_H
#define SENSORS_H

#include <vector>
#include <thread>

class Sensors {	
	int run;
	std::vector<int> portno;
	std::vector<std::thread> s;
public:
	Sensors();
	void setPortno(int port, int ind);
	int getPortno(int ind);
	void setRun(int run);
	int getRun();
	void gps();
	void variometer();
	void pitot();
	void gyroscope();
	void fuel();
	void laser();
	void barometer();
	void cardiac();
	void sensor_socket(char * name, int portno, double (*sensor)());
};

#endif

/*********************************************
*S1 - GPS                                    *
*S2 - Variômetro                             *
*S3 - Tubo de Pitot                          *
*S4 - Giroscópio                             *
*S5 - Medidor de Combustível                 *
*S6 - Laser(trem de pouso)                   *
*M1 - Barômetro                              *
*M2 - Sensor de ritmo cardíaco               *
*                                            *
*SV1 - Radar(S1, S3, S4)                     *
*SV2 - Pouso seguro(S2, S3, S6)              *
*SV3 - Estimativa de combustivel(S2, S3, S5) *
*SV4 - Pressão interna(S2, M1, M2)           *
*********************************************/