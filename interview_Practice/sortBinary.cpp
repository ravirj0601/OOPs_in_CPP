#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
void sortBinary(vector<int> &list){
    if (list.empty()) return;
    auto start = list.begin();
    auto end = list.end() - 1;
    while (start < end) {

        while (start < end && *start == 0) {
            ++start;
        }
        while (start < end && *end == 1) {
            --end;
        }
        if(start<end)iter_swap(start++, end--);
    }
}

void printArr(vector<int> &list){
    if (list.empty()) return;
    cout << "List Element: ";
    for (const auto num : list) {
        cout << num << " ";
    }
    cout << "\n";
}
int main() {
    vector<int> listEle = {1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0};
    printArr(listEle);
    // sortBinary(listEle);
    partition(listEle.begin(), listEle.end(), [](int x){return x == 0;});
    printArr(listEle);
    return 0;
}

