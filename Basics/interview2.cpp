#include <complex>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>
using namespace std;

// struct Example{
//     int a; // 4 byte
//     char b; // 1 byte
//             // 4 + 1 + 3 = 8 byte;
// }


mutex mt;
std::condition_variable prod;
std::condition_variable consu;
queue<int> buffer;
int MAX_BUFFER_SIZE = 5;
bool is_done = false;

void writer(vector<int> list){
    int lSize = list.size();
    for (int i = 0; i <= lSize-1; i++) {
        std::unique_lock<mutex> lock(mt);
        // prod.wait(lock,[&]{return i <= lSize;});
        prod.wait(lock, []{return buffer.size() < MAX_BUFFER_SIZE;});
        buffer.push(list[i]);
        lock.unlock();
        consu.notify_one();
    }
    std::unique_lock<mutex> lock(mt);
    is_done = true;
    consu.notify_all(); // Notify all waiting consumers that production is complete
}

void user(){
    while(true){
        std::unique_lock<mutex> lock(mt);
        consu.wait(lock,[]{return !buffer.empty() || is_done;});
        if (buffer.empty() && is_done) {
            break; // Exit if buffer is empty and producer is done
        }
        cout << buffer.front() << " ";
        buffer.pop();
        lock.unlock();
        prod.notify_one();
    }
}

int main() {
    vector<int> list = {4, 5, 7, 1, 3, 5, 8,7, 4, 5, 0,6, 8,5 ,6 ,4 ,4 ,3,1 ,1};
    std::thread t1 = std::thread(writer,list);
    std::thread t2 = std::thread(user);

    t1.join();
    t2.join();
    cout << "\n";
    return 0;
}
