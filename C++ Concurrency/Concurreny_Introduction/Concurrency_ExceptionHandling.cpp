#include<iostream>
#include<thread>
#include<future>
#include<mutex>

using namespace std;

mutex mut;

void fun(int x, int y, promise<int>&& p)
{
	try {
		cout << "Inside thread: " << this_thread::get_id() << endl;;
		int mul = x * y;
		throw exception("sample exception");
	}
	catch (exception e)
	{
		p.set_exception(current_exception());
	}
}

int main()
{
	promise<int>prom;
	future<int> f = prom.get_future();
	thread t(fun, 5, 5, move(prom));
	t.join();

	try {
		f.get();
	}
	catch (const exception &e)
	{
		cout << "Exception received is -" << e.what() << endl;
	}
}