#include <condition_variable>
#include <ios>
#include <iostream>
#include<fstream>
#include <mutex>
#include <ostream>
#include <stdexcept>
#include <thread>
class FileHandle{
    private:
        std::mutex  m;
        std::condition_variable cv;
        std::string file_path = "./numbers.txt";
        int current;
        int N;
        std::ofstream file;
    public:
        FileHandle():current(1), N(30), file(file_path){
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + file_path);
            }
        }

        void storeOdd(){
            while (true) {
                 std::unique_lock<std::mutex> ul(m);
                 cv.wait(ul, [this]{ return (this->current % 2 == 1) || (this->current > N);});
                 if (current > N )break;
                 file << current << std::endl;
                 ++current;
                 cv.notify_all();
            }
        }
        
        void storeEven(){
            while (true) {
                 std::unique_lock<std::mutex> ul(m);
                 cv.wait(ul, [this]{ return (this->current % 2 == 0) || (this->current > N);});
                 if (current > N )break;
                 file << current << std::endl;
                 ++current;
                 cv.notify_all();
            }
        }

        ~FileHandle(){
            file.close();
        }
};

int main() {
    
    FileHandle fh;
    std::thread t1(&FileHandle::storeOdd, &fh);
    std::thread t2(&FileHandle::storeEven, &fh);

    t1.join();
    t2.join();

    std::cout << "All data store" << std::endl;
    return 0;
}

