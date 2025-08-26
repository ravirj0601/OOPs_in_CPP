#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
using namespace std;

// Base Class
class Shape{
    public:
        Shape(){}
        virtual double area() const = 0; // I can not make object of this class as it is a 
                                         // abstract class 
        virtual ~Shape () = default;
};

// Derieved Class 
class Circle : public Shape{
    private:
        double radius;
        // static const double pi = 3.14159;
    public:
        Circle():radius(2.3){};
        Circle(double radin) : radius(radin){}
        double area() const override {
            double ans;
            ans = M_PI*radius*radius;
            // cout << "Area of this Circle is: " << ans << "\n";
            return ans;
        }
        ~Circle(){}
};

//Derived Class
class Rectangle: public Shape{
    private:
        double length;
        double width;
    public:
        Rectangle():length(2),width(3){}
        Rectangle(double len, double wid):length(len),width(wid){}
        double area() const override {
            double ans;
            ans = length*width;
            // cout << "Area of Rectangle is: " << ans << "\n";
            return ans;
        }   
        ~Rectangle(){}
};

int main() {
    vector<Shape*> shapes;
    shapes.push_back(new Circle(5.0));
    shapes.push_back(new Rectangle(4.0, 6.0));
    
    // Output
    for (const auto& shape : shapes) {
        cout << "Area: " << shape->area() << "\n";
    }

    for (auto& shape : shapes) {
        delete shape;
    }
    return 0;
}

