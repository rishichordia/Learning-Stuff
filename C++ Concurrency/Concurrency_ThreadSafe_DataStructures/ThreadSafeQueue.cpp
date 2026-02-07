#include<iostream>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<atomic>

using namespace std;

class ThreadSafeQueue
{
	queue<int> q;
	mutex mtx;
	condition_variable queueNotEmpty;
	atomic<int> size;

public:
	ThreadSafeQueue()
	{
		size = 0;
	}

	void push(const int& val)
	{
		{
			unique_lock<mutex> lock(mtx);
			q.push(val);
			cout << "Pushing: " << val << endl;
			size++;
		}
		queueNotEmpty.notify_one();
	}

	void pop(int& val)
	{
		unique_lock<mutex> lock(mtx);
		queueNotEmpty.wait(lock, [this] {return size > 0; });
		val = q.front();
		q.pop();
		size--;
	}

	bool try_pop(int& val)
	{
		unique_lock<mutex> lock(mtx);
		if (size == 0)
			return false;
		val = q.front();
		q.pop();
		size--;
		return true;
	}

	bool empty()
	{
		unique_lock<mutex> lock(mtx);
		return q.empty();
	}
};

int ffmain()
{
	ThreadSafeQueue* queue = new ThreadSafeQueue();
	vector<thread> threads;
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(thread([queue, i]() {
			//cout << "Thread:- " << i << "\n";
			queue->push(i); }));
	}
	for (int i = 0; i < 10; i++)
	{
		threads[i].join();
	}
	for (int i = 0; i < 10; i++)
	{
		threads[i] = thread([queue]() {
			int val;
			queue->pop(val);
			cout << val << endl;
			});

	}
	for (int i = 0; i < 10; i++)
		threads[i].join();
	return 0;
}