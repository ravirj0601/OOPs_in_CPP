#include <iostream>
#include <stack>
#include <stdexcept>
using namespace std;

class QueueUsingStacks{
    private:
        stack<int> first;
        stack<int> second;
    public:
        void enqueue(int value){
            first.push(value);
        }

        int dequeue(){
            if (isEmpty()) {
                throw runtime_error("Queue is empty...!");
            }

            if (second.empty()) {
                while (!first.empty()) {
                    int temp = first.top();
                    first.pop();
                    second.push(temp);
                }
            }
            int temp = second.top();
            second.pop();
            return temp;
        }

        bool isEmpty(){
            return first.empty() && second.empty();
        }
};

int main() {
    QueueUsingStacks queue1;
    queue1.enqueue(4);
    queue1.enqueue(7);
    queue1.enqueue(9);
    cout << queue1.dequeue();
    return 0;
}

