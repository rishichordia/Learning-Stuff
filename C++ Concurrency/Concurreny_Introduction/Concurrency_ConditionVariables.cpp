#include<iostream>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<chrono>
#include<sstream>
#include<vector>
#include<functional>

using namespace std;

string message;
mutex mtx;
mutex mtx3;
condition_variable cv;
condition_variable cv2;
condition_variable cv3;
bool fff;

void f4()
{
	unique_lock<mutex> lock(mtx);
	cv2.wait(lock);
	cout << "Threadf4: " << this_thread::get_id() << " . Message from the other thread is: " << message << endl;
}
void f3()
{
	unique_lock<mutex> lock(mtx);
	cv.wait(lock);
	//cv2.wait(lock);
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Threadf3: " << this_thread::get_id() << " . Message from the other thread is: " << message << endl;
}
void f1()
{
	unique_lock<mutex> lock(mtx);
	cv2.wait(lock);
	//this_thread::sleep_for(chrono::seconds(2));
	cout << "Threadf1: " << this_thread::get_id() << " . Message from the other thread is: " << message << endl;
}

void f2()
{
	cout << "Inside thread: " << this_thread::get_id() << endl;
	{
		unique_lock<mutex> lock(mtx, defer_lock);
		stringstream ss;
		ss << this_thread::get_id();
		lock.lock();
		this_thread::sleep_for(chrono::seconds(5));
		message = "This is thread " + ss.str();
		cv.notify_one();
		//cv.notify_one();
		cv2.notify_all();
	}
}

void run_same_fun_in_multiple_threads()
{
	unique_lock<mutex> lock(mtx3);
	cout << "Inside thread - " << this_thread::get_id() << endl;
	cv3.wait(lock,[]() { return fff; });
	this_thread::sleep_for(chrono::seconds(10));
	cout << "Done Thread - " << this_thread::get_id() << endl;
}

function<void()> func = []() { 
	unique_lock<mutex> lock(mtx3);
	cout << "Inside thread - " << this_thread::get_id() << endl;
	cv3.wait(lock,[]() { return fff; });
	this_thread::sleep_for(chrono::seconds(3));
	cout << "Done Thread - " << this_thread::get_id() << endl;};

int cv_main()
{
	cout << "Hello World!" << endl;
	thread t1(f1);
	thread t3(f3);
	thread t2(f2);
	thread t4(f4);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	
	vector<thread> threads;
	for (int i = 0; i < 10; i++)
	{
		function<void()> new_func = func;
		threads.push_back(thread(new_func));
	}
	fff = true;
	//cv3.notify_one();
	//cv3.notify_one();
	//cv3.notify_one();
	//cv3.notify_one();
	//cv3.notify_one();
	//cv3.notify_one();
	cv3.notify_all();

	for (int i = 0; i < 10; i++)
	{
		threads[i].join();
	}
	return 0;
}