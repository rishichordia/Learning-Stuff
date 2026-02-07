#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

int shared_data1 = 0;
int reader_count1 = 0;

mutex reader_mutex1;
mutex write_mutex1;

void reader1(int id) {
    {
        lock_guard<mutex> lock(reader_mutex1);
        reader_count1++;
        if (reader_count1 == 1) {
            write_mutex1.lock();
        }
    }

    cout << "Reader " << id << " reads: " << shared_data1 << endl;

    {
        lock_guard<std::mutex> lock(reader_mutex1);
        reader_count1--;
        if (reader_count1 == 0) {
            write_mutex1.unlock();
        }
    }
}

void writer1(int id) {
    unique_lock<mutex> lock(write_mutex1);
    shared_data1++;
    cout << "Writer " << id << " writes: " << shared_data1 << endl;
}

int fmain() {
    const int NUM_READERS = 3;
    const int NUM_WRITERS = 2;
    vector<thread> threads;

    for (int i = 0; i < 5; ++i) {
        if (i % 2 == 0) {
            for (int j = 1; j <= NUM_READERS; ++j) {
                threads.emplace_back(reader1, j);
            }
        }
        else {
            for (int j = 1; j <= NUM_WRITERS; ++j) {
                threads.emplace_back(writer1, j);
            }
        }
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final shared_data: " << shared_data1 << std::endl;

    return 0;
}