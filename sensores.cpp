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

#include <string>
#include <iostream>
#include <thread>

using namespace std;

//Sensores (por enquanto escreve valores aleatorios na saida padrao)
void S1()
{
    while(true)
        cout << "S1: " << rand() % 100 << "\n";
}
void S2()
{
    while(true)
        cout << "S2: " << rand() % 100 << "\n";
}
void S3()
{
    while(true)
        cout << "S3: " << rand() % 100 << "\n";
}
void S4()
{
    while(true)
        cout << "S4: " << rand() % 100 << "\n";
}
void S5()
{
    while(true)
        cout << "S5: " << rand() % 100 << "\n";
}
void S6()
{
    while(true)
        cout << "S6: " << rand() % 100 << "\n";
}
void M1()
{
    while(true)
        cout << "M1: " << rand() % 100 << "\n";
}
void M2()
{
    while(true)
        cout << "M2: " << rand() % 100 << "\n";
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

    //executa as threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
}