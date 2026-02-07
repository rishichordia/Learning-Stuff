#include<iostream>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<queue>
#include<functional>
#include<atomic>
#include<chrono>

using namespace std;

struct Compare {
	bool operator()(const pair<int, function<void()>>& a, const pair<int, function<void()>>& b)
	{
		return a.first < b.first;
	}
};
class TaskScheduler {

	atomic<bool> end;
	vector<thread> workers;
	priority_queue<pair<int, function<void()>>, vector<pair<int, function<void()>>>, Compare> queue;
	int max_size;
	int num_workers;
	mutex mut;
	condition_variable cv;


	void worker()
	{
		while (true)
		{
			function<void()> func;
			int priority;
			{
				unique_lock<mutex> lock(mut);
				cv.wait(lock, [this]() {return !queue.empty() || (end && queue.empty()); });
				if (end && queue.empty())
					return;
				auto curr = queue.top();
				queue.pop();
				func = curr.second;
				priority = curr.first;
			}
			cout << "Thread " << this_thread::get_id() << " .Priority - " << priority << "\n";
			func();
		}
	}

public:
	TaskScheduler(int size, int num_threads)
	{
		max_size = size;
		num_workers = num_threads;
		end = false;
	}

	void start()
	{
		for (int i = 0; i < num_workers; i++)
		{
			workers.push_back(thread(&TaskScheduler::worker, this));
		}
	}

	void exit()
	{
		end = true;
		cv.notify_all();
		for (int i = 0; i < num_workers; i++)
		{
			if (workers[i].joinable())
				workers[i].join();
		}
	}

	void schedule(int priority, function<void()> func)
	{
		unique_lock<mutex> lock(mut);
		cv.wait(lock, [this]() {return queue.size() < max_size || end; });
		if (end)
			return;
		queue.push(make_pair(priority, func));
		cv.notify_one();
	}
};

void exec(int i)
{
	cout << "This is task" << i << endl;
	this_thread::sleep_for(chrono::seconds(2));
}

int TaskSchedulermain()
{
	vector<function<void()>> tasks;
	for (int i = 0; i < 10; i++)
	{
		tasks.push_back(bind(exec, i));
	}
	vector<thread> threads;
	TaskScheduler scheduler(10, 2);
	scheduler.start();
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(thread(&TaskScheduler::schedule, &scheduler, i, tasks[i]));
	}
	for (int i = 0; i < 10; i++)
		threads[i].join();
	auto now = chrono::system_clock::now();
	this_thread::sleep_for(chrono::seconds(12));
	auto duration = now.time_since_epoch();
	auto micros = chrono::duration_cast<chrono::microseconds>(duration).count();
	cout << "Time stamp: " << micros << endl;
	scheduler.exit();
	return 0;
}