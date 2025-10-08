#include <cstddef>
#include <fstream>
#include <iostream>
using namespace std;
class Node{
    public:
        int val_;
        Node* next;
        Node(int value):val_(value),next(nullptr){}
};

class NodeOps{
    private:
        Node* head;
    public:
        NodeOps():head(nullptr){}
        void insertAtEnd(int value){
            Node* newNode = new Node(value);
            if (head == nullptr) {
                head = newNode;
                return;
            }else{
                Node* curr = head;
                while (curr->next != nullptr) {
                    curr = curr->next;
                }
                curr->next = newNode;
            }
        }

        void deleteNode(int val){
            if (head == nullptr) {
                cout << "List is empty.\n";
                return;
            }

            Node* curr = head;
            Node* prev = nullptr;
            if (head->val_ == val) {
                Node* temp = head;
                head = head->next;
                delete temp;
                return;
            }
            
            while (curr != nullptr && curr->val_!=val) {
                prev = curr;
                curr = curr->next;
            }
            if (curr != nullptr) {
                prev->next = curr->next;
                delete curr;
            }else {
                cout << "Node with Value " << val << " not faund.\n";
            }
        }

        void displayList(){
            if (head == nullptr) {
                cout << "List is empty.\n";
                return; 
            }
            cout << "List Elements: ";
            Node* curr = head;
            while (curr != nullptr) {
                cout << curr->val_ << " ";
                curr = curr->next;
            }
            cout << "\n";
        }

        void reverseList(){
            
            if (head == nullptr) {
                cout << "List is empty..!\n";
                return;
            }
            Node* prev_Node = nullptr;
            Node* curr_Node = head;
            Node* next_Node = nullptr;
            while (curr_Node !=  nullptr) {
                next_Node = curr_Node->next;
                curr_Node->next = prev_Node;
                prev_Node = curr_Node;
                curr_Node = next_Node;
            }
            head = prev_Node;
        }

        ~NodeOps(){
            while (head != nullptr) {
                Node* temp = head->next;
                delete head;
                head = temp;
            }
        }

};
int main() {
    NodeOps list1;
    list1.insertAtEnd(3);
    list1.insertAtEnd(9);
    list1.insertAtEnd(8);
    list1.insertAtEnd(30);
    list1.insertAtEnd(10);
    list1.displayList();
    list1.deleteNode(8);
    list1.displayList();
    list1.reverseList();
    list1.displayList();
    return 0;
}

