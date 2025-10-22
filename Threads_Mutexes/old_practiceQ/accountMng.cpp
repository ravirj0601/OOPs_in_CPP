#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>

struct Account{
    std::mutex m;
    int balance = 0;
    Account(int bal){
        balance = bal;
    }
};

void transferAmt(Account& to, Account& from , int amt){ 
    if (amt <= 0) {
        throw std::out_of_range("Minimum amount sould be 1 or more then that...!\n");
    }
    
    if (&to == &from) return;

    std::lock(to.m, from.m);
    std::lock_guard<std::mutex> g1(to.m, std::adopt_lock);
    std::lock_guard<std::mutex> g2(from.m, std::adopt_lock);
    
    if (from.balance < amt) {
        throw std::runtime_error("Insufficient Funds..!");
    }
    
    from.balance -= amt;
    to.balance += amt;
}

void transferAmt1(Account& to, Account& from , int amt){
    if (amt <= 0) {
        throw std::out_of_range("Minimum amount sould be 1 or more then that...!\n");
    }
    if (&to == &from) return;
    std::scoped_lock lx(to.m, from.m); 
    if (from.balance < amt) {
        throw std::runtime_error("Insufficient Funds..!");
    }
    from.balance -= amt;
    to.balance += amt;
}

void worker1(Account& a1,  Account& a2){
   for (int i = 0; i < 1000000; i++) {
        transferAmt1(a1, a2, 1);
   }
}
void worker2(Account& a1,  Account& a2){
   for (int i = 0; i < 1000000; i++) {
        transferAmt1(a2, a1, 1);
   }
}


int main(int argc, char *argv[]) {
    Account a1(1000000);
    Account a2(2000000);
    
    // int amt1 = atoi(argv[1]);
    // int amt2 = atoi(argv[2]);

    int totalSum = a1.balance + a2.balance;
    std::cout <<"a1: " << a1.balance << ", a2: " << a2.balance <</* ", Amount to be transfer: " \
        << amt << */", Sum of both Account: " << totalSum << std::endl;
    
    std::thread t1(worker1, std::ref(a1), std::ref(a2));
   std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    std::cout <<"a1: " << a1.balance << ", a2: " << a2.balance <</* ", Amount to be transfer: " \
        << amt << */", Sum of both Account: " << totalSum << std::endl;
    
    std::thread t2(worker2, std::ref(a1), std::ref(a2));
    
    t1.join();
    t2.join();
    
    std::cout <<"a1: " << a1.balance << ", a2: " << a2.balance << ", Sum of both Account: " \
        << a1.balance + a2.balance << std::endl;

    return 0;
}

