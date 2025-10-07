#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

void sReverse(string &s){
    if (s.empty()) return;
    auto start = s.begin();
    auto end = s.end() - 1;
    while (start < end) {
        // swap(*start, *end);
        iter_swap(start, end);
        ++start;
        --end;
    }
}

int main() {
    string st = "Henlo";
    cout << st << "\n";
    sReverse(st);
    cout << st << "\n";
    return 0;
}

