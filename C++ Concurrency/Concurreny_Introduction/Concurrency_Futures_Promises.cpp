#include<thread>
#include<iostream>
#include<future>
#include<mutex>

using namespace std;

void multiply(int x, int y, promise<int>&& p)
{
	int prod = x * y;
	p.set_value(prod);
}

int f1f1main()
{
	promise<int> p;
	future<int> fut = p.get_future();

	thread t(multiply, 5, 6, move(p));
	t.join();
	if (fut.valid())
	{
		int prod = fut.get();
		cout << prod << endl;
	}
	return 0;
}
