#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    
    vector<int> v = {2,7,2,1,5,9};
    sort(v.begin(), v.end(), [](int a, int b){return a > b;});
    for (auto const num : v) {
        cout << num << " "; 
    }
    
    cout << "\n";
    int threshold = 5;
    auto check = [=](int x){return x > threshold;};
    cout << check(2) << "\n";

    //  Printing a simple msges through lambda
    [](){cout << "Study Mode going to ON...\n";}();
    auto msg = [](){cout << "Study Mode ON\n";};
    msg();
   
    // Parameterized lambda fn.
    auto prd = [=](int a, int b){return a*b;};
    cout << "Product: " << prd(4, 2) << "\n";

    return 0;
}

