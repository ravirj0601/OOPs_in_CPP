#include <ios>
#include <iostream>
#include <memory>
#include <utility>

struct Node{
    int value;
    Node* next;
    Node(int val): value(val), next(nullptr){}
};

// Forward declaration of List class
class List;

// Helper funnction for Copy Assignment 
void swap(List& first, List& second) noexcept;

class List{
    private:
        Node* head;
        friend void swap(List& first, List& second) noexcept; // Friend Declaration
    public:
        List():head(nullptr){}

        // Copy Constructor for LinkedList
        List(const List& other):head(nullptr){
            if (other.head == nullptr) {
                return; // Source list is empty, new list remains empty
            }

            head = new Node(other.head->value);
            Node* current_this = head;
            Node* current_other = other.head->next;

            while (current_other != nullptr) { // Loop while there are more nodes in 'other'
                current_this->next = new Node(current_other->value);
                current_this = current_this->next;
                current_other = current_other->next;
            }
        } 
        
        
        // Copy assigmment 
        List& operator=(const List& other){
            if (&other == this) {
                return *this;
            }
            List temp(other);
            swap(*this, temp);
            return *this;
        }
       
        void print() const { // Mark as const since it doesn't modify the list
            Node* current = head;
            std::cout << "List: ";
            while (current != nullptr) {
                std::cout << current->value << " -> ";
                current = current->next;
            }
            std::cout << "nullptr\n";
        }

        // Inserting element from front
        void insertFront(int val){
            Node* temp = new Node(val);
            if (head == nullptr) {
                head = temp;
            }else {
                temp->next = head;
                head = temp;
            }
        }

        void reverseIter(){
            if (head == nullptr) {
                std::cerr << "Empty List can not reverse....!\n";
                return;
            }
            Node* prv_node = nullptr;
            Node* curr_node = head;
            Node* next_node = nullptr;
            while (curr_node != nullptr) {
                next_node = curr_node->next;
                curr_node->next = prv_node;
                prv_node = curr_node;
                curr_node = next_node;
            }
            
            head = prv_node;
        }

        Node* reverseRec(Node* curr, Node* prev){
            if (curr == nullptr) {
                return prev;
            }
            Node* next_node = curr->next;
            curr->next = prev;
            prev = curr;
            return reverseRec(next_node, prev);
        }

        void reverseRecursive(){
            head = reverseRec(head, nullptr);    
        }

        ~List(){
            Node* current_node = head;
            while (current_node != nullptr) {
                Node* next_node = current_node->next;
                delete current_node;
                current_node = next_node;
            }
            head = nullptr;
        }
};

void swap(List& first, List& second) noexcept{
    using  std::swap;
    swap(first.head, second.head);
}

int main() {
    std::cout << "--- Simple Test ---\\n";

    List list1;
    list1.insertFront(3);
    list1.insertFront(2);
    list1.insertFront(1);
    std::cout << "Original list1: ";
    list1.print(); // Expected: List: 1 -> 2 -> 3 -> nullptr

    list1.reverseIter();
    std::cout << "list1 after iterative reverse: ";
    list1.print(); // Expected: List: 3 -> 2 -> 1 -> nullptr

    List list2 = list1; // Calls copy constructor
    std::cout << "list2 (copy of list1): ";
    list2.print(); // Expected: List: 3 -> 2 -> 1 -> nullptr

    list1.insertFront(0);
    std::cout << "list1 after modification: ";
    list1.print(); // Expected: List: 0 -> 3 -> 2 -> 1 -> nullptr
    std::cout << "list2 (should be unchanged): ";
    list2.print(); // Expected: List: 3 -> 2 -> 1 -> nullptr

    List list3;
    list3.insertFront(99);
    std::cout << "list3 before assignment: ";
    list3.print(); // Expected: List: 99 -> nullptr

    list3 = list1; // Calls copy assignment operator
    std::cout << "list3 after assignment from list1: ";
    list3.print(); // Expected: List: 0 -> 3 -> 2 -> 1 -> nullptr

    std::cout << "\\nAll objects will be destructed automatically.\\n";

    return 0;
}

