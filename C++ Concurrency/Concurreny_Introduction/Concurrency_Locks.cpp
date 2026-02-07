#include <iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

int cnt = 0;
mutex mtx2;

void print_uniqueLock_defer(int i)
{
	unique_lock<mutex> lock2(mtx2, defer_lock);
	this_thread::sleep_for(chrono::seconds(10 /(i+1)));
	lock2.lock();
	cnt++;
	cout << "Thread number "<<i<<". Thread id "<<this_thread::get_id()<<" Counter: " << cnt << endl;
	lock2.unlock();
}
void print_uniquelock()
{
	unique_lock<mutex> lock(mtx2);
	cnt++;
	cout <<"Thread id "<<this_thread::get_id()<<". Counter: " << cnt << endl;
}

void print_raceCondition2()
{
	cnt++;
	cout << "Thread id "<<this_thread::get_id()<<". Counter :" << cnt << endl;
}

int tmp_main()
{
	cout << "Hello World!\n";

	vector<thread> threads;
	vector<thread> threads1;
	for (int i = 0; i < 5; i++)
	{
		threads.push_back(thread(print_raceCondition2));
	}
	for (int i = 0; i < 5; i++)
	{
		threads[i].join();
	}
	cnt = 0;
	//threads.clear();
	cout << "Threads finished" << endl;
	for (int i = 0; i < 5; i++)
	{
		threads1.push_back(thread(print_uniquelock));
	}
	for (int i = 0; i < 5; i++)
	{
		threads1[i].join();
	}
	cnt = 0;
	for (int i = 0; i < 5; i++)
	{
		threads[i] = thread(print_uniqueLock_defer, i);
	}
	for (int i = 0; i < 5; i++)
	{
		threads[i].join();
	}
	return 0;
}

