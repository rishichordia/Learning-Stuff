#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

class CountDownLatch {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    explicit CountDownLatch(int cnt) : count(cnt) {}

    void countDown() {
        std::unique_lock<std::mutex> lock(mtx);
        if (--count == 0) {
            cv.notify_all();  // Release all waiting threads
        }
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return count == 0; });
    }
};

void worker(int id, CountDownLatch& latch) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id));
    std::cout << "Worker " << id << " finished.\n";
    latch.countDown();
}

int main() {
    const int num_workers = 5;
    CountDownLatch latch(num_workers);

    std::vector<std::thread> threads;
    for (int i = 0; i < num_workers; ++i) {
        threads.emplace_back(worker, i + 1, std::ref(latch));
    }

    std::cout << "Main thread waiting for workers to finish...\n";
    latch.wait();  // Will block until all countDown() calls are done
    std::cout << "All workers done. Proceeding in main thread.\n";

    for (auto& t : threads)
        t.join();

    return 0;
}