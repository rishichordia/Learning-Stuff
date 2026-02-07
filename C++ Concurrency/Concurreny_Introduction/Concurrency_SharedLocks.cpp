#include<iostream>
#include<vector>
#include<condition_variable>
#include<thread>
#include<mutex>
#include<shared_mutex>
#include<chrono>

using namespace std;

int scnt = 0;
shared_mutex mxx;

void read(int i)
{
	shared_lock<shared_mutex> lock(mxx);
	this_thread::sleep_for(chrono::seconds((i + 1)%5));
	cout << "Reader Thread " << i<< " . Counter: " << scnt<< endl;
}

void write(int val)
{
	unique_lock<shared_mutex> lock(mxx);
	scnt = val;
	cout << "Writer thread" <<endl;
}

int file4_main()
{
	unsigned int n = thread::hardware_concurrency();
	cout << n << endl;
	vector<thread> readers;
	for (int i = 0; i < 5; i++)
	{
		readers.push_back(thread(read,i));
	}
	thread writer1(write,3);
	writer1.join();
	for (int i = 5; i < 10; i++)
	{
		readers.push_back(thread(read, i));
	}
	for (auto& thread : readers)
		thread.join();
	return 0;
}