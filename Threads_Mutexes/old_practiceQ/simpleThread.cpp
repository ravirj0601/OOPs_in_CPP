#include <chrono>
#include <iostream>
#include <mutex>
#include <scoped_allocator>
#include <thread>

extern std::mutex m1, m2;
int counter = 0;

void worker1(){
    int local = 0;
    for (int i = 0; i < 10000000; ++i) {
        // lock memory on every counter++
        // counter++;
        // std::scoped_lock lk(m1, m2);
        std::lock(m1, m2);
        std::lock_guard<std::mutex> g1(m1, std::adopt_lock);
        std::lock_guard<std::mutex> g2(m2, std::adopt_lock);
        ++local;

         // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // std::lock_guard<std::mutex> g2(m2);
    }
    // {
    //     std::lock_guard<std::mutex> guard(m);
    //     counter += local; 
    // }
}

void worker2(){
    for (int i = 0; i < 10000000; ++i) {
        // std::lock_guard<std::mutex> guard(m);
        // std::lock_guard<std::mutex> g2(m2);
        // std::scoped_lock lk(m1, m2);
        std::lock(m1, m2);
        std::lock_guard<std::mutex> g1(m1, std::adopt_lock);
        std::lock_guard<std::mutex> g2(m2, std::adopt_lock);
        // ++local;
        ++counter;
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // std::lock_guard<std::mutex> g1(m1);
    }
}


int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(worker1);
    std::thread t2(worker2);
    

    t1.join();
    t2.join();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto ms  = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Elapsed: " << ms << "ms\n";

    std::cout << "Counter: "<< counter << "\n";
    return 1;
}

