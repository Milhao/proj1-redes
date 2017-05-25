/******************************************
*Rafael Silva de Milhã		NºUSP: 8139701*
******************************************/

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

int main()
{
    //threads de cada sensor
    thread t1(S1);
    thread t2(S2);
    thread t3(S3);
    thread t4(S4);
    thread t5(S5);
    thread t6(S6);

    //executa as threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
}