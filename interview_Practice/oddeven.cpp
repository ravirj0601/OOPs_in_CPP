#include <condition_variable>
#include <exception>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
using namespace std;

class OddEven{
    private:
        int count;
        int limit;
        mutex m1;
        condition_variable cv;
        bool done = false;
    public:
        OddEven(int cap): limit(cap), count(0){
            if (limit <= 0) {
                throw std::invalid_argument("Limit must be greater than 0!");
            }
        }

        void printEven(){
            while (true) {
                unique_lock<mutex> l1(m1);
                cv.wait(l1,[&](){return (count%2==0) || (count >= limit);});
                if (done) {
                    break;
                }
                cout << ++count << " " ;
                if (count == limit) {
                    done = true;
                    cv.notify_all();
                }
                cv.notify_one();
            }
            cout << "\n";
        }
        void printOdd(){
            while (true) {
                unique_lock<mutex> l1(m1);
                cv.wait(l1,[&](){return (count%2==1) || (count >= limit);});
                if (done) {
                    break;
                }
                cout << ++count << " " ;
                if (count == limit) {
                    done = true;
                    cv.notify_all();
                }
                cv.notify_one();
            }
            cout << "\n";
        }
    
};

int main() {
    OddEven ops1(50); 

    OddEven* ops2_ptr = nullptr;
    try {
        ops2_ptr = new OddEven(-50); 
    } catch (const std::invalid_argument& e) {
        cout << "Error creating OddEven instance with negative limit: " << e.what() << "\n";
    }

    thread t1, t2; 
    thread t3, t4; 

    try {
        t1 = thread(&OddEven::printEven, &ops1);
        t2 = thread(&OddEven::printOdd, &ops1);

        if (ops2_ptr != nullptr) { 
            t3 = thread(&OddEven::printEven, ops2_ptr);
            t4 = thread(&OddEven::printOdd, ops2_ptr);
        }
    } catch (const std::exception &e) { 
        cout << "Terminated because of " << e.what() << "\n"; 
    }
    
    t1.join();
    t2.join();

    if (ops2_ptr != nullptr) {
        t3.join();
        t4.join();
        delete ops2_ptr; 
    }

    return 0;
}

