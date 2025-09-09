#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;
mutex m1;
condition_variable cv;
int counter = 0;


void addeven(int limit){
    while (true) {
        unique_lock<mutex> lk(m1);
        cv.wait(lk, [&](){return (counter%2==0) || (counter > limit);});
        
        if (counter > limit) {
            break;
        }
        ++counter;
        cout<< counter << "\n"; 
        cv.notify_one();
    }
}

void addodd(int limit){
    while (true) {
        unique_lock<mutex> lk(m1);
        cv.wait(lk, [&](){return (counter%2==1) || (counter > limit);});
        if (counter > limit) {
            break;
        }
        ++counter;
        cout<< counter << "\n"; 
        cv.notify_one();
    }
}



int main() {
    int limit = 50;
    thread t1 = thread(addeven, limit);
    thread t2 = thread(addodd, limit);

    t1.join();
    t2.join();
    return 0;
}

