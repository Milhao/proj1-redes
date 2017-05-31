#ifndef __CONN_H__
#define __CONN_H__

#define HOSTNAME "localhost"
#define PORTS {51711, 51712, 51713, 51714, 51715, 51716, 51717, 51718}
#define BUFFER_SIZE 16

enum MESSAGE {
	CONFIRM = 1,
	IDENTIFY,
	NEXT,
	RESEND,
	CLOSE
};

#endif
