#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

int run = 1;

enum MESSAGE {
	CONFIRM = 1,
	IDENTIFY,
	NEXT,
	RESEND,
	CLOSE
};

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

double gyroscope() {
    return rand() / rand();
}

void sensor_socket(char * name, int portno, double (*sensor)(), int n_trys) {
	int sockfd, newsockfd;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int i, n;
	enum MESSAGE msg;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERRO ao abrir socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERRO ao associar");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	while(run) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) {
			printf("ERRO ao aceitar");
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

void quit() {
	while(run) {
		printf("Digite 0 para fechar tudo e sair.\n");
		scanf("%d", &run);
	}
	//shutdown_socket();
	exit(0);
}

int main(int argc, char *argv[]) {
	//Inicia as threads
	char s[20] = "Giroscópio";
	std::thread s1 (sensor_socket, s, 51717, gyroscope, 5);
	std::thread q (quit);
	s1.join();
	q.join();
	return 0;
}
