#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
int couter = 0;
mutex m1;

void worker1(){
    for (int i= 0; i < 1000000; i++) {
        atomic<int> couter{0};
        lock_guard<mutex> guard(m1);
        couter++;
    }
}

void worker2(){
    for (int i= 0; i < 1000000; i++) {
        atomic<int> couter{0};
        lock_guard<mutex> guard(m1);
        couter++;
    }
}

int main() {
    thread t1 = thread(worker1);    
    thread t2 = thread(worker2);

    t1.join();
    t2.join();
    
    cout << couter << endl;
    return 0;
}

