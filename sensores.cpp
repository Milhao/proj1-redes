/******************************************
*Rafael Silva de Milhã		NºUSP: 8139701*
******************************************/

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

#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

//Sensores (por enquanto escreve valores aleatorios na saida padrao)
void S1() {
    //faz conexao com a central

    //envia dados
    while(true)
        //envia msg
        return;
}
void S2() {
    while(true)
        //envia msg
        return;
}
void S3() {
    while(true)
        //envia msg
        return;
}
void S4() {
    while(true)
        //envia msg
        return;
}
void S5() {
    while(true)
        //envia msg
        return;
}
void S6() {
    while(true)
        //envia msg
        return;
}
void M1() {
    while(true)
        //envia msg
        return;
}
void M2() {
    while(true)
        //envia msg
        return;
}
void Central() {
    int sockfd, newsockfd; //array subscripts into the file descriptor table
    int port_num = 51717; //numero da porta do servidor
    socklen_t clilen; //tamanho do endereço do cliente
    char buffer[256]; //buffer de leitura da conexao
    struct sockaddr_in serv_addr, cli_addr; //endereços de internet do servidor e do cliente
    int n; //retorno das escritas e leituras no socket

    //criando o socket, AF_INET = dominio como sendo internet, SOCK_STREAM = define o tipo de socket como stream,
    //0 = SO escolhe o protocolo mais apropriado
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        cout << "Erro ao criar o socket!";

    //zera o buffer
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; //ip da maquina
    serv_addr.sin_port = htons(port_num); //numero da porta convertido para network byte order
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        cout << "Erro ao associar o socket ao endereço!";

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    //bloqueia o processo até receber uma conexao com um cliente
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0)
        cout << "Erro ao aceitar o cliente";

    int s1, s2, s3, s4, s5, s6, m1, m2;
    while(true){
        printf("\033[2J");
        printf("\033[0;0f");
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0)
            cout << "Erro ao ler o socket";
        //mostra os valores dos sensores
        cout << "S1) " << buffer << "S2) " << s2 << "\nS3) " << s3 << "\nS4) " << s4 << "\nS5) " << s5 << "\nS6) " << s6 << "\nM1) " << m1 << "\nM2) " << m2 << "\n";
        sleep(1);
    }
    close(sockfd);
    close(newsockfd);
}

int main()
{
    //threads de cada sensor
    thread t1(S1);
    thread t2(S2);
    thread t3(S3);
    thread t4(S4);
    thread t5(S5);
    thread t6(S6);
    thread t7(M1);
    thread t8(M2);
    thread t9(Central);

    //executa as threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
}