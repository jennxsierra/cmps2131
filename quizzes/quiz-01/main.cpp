#include <iostream>
using namespace std;

// Creating a node
class Node {
public:
    int data;
    Node* next;
};

// Print the list
void printList(Node* head);

// Delete ALL odd numbers from the list
void deleteOdd(Node*& head);

// Reverse list by changing the next pointers
void reverseList(Node*& head);

int main() {
    Node* head = nullptr;
    Node* one = nullptr;
    Node* two = nullptr;
    Node* three = nullptr;

    // Allocate 3 nodes in the heap
    one = new Node();
    two = new Node();
    three = new Node();

    // Assign data
    one->data = 1;
    two->data = 2;
    three->data = 3;

    // Connect nodes
    one->next = two;
    two->next = three;
    three->next = nullptr;

    // Set the head of the list
    head = one;

    // Print the initial list
    cout << "Original list: ";
    printList(head);

    // Reverse the list
    reverseList(head);

    // Print the list after reversing
    cout << "List after reversing: ";
    printList(head);

    // Delete odd numbers
    deleteOdd(head);

    // Print the list after deleting odd numbers
    cout << "List after deleting ALL odd numbers: ";
    printList(head);

    // Wait for user input before closing the console
    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void deleteOdd(Node*& head) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->data % 2 != 0) {
            if (prev == nullptr) {
                head = current->next;
                delete current;
                current = head;
            } else {
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void reverseList(Node*& head) {
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;  // Store next node
        curr->next = prev;  // Reverse current node's pointer
        prev = curr;        // Move prev one step forward
        curr = next;        // Move curr one step forward
    }

    head = prev;  // Update head to the new front of the list
}

