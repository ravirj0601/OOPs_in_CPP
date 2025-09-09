#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

std::mutex m1, m2;
int shared = 0;

// void A() {
//     std::this_thread::sleep_for(std::chrono::milliseconds(10)); // simulate work
//     std::scoped_lock lk(m1, m2); // take BOTH locks atomically (deadlock-free)
//     ++shared;                    // critical section
// }
// 
// void B() {
//     std::this_thread::sleep_for(std::chrono::milliseconds(10));
//     std::scoped_lock lk(m1, m2); // same order/strategy
//     ++shared;
// }

void A() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::lock(m1, m2);                                    // lock both together
    std::lock_guard<std::mutex> g1(m1, std::adopt_lock);  // adopt
    std::lock_guard<std::mutex> g2(m2, std::adopt_lock);  // adopt
    ++shared;
}

void B() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::lock(m1, m2);
    std::lock_guard<std::mutex> g1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> g2(m2, std::adopt_lock);
    ++shared;
}

int main() {
    std::thread t1(A), t2(B);
    t1.join();
    t2.join();
    std::cout << "shared = " << shared << "\n";
}
