#include <iostream>
#include <string>
using namespace std;

class Person{
private:
    string name;
    int age;
public:
    // Default Constructor
    Person():name("Unknown"),age(0){}

    // Parameterized Constructor
    Person(string param_name, int param_age):name(param_name), age(param_age){}

    //Copy Constructor
    Person(const Person &other){
        name = other.name;
        age = other.age;
    }

    void display() const {
        cout << "Person Name: " << name << " and age is " << age << "\n";
    }

    ~Person(){
    }

};

int main() {
    
    Person monu;
    Person amit("Amit", 30);
    Person vinu = amit;

    monu.display();
    vinu.display();
    amit.display();
    return 0;
}

