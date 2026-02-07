#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<chrono>

using namespace std;

class Barrier {

	mutex mx;
	condition_variable cv;
	int total;
	int completed_threads;
	bool reset_flag;
public: 
	Barrier(int total_threads)
	{
		total = total_threads;
		completed_threads = 0;
		reset_flag = false;
	}
	void start()
	{
		unique_lock<mutex> lock(mx);
		if (reset_flag)
		{
			cv.notify_all();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
		reset_flag = false;
	}
	void wait()
	{
		this_thread::sleep_for(chrono::seconds(2));
		unique_lock<mutex> lock(mx);
		completed_threads++;
		if (completed_threads == total)
			cv.notify_all();
		else
		cv.wait(lock, [this]() {return completed_threads == total; });
	}
};

void work(int id, Barrier* barrier)
{
	cout << "Thread " << id << " before barrier\n";
	barrier->wait();
	cout << "Thread " << id << " after barrier\n";
}

int Barrier_main()
{
	Barrier* ob = new Barrier(5);
	vector<thread> threads;
	for (int i = 0; i < 5; i++)
	{
		threads.push_back(thread(work, i, ob));
	}
	for (int i = 0; i < 5; i++)
	{
		threads[i].join();
	}
	return 0;
}