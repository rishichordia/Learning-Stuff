#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include<shared_mutex>

using namespace std;

int shared_data = 0;
int reader_count = 0;
int writer_count = 0;

shared_mutex resource_mutex;
mutex write_mutex;
condition_variable writer_signal;

void reader2(int id) {
    {
        unique_lock<mutex> waitForWriters(write_mutex);
        writer_signal.wait(waitForWriters, []() {return writer_count == 0; });
    }
    shared_lock<shared_mutex> readers(resource_mutex);
    std::cout << "Reader " << id << " reads: " << shared_data << std::endl;
}

void writer2(int id) {
    {
        unique_lock<mutex> incrementWriters(write_mutex);
        writer_count++;
    }
    unique_lock<shared_mutex> lock(resource_mutex, defer_lock);
    lock.lock();
    shared_data++;
    std::cout << "Writer " << id << " writes: " << shared_data << std::endl;
    lock.unlock();
    {
        unique_lock<mutex> decrementWriter(write_mutex);
        writer_count--;
        if (writer_count == 0)
            writer_signal.notify_all();
    }
}

int wmain() {
    const int NUM_READERS = 3;
    const int NUM_WRITERS = 2;
    std::vector<std::thread> threads;

    for (int i = 0; i < 5; ++i) {
        if (i % 2 == 0) {
            for (int j = 1; j <= NUM_READERS; ++j) {
                threads.emplace_back(reader2, j);
            }
        }
        else {
            for (int j = 1; j <= NUM_WRITERS; ++j) {
                threads.emplace_back(writer2, j);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final shared_data: " << shared_data << std::endl;

    return 0;
}