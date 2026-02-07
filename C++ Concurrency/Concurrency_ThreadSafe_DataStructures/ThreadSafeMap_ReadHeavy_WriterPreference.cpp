#include<iostream>
#include<shared_mutex>
#include<condition_variable>
#include<map>
#include<vector>

using namespace std;

class ThreadSafeMapAdv_W
{
	map<int, int> mp;
	shared_mutex mtx;
	mutex check_writers;
	atomic<int> writers_waiting;
	condition_variable readSafe;

public:
	ThreadSafeMapAdv_W()
	{}

	void set(int key, int val)
	{
		{
			unique_lock<mutex> waitOnWritersLock(check_writers);
			writers_waiting++;
		}
		unique_lock<shared_mutex> lock(mtx);
		mp[key]= val;
		{
			unique_lock<mutex> waitOnWritersLock(check_writers);
			writers_waiting--;
			if (writers_waiting == 0)
				readSafe.notify_all();
		}
		//cout << "key:" << key << " Value:" << val << endl;
	}

	bool contains(int key)
	{
		return mp.find(key) != mp.end();
	}

	int get(int key)
	{
		unique_lock<mutex> waitOnWritersLock(check_writers);
		readSafe.wait(waitOnWritersLock, [this]() {return writers_waiting == 0; });
		shared_lock<shared_mutex> lock(mtx);
		waitOnWritersLock.unlock();
		
		if (mp.find(key) != mp.end())
			return mp[key];
		return -1;
	}

	void erase(int key)
	{
		{
			unique_lock<mutex> waitOnWritersLock(check_writers);
			writers_waiting++;
		}
		unique_lock<shared_mutex> lock(mtx);
		mp.erase(key);
		{
			unique_lock<mutex> waitOnWritersLock(check_writers);
			writers_waiting--;
			if (writers_waiting == 0)
				readSafe.notify_all();
		}
	}

	void clear()
	{
		unique_lock<shared_mutex> lock(mtx);
		mp.clear();
	}
};

int main()
{
	ThreadSafeMapAdv_W* map = new ThreadSafeMapAdv_W();
	vector<thread> threads;
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(thread([map, i]() {
			//cout << "Thread:- " << i << "\n";
			map->set(i, i); }));
	}
	for (int i = 0; i < 10; i++)
	{
		threads[i].join();
	}
	thread t([map]() {int val = map->get(1); cout << "Thread t " << val << endl; });
	thread t1([map]() {int val = map->get(2); cout << "Thread t1 " << val << endl; });
	thread t2([map]() {int val = map->get(3); cout << "Thread t2 " << val << endl; });
	t.join();
	t1.join();
	t2.join();
	for (int i = 0; i < 8; i++)
	{
		threads[i] = thread([map, i]() {
			bool result = map->contains(i);
			int val = map->get(i);
			//map->erase(i);
			cout << val << endl; });
	}

	for (int i = 0; i < 8; i++)
		threads[i].join();

	map->clear();
	string f = map->contains(9) ? "True" : "False";
	cout << f << endl;
	delete(map);
	return 0;
}