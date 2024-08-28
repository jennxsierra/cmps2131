#include <iostream>
using namespace std;

// Creating a node
class Node {
public:
    int value;
    Node* next;
};

// Function to print the linked list
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
}

// Function to delete the first node of the list
void deleteFromBeginning(Node*& head) {
    if (head == nullptr) return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

// Function to delete the last node of the list
void deleteFromEnd(Node*& head) {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
}

// Function to delete a node after a given node
void deleteAfter(Node* prevNode) {
    if (prevNode == nullptr || prevNode->next == nullptr) {
        cout << "The given node is nullptr or the next node is nullptr" << endl;
        return;
    }
    Node* temp = prevNode->next;
    prevNode->next = temp->next;
    delete temp;
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
    one->value = 1;
    two->value = 2;
    three->value = 3;
    four->value = 4;
    five->value = 5;

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

    // Delete a node from the beginning
    deleteFromBeginning(head);
    cout << "List after deletion from the beginning: ";
    printList(head);

    // Delete a node from the end
    deleteFromEnd(head);
    cout << "List after deletion from the end: ";
    printList(head);

    // Delete a node after the second node
    deleteAfter(two);
    cout << "List after deletion after the second node: ";
    printList(head);

    // Clean up allocated memory
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Wait for user input before closing the console
    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}