#include <iostream>
#include <stack>
#include <stdexcept>

class QueueUsingStacks{
    private:
        std::stack<int> first;
        std::stack<int> second;
        void transfer_Element(){
            if (second.empty()) {
                while (!first.empty()) {
                    int temp = first.top();
                    first.pop();
                    second.push(temp);
                }
            }
        }
    public:
        void enqueue(int value){
            first.push(value);
        }

        int dequeue(){
            if (isEmpty()) {
                throw std::runtime_error("Queue is empty...!");
            }
            transfer_Element();
            int temp = second.top();
            second.pop();
            return temp;
        }

        int front(){
            if (isEmpty()) {
                throw std::runtime_error("Queue is empty...!");
            }
            transfer_Element();
            return second.top();
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
    std::cout << queue1.dequeue();
    return 0;
}

