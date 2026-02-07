#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
mutex m1, m2, m3, m4;

void d5()
{
	if (m3.try_lock())
	{
		cout << "M3 acquired" << endl;
	}
	else
	{
		cout << "F" << endl;
	}
}

void d3()
{
	lock(m3, m4);
	lock_guard<mutex> l1(m3, adopt_lock);
	lock_guard<mutex> l2(m4, adopt_lock);
	cout << "Inside thread " << this_thread::get_id() << endl;
}

void d4()
{
	lock(m3, m4);
	lock_guard<mutex> l1(m3, adopt_lock);
	lock_guard<mutex> l2(m4, adopt_lock);
	cout << "Inside thread " << this_thread::get_id() << endl;
}

void d1()
{
	mutex* f = &m1;
	mutex* s = &m2;
	if (f > s) swap(f, s);
	lock_guard<mutex> l1(*f);
	lock_guard<mutex> l2(*s);
	cout << "Inside thread " << this_thread::get_id() << endl;
}

void d2()
{
	mutex* f = &m1;
	mutex* s = &m2;
	if (f > s) swap(f, s);
	lock_guard<mutex> l1(*f);
	lock_guard<mutex> l2(*s);
	cout << "Inside thread " << this_thread::get_id() << endl;
}

int deadlock_main()
{
	thread t1(d1);
	thread t2(d2);
	thread t3(d3);
	thread t5(d5);
	thread t4(d4);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	return 0;
}