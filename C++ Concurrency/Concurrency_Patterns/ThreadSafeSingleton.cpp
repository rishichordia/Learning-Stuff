#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<vector>
#include<atomic>

using namespace std;

// This is implemented with double checked locking
class Singleton
{
	static mutex mx;
	static Singleton* instance;
	Singleton()
	{
		cout << "Initialized" << endl;
	}
public:
	static Singleton* get_instance()
	{
		if (instance == nullptr)
		{
			unique_lock<mutex> lock(mx);
			if (instance == nullptr)  // This is double checked locking
				instance = new Singleton();
		}
		return instance;
	}

	void doSomething()
	{
		cout << "Thread :" << this_thread::get_id << "\n";
	}
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mx;

void exec()
{
	Singleton* pointer = Singleton::get_instance();
	pointer->doSomething();
}

int threadSafeSingleton_main()
{
	vector<thread>threads;
	for (int i = 0; i < 5; i++)
	{
		threads.push_back(thread(exec));
	}
	for (auto& t : threads)
		t.join();
	return 0;
}