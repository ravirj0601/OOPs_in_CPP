#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Lambda fn with STL
    /**
    vector<int> v = {2, 6, 8, 1, 3, 9, 10, 7};
    auto count = count_if(v.begin(), v.end(), [](int x){return x%2==0;});
    
    auto is_even = [](int x){return x%2==0;};
    auto count2 = count_if(v.begin(), v.end(), is_even);
    cout << count << "\n" <<  count2 << "\n";
    */
    
    int no = 0;
    int limit = 50;
    while (true) {
        [&no](){no++;}();
        if (no == 20) {
            break;
        }
    }
    
    cout << no << "\n";
    
    auto f = [no]()mutable{++no; return no;};
    while (true) {
        int ni = f();
        if (ni >= limit) {
            break;
        }
        // no = ni;
        cout << ni << "\n";
    }

    cout << no << "\n";
    return 0;
}

