#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class Buffer{
    private:
        vector<int> arr_;
    public:
        
        Buffer() = default;

        explicit Buffer(vector<int> vec)  noexcept : arr_(vec){
            cout << "Parameterized ctor\n";
        }
        ~Buffer(){
            cout << "Destructor\n";
        }
        
        // Copy constructor
        Buffer(const Buffer& other) : arr_(other.arr_){
            cout << "Copy ctor:\n";
        }
        // Move Constructor
        Buffer(Buffer&& other) : arr_(std::move(other.arr_)){
            cout << "Move ctor:\n";
        }
        
        // Copy assignment
        Buffer& operator=(const Buffer& other){
            cout << "Copy assign:\n";
            //if (this != &other) {
            //    return *this;
            //}
            Buffer tmp(other);
            swap(tmp);
            return *this;
        }

        // Move assignment
        Buffer& operator=(Buffer&& other) noexcept {
            cout << "Move assign\n";
            // if (this != &other) {
            //     return *this;
            // }
            arr_ = std::move(other.arr_);
            return *this;
        }

        void swap(Buffer& other) noexcept{
            arr_.swap(other.arr_);
        }

        void print() const {
            cout << "Elements: ";
            for (const auto nums : arr_) {
                cout << nums << " ";
            }
            cout << "\n";
        }
};

int main() {
    Buffer a(vector<int>{1, 2, 3});
    Buffer b = a;
    cout << "A: ";
    a.print();
    cout << "\nb: ";
    b.print();

    Buffer c(vector<int>{4, 5, 6, 7});
    cout << "\nc: ";
    c.print();
    c = a;
    cout << "\nc: ";
    c.print();

    Buffer d = Buffer(vector<int>{8, 9});
    cout << "\nd: ";
    d.print();
    Buffer e;
    e = Buffer(vector<int>{10, 11});
    cout << "\ne: ";
    e.print();
    
    return 0;
}

