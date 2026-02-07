#include<iostream>
#include<mutex>
#include<condition_variable>
#include<stack>
#include<atomic>
#include<thread>
#include<vector>

using namespace std;

class ThreadSafeStack
{
	stack<int> s;
	mutex mtx;
	condition_variable stackNotEmpty;
	atomic<int> size;

public:
	ThreadSafeStack()
	{
		size = 0;
	}

	void push(const int& val)
	{
		{
			unique_lock<mutex> lock(mtx);
			s.push(val);
			size++;
		}
		stackNotEmpty.notify_one();
	}

	void pop(int& val)
	{
		unique_lock<mutex> lock(mtx);
		stackNotEmpty.wait(lock, [this] {return size > 0; });
		val = s.top();
		s.pop();
		size--;
	}

	bool try_pop(int& val)
	{
		unique_lock<mutex> lock(mtx);
		if (size == 0)
			return false;
		val = s.top();
		s.pop();
		size--;
		return true;
	}

	bool empty()
	{
		unique_lock<mutex> lock(mtx);
		return s.empty();
	}
};

mutex mtx;
ThreadSafeStack* stk;
void syncPush(int i)
{
	unique_lock<mutex> lock(mtx);
	stk->push(i);
}
void syncPop()
{
	unique_lock<mutex> lock(mtx);
	int i;
	stk->pop(i);
	cout << i << " ";
}

int fdfmain()
{
	stk = new ThreadSafeStack();
	vector<thread> threads;
	for (int i = 0; i < 10; i++)
		threads.push_back(thread(syncPush, i));

	for (int i = 0; i < 10; i++)
		threads[i].join();

	for (int i = 0; i < 10; i++)
		threads[i] = thread(syncPop);

	for (int i = 0; i < 10; i++)
		threads[i].join();
	return 0;
}