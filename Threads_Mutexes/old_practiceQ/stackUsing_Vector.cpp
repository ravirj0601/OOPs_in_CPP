// #include <condition_variable>
#include <iostream>
// #include <mutex>
#include <vector>
using namespace std;

class StackUsingVector{
    private:
        vector<int> st;
        // mutex m1;
        // condition_variable cv;
    public:
        StackUsingVector(){}
        void push(int x){
            st.push_back(x);
        }

        int pop(){
            int res = st.back();
            st.pop_back();
            return res;
        }

        int top(){
            int res = st.back();
            return res;
        }
        
        bool empty(){
            return st.empty();
        }

        void printst(){
            cout << "Vector's Elements: ";
            for (const auto nums : st) {
                cout << nums << " ";
            }
            cout << "\n";
        }
};

int main() {
    StackUsingVector stck;
    stck.push(4);
    stck.push(6);
    stck.push(7);
    stck.printst();
    stck.pop();
    stck.printst();

    return 0;
}

