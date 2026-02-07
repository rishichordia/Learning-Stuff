#include<iostream>
#include<mutex>
#include<condition_variable>
#include<unordered_map>
#include<algorithm>
#include<chrono>
#include<queue>
#include<deque>

typedef long long int ll;
using namespace std;

class RateLimiter {
	using Clock = chrono::high_resolution_clock;
	using TimePoint = chrono::time_point<Clock>;

	unordered_map<ll, deque<ll>> clients;
	unordered_map<ll, unique_ptr<mutex>> client_mutexes;
	mutex registration_mutex;
	ll allowed_requests;
	ll window_ms;

public:
	RateLimiter(ll requests, ll window_ms = 1000)
	{
		allowed_requests = requests;
		this->window_ms = window_ms;
	}
	void register_client(ll client_id)
	{
		unique_lock<mutex> lock(registration_mutex);
		if (clients.find(client_id) != clients.end())
			return;
		clients[client_id] = deque<ll>();
		client_mutexes[client_id] = make_unique<mutex>();
	}
	bool allow(int clientid)
	{
		{
			lock_guard<mutex> reg_lock(registration_mutex);
			if (clients.find(clientid) == clients.end())
				return false;
		}

		auto now = Clock::now();
		ll current_ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
		
		unique_lock<mutex> lock(*client_mutexes[clientid]);
		deque<ll>& timestamps = clients[clientid];
		while (!timestamps.empty() && current_ms - timestamps.front() >= window_ms)
		{
			timestamps.pop_front();
		}
		if (timestamps.size() < allowed_requests)
		{
			timestamps.push_back(current_ms);
			return true;
		}

		return false;
	}
};

int main()
{
	RateLimiter r1(5);
	r1.register_client(101);
	if (r1.allow(101))
		cout << "Request Allowed\n";
	else
		cout << "Request rejected\n";
	return 0;
}