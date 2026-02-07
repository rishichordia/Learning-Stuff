#include<iostream>
#include<atomic>
#include<thread>
#include<vector>

using namespace std;

atomic<int> inc = 0;

class Spinlock {
	atomic_flag flag = ATOMIC_FLAG_INIT;
public:
	void lock()
	{
		while (flag.test_and_set(memory_order_acquire));
	}

	void unlock()
	{
		flag.clear(memory_order_release);
	}
};

Spinlock spin;
int spin_count = 0;

void incr(int times)
{
	for (int i = 0; i < times; i++)
	{
		spin.lock();
		spin_count++;
		spin.unlock();
	}
}

void a1()
{
	inc++;
}

int file3_main()
{
	vector<thread> threads;
	for (int i = 0; i < 1000; i++)
	{
		threads.push_back(thread(a1));
	}
	for (int i = 0; i < 1000; i++)
	{
		threads[i].join();
	}
	int val = inc.load();
	int cmp = 1001;
	inc.compare_exchange_strong(cmp, 0);
	cout << val << "and" << cmp<< endl;
	val = inc.load();
	cout << val << endl;


	for (int i = 0; i < 5; i++)
	{
		threads[i] = thread(incr, 1000);
	}
	for (int i = 0; i < 5; i++)
	{
		threads[i].join();
	}
	cout << spin_count << endl;
	return 0;
}