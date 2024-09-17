#include <iostream>
using namespace std;

// Creating a node
class Node {
public:
    int data;
    Node* next;
};

// Function to print the linked list
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Function to reverse the linked list
void reverseList(Node* head) {
    if (head == nullptr) {
        return;
    }

    reverseList(head->next);
    std::cout << head->data << " ";
}

int main() {
    Node* head = nullptr;
    Node* one = nullptr;
    Node* two = nullptr;
    Node* three = nullptr;
    Node* four = nullptr;
    Node* five = nullptr;

    // Allocate 5 nodes in the heap
    one = new Node();
    two = new Node();
    three = new Node();
    four = new Node();
    five = new Node();

    // Assign values
    one->data = 1;
    two->data = 2;
    three->data = 3;
    four->data = 4;
    five->data = 5;

    // Connect nodes
    one->next = two;
    two->next = three;
    three->next = four;
    four->next = five;
    five->next = nullptr;

    // Set the head of the list
    head = one;

    // Print the initial list
    cout << "Original list: ";
    printList(head);

    // Reverse the list
    cout << "Reverse list: ";
    reverseList(head);

    // Wait for user input before closing the console
    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}