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
class ThreadPoolAdv
{
	int _capacity;
	int maxTasksSupported;
	queue<packaged_task<int()>> taskQueue;
	vector<thread> threads;
	mutex queueMutex;
	condition_variable taskReceived;
	condition_variable queueNotFull;
	condition_variable allTasksCompleted;

	atomic<bool> end;
	atomic<bool> waiting;
	atomic<int> totalSubmitted{ 0 };
	atomic<int> totalCompleted{ 0 };
	atomic<int> totalTasksInQueue{ 0 };

	void worker()
	{
		while (!end)
		{
			packaged_task<int()> task;
			{
				unique_lock<mutex> lock(queueMutex);
				taskReceived.wait(lock, [this] { return !this->taskQueue.empty() || end; });
				if (end && this->taskQueue.empty()) return;
				task = move(this->taskQueue.front());
				this->taskQueue.pop();
				totalTasksInQueue--;
			}
			queueNotFull.notify_one();
			if (task.valid())
			{
				task();
				totalCompleted++;
			}
			if (totalSubmitted == totalCompleted)
				allTasksCompleted.notify_one();
		}
	}

public:
	ThreadPoolAdv(int size, int maxTasksSupported)
	{
		this->_capacity = size;
		this->end = false;
		this->maxTasksSupported = maxTasksSupported;
		for (int i = 0; i < size; i++)
		{
			this->threads.push_back(thread(&ThreadPoolAdv::worker, this));
		}
	}

	~ThreadPoolAdv()
	{
		{
			unique_lock<mutex> lock(queueMutex);
			this->end = true;
		}
		cout << "Destructor" << endl;
		this->taskReceived.notify_all();
		for (int i = 0; i < this->_capacity; i++)
		{
			if (threads[i].joinable())
				threads[i].join();
		}
		cout << "All threads joined" << endl;
	}

	void submitTask(packaged_task<int()>&& task)
	{
		{
			unique_lock<mutex> lock(this->queueMutex);
			queueNotFull.wait(lock, [this] { return end || (!waiting && totalTasksInQueue < maxTasksSupported); });
			this->taskQueue.push(move(task));
			totalTasksInQueue++;
			totalSubmitted++;
			cout << "Task Submitted" << endl;
		}
		this->taskReceived.notify_one();
	}

	void wait()
	{
		unique_lock<mutex> lock(queueMutex);
		waiting = true;
		allTasksCompleted.wait(lock, [this] { return (totalTasksInQueue == 0 && totalSubmitted == totalCompleted); });
		cout << "All tasks completed" << endl;
		waiting = false;
	}
};

int complexmain()
{
	ThreadPoolAdv pool(5,15);
	vector<future<int>> results;
	int x = 5, y = 20;
	for (int i = 0; i < 10; i++)
	{
		packaged_task<int()> task([]() {
			this_thread::sleep_for(chrono::seconds(5));
			cout << "Hello World from thread: " << this_thread::get_id() << endl;
			return 5; }
			);
		results.push_back(task.get_future());
		pool.submitTask(move(task));
	}
	pool.wait();
	for (int i = 0; i < 5; i++)
	{
		packaged_task<int()> task([]() {
			this_thread::sleep_for(chrono::seconds(5));
			cout << "Hello World from thread: " << this_thread::get_id() << endl;
			return 5; }
			);
		results.push_back(task.get_future());
		pool.submitTask(move(task));
	}

	//for (int i = 0; i < 15; i++)
	//{
	//	if (results[i].valid())
	//		cout << results[i].get();
	//}
	this_thread::sleep_for(chrono::seconds(10));

	return 0;
}