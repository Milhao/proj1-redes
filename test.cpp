/******************************************
*Rafael Silva de Milhã		NºUSP: 8139701*
******************************************/

#include <string>
#include <iostream>
#include <thread>

using namespace std;

// The function we want to execute on the new thread.
void task1(string msg)
{
	for(int i = 0; i < 5; i++)
    cout << i << msg << "\n";
}
void task2(string msg)
{
	for(int i = 0; i < 5; i++)
    cout << i << msg << "\n";
}

int main()
{
    // Constructs the new thread and runs it. Does not block execution.
    thread t1(task1, "Hello");
    thread t2(task2, "Bye");

    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    t1.join();
    t2.join();
}