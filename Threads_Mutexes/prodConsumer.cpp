#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

int generate_random_number();

class ProducerConsumer{
    private:
        std::queue<int> buffer;
        int limit;
        const int cap;
        int count;
        std::mutex m;
        std::condition_variable cv_full, cv_empty;

    public:
        ProducerConsumer(int stopCount): limit(stopCount) ,cap(5), count(0){}
        
        void producer(){
            while (true) {
                std::unique_lock<std::mutex> pl(m);
                //while (buffer.size() >= cap) {
                cv_full.wait(pl, [&]{return buffer.size() < cap || count >= limit;});
                if (count >= limit) {std::cout << "Producer Stopped...\n"; break;}
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                int no = generate_random_number();
                buffer.push(no);
                std::cout << "Pushed Number: " << no << "\n";
                ++count;
                cv_empty.notify_one();
            }
        }
             

        void consumer(){
            while (true) {
                std::unique_lock<std::mutex> lq(m);
                // while (buffer.size() == 0) {
                //     cv_empty.wait(lq);
                // }
                cv_empty.wait(lq, [&]{return !buffer.empty() || count >= limit; });
                if (buffer.empty() && count >= limit) {
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                int no = buffer.front();
                buffer.pop();
                std::cout << "Consumer: " << no << "\n"; 
                cv_full.notify_one();
            }
        }
        

        ~ProducerConsumer(){
            while (!buffer.empty()) {
                buffer.pop();
            }
        }

};

int generate_random_number() {
    static std::random_device rd;          // Non-deterministic seed source
    static std::mt19937_64 gen(rd());         // Mersenne Twister engine, seeded once
    
    // Distribution for range [0, 250]
    static std::uniform_int_distribution<> distrib(0, 250);

    return distrib(gen); // Generate and return a number
}

int main() {
    ProducerConsumer pc(20);
    std::thread t1(&ProducerConsumer::producer, &pc);
    std::thread t2(&ProducerConsumer::consumer, &pc);

    t1.join();
    t2.join();

    return 0;
}

