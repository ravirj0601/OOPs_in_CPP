#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>

class CreateList{
    private:
        std::string file_name = "./number2.txt";
        int current;
        int n;
        std::mutex m;
        std::condition_variable cv;
        std::ofstream file;
    public:
        CreateList(int N) : current(1), n(N), file(file_name){
            if (!file.is_open()) {
                throw std::runtime_error("File can not be open " + file_name);
            } 
        }

        void storeThree(){
            while (true) {
                std::unique_lock<std::mutex> pl(m);
                while (current %  3 == 0 && current <= n) {
                    cv.wait(pl);
                }
                if (current > n) {
                    cv.notify_all();
                    break;
                }
                file << current << "\n";
                ++current;
                cv.notify_all();
            }
        }

        void storeFive(){
            while (true) {
                std::unique_lock<std::mutex> pl(m);
                while (current % 3 == 1 && current <= n) {
                    cv.wait(pl);
                }
                if (current > n) {
                    cv.notify_all();
                    break;
                }
                file << current << "\n";
                ++current;
                cv.notify_all();
            }
        }
        
        void storeSeven(){
            while (true) {
                std::unique_lock<std::mutex> pl(m);
                while (current % 3 == 3 && current <= n) {
                    cv.wait(pl);
                }
                if (current > n) {
                    cv.notify_all();
                    break;
                }
                file << current << "\n";
                ++current;
                cv.notify_all();
            }
        }
        ~CreateList(){
            file.close();
        }
};



int main() {
    CreateList ls(40);
    std::thread t1(&CreateList::storeThree, &ls);
    std::thread t2(&CreateList::storeFive, &ls);
    std::thread t3(&CreateList::storeSeven, &ls);

    t1.join();
    t2.join();
    t3.join();
    std::cout << "Data Stored\n";
    return 0;
}

