#include <iostream>
#include <istream>
#include <string>
#include <utility>
using namespace std;


void ageVerification(){
    string name;
    int age;
    getline(cin, name);
    cin >> age;
    if (age < 0) {
        cerr <<  "Invalid Age!!!";
        return;
    }
    if (age < 18) {
        cout << "You are a Minor..!\n";
    }else{
        cout << "You are an  Adult..!\n";
    } 
}

void arrayOps(){
    int arr[5];
    int i = 0;
    cout << "Enter 5 integers:\n";
    while (i < 5) {
        cin >> arr[i];
        i++;
    }
    for(auto num:arr){
        cout << num << " ";
    }
}

int multiply(int a, int b){
    return a*b;
}

void swapINT(int &a, int &b){
    swap(a,b);
}

void swapInt(int* a, int* b){
    swap(*a, *b);
}

int main() {
    int a, b;
    int *p = &a;
    int *q = &b;
    cout << "Enter two numbers: ";
    cin >> *p >> *q;
    cout << "Before swap\nA: " << *p << ", B: " << *q << "\n";
    swapInt(p, q);
    cout << "After swap\nA: " << *p << ", B: " << *q << "\n";
    // int result = multiply(a, b);
    // cout << "Multiplication of " << a << " and " << b << " is " << result << "\n"; 
    // ageVerification();
    return 0;
}

