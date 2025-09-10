#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

class ProdCons{
    private:
        queue<int> u;
        int min_val;
        int max_val;
        int _limit;
        mutex m1;
        condition_variable cv;


        int randomNoGen(){
            return min_val+(rand() % (max_val - min_val+1));
        }

    public:
        
        ProdCons(int lim):min_val(1), max_val(200), _limit(lim){}
        
        void producer(){
            while (true) {
                unique_lock<mutex> cvl(m1);
                cv.wait(cvl, [&](){return u.size() < _limit;});
                int temp = randomNoGen();
                u.push(temp);
                cout << temp << " Pushed....\n";
                this_thread::sleep_for(chrono::milliseconds(20));
                cv.notify_one();
            } 
        }

        void consumer(){
            while (true) {
                unique_lock<mutex> cvl(m1);
                cv.wait(cvl,[&](){return !u.empty();});
                cout << "Poped value: " << u.front() << "\n";
                u.pop();
                this_thread::sleep_for(chrono::milliseconds(20));
                cv.notify_one();
            }
        }

};

int main() {
    srand(time(0));
    ProdCons pc1(9);
    thread t1 = thread(&ProdCons::producer, &pc1);
    thread t2 = thread(&ProdCons::consumer, &pc1);

    t1.join();
    t2.join();

    return 0;
}

