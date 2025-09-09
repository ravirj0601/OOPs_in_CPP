#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

int main() {

    vector<string> v = {
        "apple", "kiwi", "banana", "appla", "fig", "strawberry"
    };
    vector<string> ans;
    
    for (auto &w : v) {
        transform(w.begin(), w.end(), w.begin(),
                [](unsigned char c){
                return toupper(c); });
    }

    transform(v.begin(), v.end(), back_inserter(ans),
           [](string s){
           reverse(s.begin(), s.end());
           return s;
           });

    for (auto const &w : v) {
        cout << w << " ";
    }
    cout << "\n"; 
    for (auto const &w : ans) {
        cout << w << " ";
    }
    cout << "\n";
    return 0;
}
   


    /**
    vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    vector<int> ans;
    transform(v.begin(), v.end(), back_inserter(ans),
            [](int x){
            return x*x;
            });
    for (const auto num : ans) {
        cout << num << " ";
    }

    vector<int> ans;
    copy_if(v.begin(), v.end(), back_inserter(ans),
            [](int x){
            return x%2==0;
            });
    for (const auto &no : ans) {
        cout << no << " ";
    }
    cout << "\n";
    
    std::sort(v.begin(), v.end(), 
            [](const string &a, const string &b){
            if (a.size() == b.size()) {
                return a < b;
            }
            return a.size() < b.size();
            }); 

    cout << "\n";
    */

    // Using lambda for for_each STL
    // vector<int> v = {1, 2, 3, 4, 5};
    // int sum = 0;
    // auto sum2 = [&sum](int x){return sum+=x;};
    // for_each(v.begin(), v.end(), [&sum](int x){return sum+=x;});
    // cout << "Sum: " << sum << "\n";

    // return 0;
// }

