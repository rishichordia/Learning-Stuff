#include<iostream>
#include<mutex>
#include<condition_variable>
#include<map>
#include<vector>

using namespace std;

class ThreadSafeMap
{
	map<int, int> mp;
	mutex mtx;

public:
	ThreadSafeMap()
	{
	}

	void insert(int key, int val)
	{
		unique_lock<mutex> lock(mtx);
		mp.insert({ key, val });
		cout << "key:" << key << " Value:" << val << endl;
	}

	bool contains(int key)
	{
		unique_lock<mutex> lock(mtx);
		if (mp.find(key) != mp.end())
			return true;
		return false;
	}

	int get(int key)
	{
		unique_lock<mutex> lock(mtx);
		if (mp.find(key) != mp.end())
			return mp[key];

		return -1;
	}

	void erase(int key)
	{
		unique_lock<mutex> lock(mtx);
		mp.erase(key);
	}

	void clear()
	{
		unique_lock<mutex> lock(mtx);
		mp.clear();
	}
};

int fffmain()
{
	ThreadSafeMap* map = new ThreadSafeMap();
	vector<thread> threads;
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(thread([map, i]() {
			//cout << "Thread:- " << i << "\n";
			map->insert(i, i); }));
	}
	for (int i = 0; i < 10; i++)
	{
		threads[i].join();
	}
	for (int i = 0; i < 8; i++)
	{
		threads[i] = thread([map, i]() {
			bool result = map->contains(i);
			int val = map->get(i);
			map->erase(i);
			cout << val << endl; });
	}
	for (int i = 0; i < 8; i++)
		threads[i].join();
	map->clear();
	string f = map->contains(9) ? "True" : "False";
	cout << f << endl;
	return 0;
}