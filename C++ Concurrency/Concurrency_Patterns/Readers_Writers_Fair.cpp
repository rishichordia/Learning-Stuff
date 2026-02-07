#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include<shared_mutex>
#include<queue>
#include<unordered_set>

using namespace std;

class ThreadSafeQueue
{
	queue<int> q;
	mutex mtx;
	condition_variable queueNotEmpty;

public:
	ThreadSafeQueue()
	{}

	void push(const int& val)
	{
		{
			unique_lock<mutex> lock(mtx);
			q.push(val);
		}
		queueNotEmpty.notify_one();
	}

	void pop()
	{
		unique_lock<mutex> lock(mtx);
		queueNotEmpty.wait(lock, [this] {return !q.empty(); });
		q.pop();
	}

	bool try_pop(int& val)
	{
		unique_lock<mutex> lock(mtx);
		if (q.empty())	return false;
		val = q.front();
		q.pop();
		return true;
	}

	bool empty()
	{
		unique_lock<mutex> lock(mtx);
		return q.empty();
	}

	int front()
	{
		unique_lock<mutex> lock(mtx);
		return q.front();
	}
};

int common_data = 0;
int readers_count = 0;

shared_mutex resource_mutex1;
condition_variable cv;
mutex data_mutex;

ThreadSafeQueue* q;
int next_reader_group = 1;
unordered_set<int> reader_group_pushed;

void reader(int id) {
	int my_group;
	{
		unique_lock<mutex> lock(data_mutex);
		my_group = next_reader_group;
		if (reader_group_pushed.find(my_group) == reader_group_pushed.end())
		{
			reader_group_pushed.insert(my_group);
			q->push(my_group);
		}
		cv.wait(lock, [&]() {return my_group <= q->front() && q->front() < 1000; });
		readers_count++;
	}
	{
		shared_lock<shared_mutex> rlock(resource_mutex1);
		this_thread::sleep_for(chrono::milliseconds(50));
		cout << "Reader " << id << " reads: " << common_data << endl;
	}
	{
		unique_lock<mutex> lock2(data_mutex);
		readers_count--;
		if (readers_count == 0)
		{
			next_reader_group++;
			q->pop();
			reader_group_pushed.erase(next_reader_group);
			cv.notify_all();
		}
	}
}

void writer(int id) {
	{
		unique_lock<mutex> lock(data_mutex);
		q->push(id);
		next_reader_group++;
		cv.wait(lock, [&]() {return q->front() == id; });
	}
	{
		unique_lock<shared_mutex> lock(resource_mutex1);
		common_data++;
		this_thread::sleep_for(chrono::milliseconds(50));
		cout << "Writer " << id << " writes: " << common_data << std::endl;
	}
	{
		unique_lock<mutex> lock(data_mutex);
		q->pop();
		cv.notify_all();
	}
}

int reader_writer_main() {
    const int NUM_READERS = 3;
    const int NUM_WRITERS = 2;
    std::vector<std::thread> threads;
	int reader_thread_id = 1;
	int writer_thread_id = 1001;
	q = new ThreadSafeQueue();
    for (int i = 0; i < 6; ++i) {
        if (i % 2 == 0) {
            for (int j = 1; j <= NUM_READERS; ++j) {
                threads.emplace_back(reader, reader_thread_id);
				reader_thread_id++;
            }
        }
        else {
            for (int j = 1; j <= NUM_WRITERS; ++j) {
                threads.emplace_back(writer, writer_thread_id);
				writer_thread_id++;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final common_data: " << common_data << std::endl;
	
	delete q;
    return 0;
}