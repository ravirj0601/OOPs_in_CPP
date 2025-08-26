#include <cstddef>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Base{
    private:
        string sn;
    public:
        // Base default constr
        Base():sn("Random"){
            cout << "Base Class default const: value: " << sn << "\n";
        }
        // Base parameterized constr
        Base(string s):sn(s){
            cout << "Base Class parameterized constr: " << sn << "\n";    
        }
        // Base copy constr
        Base(const Base& other){
            sn = other.sn;
            cout << "Base Class copy constr: " << sn << "\n";    
        }
        // Base destructor
        virtual ~Base(){
            cout << "Base class destructor...!\n"; 
        }
};

class Derived : public Base{
    private:
        string ss;
    public:
        // Derived defalut constr
        Derived(){
            cout << "Derived class default const\n";
        }
        // Derived parameterized constr
        Derived(string s):Base(s),ss(s){
            cout << "Derived class parameterized constr local: "<< ss << ", Derieved: " << s << "\n";
        }
        // Derived copy constr
        Derived(const Derived& other) : Base(other), ss(other.ss){
            // ss = other.ss;
            cout << "Derived class copy constr "<< ss << "\n";
        }
        // Derived Destructor
        ~Derived(){
            cout << "Derived class destructor...!\n"; 
        };
};

class Buffer{
    private:
         char* data;
         size_t size;
    public:
        // Buffer Deafault Constr..
        Buffer() : data(nullptr), size(0){
            cout << "Buffer() - default constr (data: " << static_cast<void*>(data) << ", size: " << size << ")\n";
        }
            
        // Buffer Parameterized Constr..
        Buffer(size_t s):data(new char[s]), size(s){
            memset(data, 0, size);  // Zero-Initialize to the buffer
            cout << "Buffer(size_t) - parameterized constr (data: " << static_cast<void*>(data) << ", size: " << size << ")\n"; 
        }

        // Buffer Copy constructor
        Buffer(const Buffer& other) : data(new char[other.size]), size(other.size){
            memcpy(data, other.data, size);
            cout << "Buffer() - copy constr (data: " << static_cast<void*>(data) << ", size: " << size << ")\n";  
        }
        
        // Buffer Move Constructor
        Buffer(Buffer&& other) noexcept : data(other.data), size(other.size){
           
            other.data = nullptr;
            other.size = 0;
            cout << "Buffer() - Move constructor (data: " << static_cast<void*>(data) << ", size: " << size << ")\n";
        }

        // Buffer Copy Assignment
        Buffer& operator=(const Buffer& other){
            cout << "Buffer() - copy Assignment (data: " << static_cast<void*>(data) << ", size: " << size << ")\n"; 
            if (this != &other) { 
                char* new_data = new  char[other.size];
                std::memcpy(new_data, other.data, other.size);
                delete[] data;
                data = new_data;
                size  = other.size;
            }
            return *this;
        }

        // Buffer Move Assignment
        Buffer& operator=(Buffer&& other) noexcept {
            cout << "Buffer& operator=(Buffer&&) - Move Assignment Operator\n";
            if (this != &other) {
                delete[] data;
                data = other.data;
                size = other.size;
                other.data = nullptr;
                other.size = 0;
            }
            return *this;
        }


        // Destructor
        ~Buffer(){
            cout << "~Buffer() - destructor (data: " << static_cast<void*>(data) << ", size: " << size << ")\n";
            delete[] data;
            data = nullptr;
            size = 0;
        }
        
};

int main() {
    // Part A & B tests (keep them for context)
    Derived d("D");
    std::unique_ptr<Base> p = std::make_unique<Derived>("PD"); 

    std::cout << "\n--- Buffer Class Tests ---\n";

    // Test 1: Default Constructor
    Buffer default_buffer;

    // Test 2: Parameterized Constructor
    Buffer a(1024); 

    // Test 3: Copy Constructor
    Buffer b = a; // Should call copy constructor

    // Test 4: Copy Assignment Operator
    Buffer c(2048);
    c = a; // Should call copy assignment operator

    // Test 5: Move Constructor (using a temporary object)
    // The compiler might optimize this with NRVO, but it's a good conceptual test.
    // To force a move, you might use std::move, but for temporaries, it's automatic.
    Buffer d_moved = Buffer(4096); 

    // Test 6: Move Assignment Operator
    Buffer e(512);
    e = Buffer(128); // Should call move assignment operator

    std::cout << "--- End of Buffer Class Tests ---\n\n";

    return 0;
}

