#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template <typename RandomIt>
void sortBinary(RandomIt first, RandomIt last){
    if (first == last) return;
    auto low = first;
    auto mid = first;
    auto high = last - 1;
    while (mid <= high) {
        if (*mid == 0)
            iter_swap(low++, mid++);
        else if (*mid == 1)
            mid++;
        else
            iter_swap(mid, high--);
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

void run_test(std::vector<int> v, std::vector<int> expected) {
    sortBinary(v.begin(), v.end());
    assert(v == expected);
}

int main() {
    run_test({2,0,2,1,1,0}, {0,0,1,1,2,2});
    run_test({}, {});
    run_test({0}, {0});
    run_test({2}, {2});
    run_test({1,1,1}, {1,1,1});
    run_test({0,0,0,1,2,2}, {0,0,0,1,2,2});
    run_test({2,2,2,0,0,0}, {0,0,0,2,2,2});
    run_test({0,2,1,2,0,1,0}, {0,0,0,1,1,2,2});
    std::cout << "All tests passed.\n";

// int main() {
    //vector<int> listEle = {1,2,2,1,0,2,0,2,1,0,1,1,2,0,1,0};
    // printArr(listEle);
    
    // Three pointer way
    // sortBinary(listEle);

    // Single lambda Function will work to sort anything
    // sort(listEle.begin(), listEle.end(), [](int x, int y){
    //         return x < y;
    //         });
    
    // Using lambda function 
   //  auto it = partition(listEle.begin(), listEle.end(), [](int x){
   //          return x == 0;
   //          });
   //  partition(it, listEle.end(),[](int x){
   //          return x == 1;
   //          });
   //  printArr(listEle);
    return 0;
}

