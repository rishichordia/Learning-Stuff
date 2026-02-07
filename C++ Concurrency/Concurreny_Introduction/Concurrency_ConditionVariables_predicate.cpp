#include<iostream>
#include<condition_variable>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

mutex mx;
condition_variable cV;
string message1;
bool flag;

void g1()
{
	unique_lock<mutex> lock(mx);
	cV.wait(lock,[] { return flag; });
	cout << "Threadf1 -" << this_thread::get_id() << " . The message1 from the other thread is - " << message1 << endl;
}

void g2()
{
	cout << "Inside thread " << this_thread::get_id() << endl;
	unique_lock<mutex> lock(mx);
	this_thread::sleep_for(chrono::seconds(2));
	message1 = "hello";
	flag = true;
	cV.notify_one();
}

int fffdf_main()
{
	thread t1(g1);
	thread t2(g2);
	t1.join();
	t2.join();
	return 0;
}