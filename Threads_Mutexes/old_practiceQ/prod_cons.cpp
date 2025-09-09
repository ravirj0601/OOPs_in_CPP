#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

std::mutex m;
std::condition_variable cv;
std::queue<int> q;
void producer(int a){ 
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    {
        std::lock_guard<std::mutex> g1(m);
        q.push(a);
    }
    cv.notify_one();
}

void consumer(){
    while (true)
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{ return !q.empty();});
        std::cout << "Value: " <<  q.front() << "\n";
        q.pop();
        lk.unlock();
        if (q.empty()) {
            break;
        }
    }
}

int main() {
    std::thread t1(producer, 111);
    std::thread t2(consumer);
    std::thread t3(producer, 323);
    // std::thread t2(consumer);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}

