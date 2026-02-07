#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <queue>
#include <functional>
#include <vector>
#include <condition_variable>
#include<atomic>
#include<chrono>
#include<future>
using namespace std;

// In this class , I will create a thread pool and show how it can be used
// This is the final implementation after a lot of thinking. 
class ThreadPool
{
	int _capacity;
	queue<function<void()>> taskQueue;
	vector<thread> threads;
	mutex queueMutex;
	condition_variable taskReceived;
	atomic<bool> end;
	
	void worker()
	{
		while (!end)
		{
			function<void()> task;
			{
				unique_lock<mutex> lock(queueMutex);
				taskReceived.wait(lock, [this] { return !this->taskQueue.empty() || end; });
				if (end && this->taskQueue.empty()) return;
				task = move(this->taskQueue.front());
				this->taskQueue.pop();
			}
			if (task)
				task();
		}
	}

public :
	ThreadPool(int size)
	{
		this->_capacity = size;
		this->end = false;
		for (int i = 0; i < size; i++)
		{
			this->threads.push_back(thread(&ThreadPool::worker,this));
		}
	}

	~ThreadPool()
	{
		{
			unique_lock<mutex> lock(queueMutex);
			this->end = true;
		}
		cout << "Destructor"<<endl;
		this->taskReceived.notify_all();
		for (int i = 0; i < this->_capacity; i++)
		{
			if (threads[i].joinable())
				threads[i].join();
		}
		cout << "All threads joined" << endl;
	}

	void submitTask(function<void()> task)
	{
		{
			unique_lock<mutex> lock(this->queueMutex);
			this->taskQueue.push(task);
			cout << "Task Submitted" << endl;
		}
		this->taskReceived.notify_one();
	}
};

int f_main()
{
	ThreadPool pool(5);	
	vector<function<void()>> tasks;

	for (int i = 0; i < 15; i++)
		tasks.push_back([]() { 
		this_thread::sleep_for(chrono::seconds(5));
		cout << "Hello World from thread: " << this_thread::get_id()<< endl; });
	
	for(int i = 0;i<15;i++)
		pool.submitTask(tasks[i]);
	this_thread::sleep_for(chrono::seconds(60));
	
	return 0;
}