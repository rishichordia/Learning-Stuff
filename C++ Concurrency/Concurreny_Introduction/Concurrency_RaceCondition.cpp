#include <iostream>
#include<vector>
#include<thread>
#include<mutex>
using namespace std;

int counter = 0;
mutex mtx1;

void print_no_racecondition_manual()
{
	mtx1.lock();
	counter++;
	cout << "Counter: " << counter << endl;
	mtx1.unlock();
}

void print_no_racecondition()
{
	lock_guard<mutex> lock(mtx1);
	counter++;
	cout << "Counter: " << counter << endl;
}
void print_raceCondition()
{
	counter++;
	cout << "Counter :" << counter << endl;
}

int file_main()
{
	cout << "Hello World!\n";

	vector<thread> threads;
	vector<thread> threads1;
	for (int i = 0; i < 5; i++)
	{
		threads.push_back(thread(print_raceCondition));
	}
	for (int i = 0; i < 5; i++)
	{
		threads[i].join();
	}
	counter = 0;
	//threads.clear();
	cout << "Threads finished" << endl;
	for (int i = 0; i < 5; i++)
	{
		threads1.push_back(thread(print_no_racecondition));
	}
	for (int i = 0; i < 5; i++)
	{
		threads1[i].join();
	}
	//counter = 0;
	for (int i = 0; i < 5; i++)
	{
		threads[i] = thread(print_no_racecondition_manual);
	}
	for (int i = 0; i < 5; i++)
	{
		threads[i].join();
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
