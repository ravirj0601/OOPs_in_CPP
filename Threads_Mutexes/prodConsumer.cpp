#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Prod_Cons{
    private:
        int count;
        int limit;
        mutex m1;
        condition_variable cv;
        bool done = false;
    public:
        Prod_Cons(int lim):limit(lim),count(0){};
        void printEven(){
            while(true){
                unique_lock<mutex> lk(m1);
                cv.wait(lk, [&](){ return (count%2==0) || (count >= limit);});
                if (count == limit) {
                    break;
                }
                cout << ++count << " ";
                if (done) {
                    done = true;
                }
                cv.notify_one();
            }
            cout << "\n";
        }

        void printOdd(){
            while(true){
                unique_lock<mutex> lk(m1);
                cv.wait(lk, [&](){ return (count%2==1) || (count >= limit);});
                if (done) {
                    break;
                }
                cout << ++count << " ";
                if (count == limit) {
                    done = true;
                }
                cv.notify_one();
            }
            cout << "\n";
        }
};

int main() {
    Prod_Cons pr1(50);
    thread t1 = thread(&Prod_Cons::printEven, &pr1);
    thread t2 = thread(&Prod_Cons::printOdd, &pr1);
    t1.join();
    t2.join();
    return 0;
}

