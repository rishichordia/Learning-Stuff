#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<condition_variable>
#include<chrono>

using namespace std;

class ProducerConsumer
{
	queue<int> q;
	int max_size;
	mutex queue_mutex;
	condition_variable cv_empty, cv_full;
	atomic<bool> stop_flag;

public:
	ProducerConsumer(int size)
	{
		max_size = size;
		stop_flag = false;
	}

	void producer(int id)
	{
		for (int i = 0; i < 5; i++)
		{
			unique_lock<mutex> lock(queue_mutex);
			cv_full.wait(lock, [this]() {return q.size() < max_size || stop_flag; });
			if (stop_flag)
				return;
			q.push(i);
			cout << "Producer "<< id <<" produced " << i << "\n";
			lock.unlock();
			cv_empty.notify_one();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}

	void consumer(int id)
	{
		while (true)
		{
			unique_lock<mutex> lock(queue_mutex);
			cv_empty.wait(lock, [this]() { return !q.empty() || stop_flag; });
			if (stop_flag)
				return;
			int curr = q.front();
			q.pop();
			cout << "Consumer " << id << " consumes: " << curr << "\n";
			cv_full.notify_one();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}

	void stop()
	{
		stop_flag = true;
		cv_full.notify_all();
		cv_empty.notify_all();
	}
};


int producer_consumer_main()
{
	ProducerConsumer* p = new ProducerConsumer(10);
	vector<thread> threads;

	threads.push_back(thread(&ProducerConsumer::producer, p, 1));
	threads.push_back(thread(&ProducerConsumer::producer, p, 2));
	threads.emplace_back(thread(&ProducerConsumer::consumer, p, 1));
	threads.emplace_back(thread(&ProducerConsumer::consumer, p, 2));

	this_thread::sleep_for(chrono::seconds(2));
	p->stop();

	for (int i = 0;i<threads.size();i++)
		threads[i].join();
	return 0;
}