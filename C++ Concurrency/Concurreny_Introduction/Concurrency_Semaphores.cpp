#include<iostream>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<chrono>

using namespace std;

class Semaphore {
	mutex mx;
	condition_variable cv;
	int count;
public:
	Semaphore(int count = 0)
	{
		this->count = count;
	}
	void wait()
	{
		unique_lock<mutex> lock(mx);
		cv.wait(lock, [this]() {return count > 0; });
		count--;
	}

	void signal()
	{
		unique_lock<mutex> lock(mx);
		count++;
		cv.notify_one();
	}
};

void worker(Semaphore& sem, int id) {
	cout << "Worker " << id << " waiting...\n";
	sem.wait();
	cout << "Worker " << id << " acquired semaphore\n";
	this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << "Worker " << id << " releasing semaphore\n";
	sem.signal();
}

int main()
{
	Semaphore sem(2);
	thread t1(worker, ref(sem), 1);
	thread t2(worker, ref(sem), 2);
	thread t3(worker, ref(sem), 3);
	thread t4(worker, ref(sem), 4);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}