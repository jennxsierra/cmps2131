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
    while (current != NULL) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
}

// Function to insert a new node at the beginning of the list
void insertAtBeginning(Node*& head, int newValue) {
    Node* newNode = new Node();
    newNode->value = newValue;
    newNode->next = head; // Point new node's next to the current head
    head = newNode;       // Update head to point to the new node
}

// Function to print all odd numbers in the linked list
void printOddNumbers(Node* head) {
    Node* current = head;
    while (current != NULL) {
        if (current->value % 2 != 0) {
            cout << current->value << " ";
        }
        current = current->next;
    }
    cout << endl;
}

// Function to insert a new node at the end of the list
void insertAtEnd(Node*& head, int newValue) {
    Node* newNode = new Node();
    newNode->value = newValue;
    newNode->next = NULL;

    // If the list is empty, make the new node the head
    if (head == NULL) {
        head = newNode;
        return;
    }

    // Otherwise, traverse to the end of the list
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Link the last node to the new node
    current->next = newNode;
}

// Function to double each of the nodes values
void doubleList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        current->value *= 2;
        current = current->next;
    }
}

// Function to insert a new node after a given node
void insertAfter(Node* prevNode, int newValue) {
    // Check if the given previous node is NULL
    if (prevNode == NULL) {
        cout << "The given previous node cannot be NULL" << endl;
        return;
    }

    // Allocate new node
    Node* newNode = new Node();

    // Assign data to the new node
    newNode->value = newValue;

    // Make the next of the new node as the next of the previous node
    newNode->next = prevNode->next;

    // Move the next of the previous node to point to the new node
    prevNode->next = newNode;
}


int main() {
    Node* head = NULL;
    Node* one = NULL;
    Node* two = NULL;
    Node* three = NULL;

    // Allocate 3 nodes in the heap
    one = new Node();
    two = new Node();
    three = new Node();

    // Assign values
    one->value = 1;
    two->value = 2;
    three->value = 3;

    // Connect nodes
    one->next = two;
    two->next = three;
    three->next = NULL;

    // Set the head of the list
    head = one;

    // Print the initial list
    cout << "Original list: ";
    printList(head);

    // Insert a new node at the beginning
    insertAtBeginning(head, 0);

    // Print the updated list
    cout << "List after insertion at the beginning: ";
    printList(head);

    // Print all odd numbers in the list
    cout << "Odd numbers in the list: ";
    printOddNumbers(head);

    // Insert a new node at the end
    insertAtEnd(head, 4);

    // Print the updated list
    cout << "List after insertion at the end: ";
    printList(head);

    // Insert a new node after the third node
    insertAfter(three, 5);

    // Print the updated list
    cout << "List after insertion after the third node: ";
    printList(head);

    // Double each of the nodes values
    doubleList(head);

    // Print the updated list
    cout << "List after doubling each value: ";
    printList(head);

    // Clean up allocated memory
    delete one;
    delete two;
    delete three;

    // Wait for user input before closing the console
    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}