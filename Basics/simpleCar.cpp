#include <iostream>
#include <string>
using namespace std;

class Car{
    private:
        string color;
        string model;
        int numbers;
    public:
        //Default Constructor
        Car(){}

        //Parametterized Constructor
        Car(string col,  string mod, int no){
            color = col;
            model = mod;
            numbers = no;
        }
        // Copy constructor
        Car(const Car &other){
            color = other.color;
            model = other.model;
            numbers = other.numbers;
        }
        //  Copy assignment operator
        Car& operator=(const Car &other){
            if (this != &other) {
                color = other.color;
                model = other.model;
                numbers = other.numbers;
            }
            return *this;
        }

        // Operator overloading
        Car operator+(const Car &other){
            return Car(color + "-" + other.color, model + "-" + other.model, numbers + other.numbers);
            
        }

        bool operator==(const Car &other){
            return (color == other.color && model == other.model && numbers == other.numbers);
        }

        void displayDetails(){
            cout << "Car model is "  << model <<  " Color is " << color << " Total no of production No: "\
                << numbers << endl;
        }
};

int main() {
    Car Tata("Blue", "Tiago", 1000);
    Tata.displayDetails();
    
    Car LandRover("Red", "Defender", 50);
    LandRover.displayDetails();

    Car parentCompaney;
    parentCompaney = Tata + LandRover;

    parentCompaney.displayDetails();

    if (Tata == LandRover) {
        cout << "Both are same....!\n";
    }else {
        cout << "Both are Different....!\n";
    }

    return 0;
}

