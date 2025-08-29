#include <exception>
#include <iostream>
#include <mutex>
#include <stdexcept>

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

int main(int argc, char *argv[]) {
    Account a1(1000);
    Account a2(2000);
    
    int amt = atoi(argv[1]);
    
    std::cout <<"a1: " << a1.balance << ", a2: " << a2.balance << ", Amount to be transfer: " << amt << "\n";
    try {
        transferAmt1(a1, a2, amt);
    } catch (std::exception& e) {
        std::cerr << "Error found: " << e.what() << "\n";
    }
    std::cout <<"a1: " << a1.balance << ", a2: " << a2.balance << "\n";

    return 0;
}

