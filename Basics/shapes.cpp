#include <cmath>
#include <iostream>
#include <memory>
using namespace std;

// abstract class
class Shapes{
public:
    Shapes(){}
    virtual void print() = 0;
    
    // Function Overloading
    // void print(int a, int b){
    //     cout << "A:" << a << " ,B:" << b << "\n";
    // }

    virtual ~Shapes(){}
};

// Derived Class
class Circle:public Shapes{
    int radius;
    const double pie = 3.14159;
    public:
        Circle(int rad){
            radius = rad;
        }

        // Function Overriding
        void print() override{
            cout << "Area of circle is: " << pie * (radius * radius) << "\n";
        }
};

// Derived Class
class Rectangle : public Shapes{
private:
    int width;
    int hight;
public:
    Rectangle(int wid, int hig){
        width = wid;
        hight = hig;
    }

    void print() override{
        cout << "Rectangle volume of this: " <<  width * hight  << "\n";
    }

};

int main() {
    // Using simple pointer we need to delete it manually
    Shapes* cirS = new Circle(5); 
    Shapes* rectS =  new Rectangle(3, 8);
    
    unique_ptr<Shapes> cirS1 = make_unique<Circle>(9);
    unique_ptr<Shapes> rectS2 = make_unique<Rectangle>(5, 8);
    // Can not create object as it is a base class
    // Shapes kkk; // Can not create object as it is a base class
    // kkk.print();
    // kkk.print(5, 8);
    cirS->print();
    rectS->print();
    cout << "-----------------------\n";
    cirS1->print();
    rectS2->print();
    delete cirS;
    delete rectS;
    return 0;
}

