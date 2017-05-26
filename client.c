#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    FILE *fp = fopen(argv[3], "r");

    if (fp == NULL){
        printf("I could not read this file");
        exit(0);
    }

    char buffer[256];
    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    // roda o while até o fim do arquivo, envia 1 log por segundo
    while(!feof(fp)){   
        bzero(buffer,256);
        fgets(buffer, 30, fp);      // armazena a informação do log no arquivo
        n = write(sockfd,buffer,strlen(buffer));    // envia a informação pro servidor

        if (n < 0) 
            error("ERROR writing to socket");
        sleep(1);
    }
    printf("Closing Client...");
    close(sockfd);
    fclose(fp);
    return 0;
}
