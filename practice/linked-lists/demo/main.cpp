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

// Function to print the linked list in reverse
void printListReverse(Node* head) {
    if (head == nullptr) {
        return;
    }

    printListReverse(head->next);
    std::cout << head->value << " ";
}

// Function to print all odd numbers in the linked list
void printOddNumbers(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value % 2 != 0) {
            cout << current->value << " ";
        }
        current = current->next;
    }
    cout << endl;
}

// Function to double each of the nodes values
void doubleList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        current->value *= 2;
        current = current->next;
    }
}

// Function to insert a new node at the beginning of the list
void insertAtBeginning(Node*& head, int newValue) {
    Node* newNode = new Node();
    newNode->value = newValue;

    newNode->next = head; // Point new node's next to the current head
    head = newNode;       // Update head to point to the new node
}

// Function to insert a new node at the end of the list
void insertAtEnd(Node*& head, int newValue) {
    Node* newNode = new Node();
    newNode->value = newValue;
    newNode->next = nullptr;

    // If the list is empty, make the new node the head
    if (head == nullptr) {
        head = newNode;
        return;
    }

    // Otherwise, traverse to the end of the list
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    // Link the last node to the new node
    current->next = newNode;
}

// Function to insert a new node at any position
void insertAfter(Node* prevNode, int newValue) {
    if (prevNode == nullptr) {
        cout << "The given previous node cannot be nullptr" << endl;
        return;
    }

    Node* newNode = new Node();
    newNode->value = newValue;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
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
    three->next = nullptr;

    // Set the head of the list
    head = one;

    // Print the initial list
    cout << "Original list: ";
    printList(head);

    // Insert a new node at the beginning
    insertAtBeginning(head, 0);
    cout << "After inserting at the beginning: ";
    printList(head);

    // Insert a new node at the end
    insertAtEnd(head, 4);
    cout << "After inserting at the end: ";
    printList(head);

    // Insert a new node after the second node
    insertAfter(two, 5);
    cout << "After inserting after the second node: ";
    printList(head);

    // Delete the first node
    deleteFromBeginning(head);
    cout << "After deleting the first node: ";
    printList(head);

    // Delete the last node
    deleteFromEnd(head);
    cout << "After deleting the last node: ";
    printList(head);

    // Delete the node after the second node
    deleteAfter(two);
    cout << "After deleting the node after the second node: ";
    printList(head);

    // Print all odd numbers in the list
    cout << "Odd numbers in the list: ";
    printOddNumbers(head);

    // Double each of the nodes values
    doubleList(head);
    cout << "After doubling each node's value: ";
    printList(head);

    // Print the list in reverse
    cout << "List in reverse: ";
    printListReverse(head);

    // Clean up allocated memory
    delete one;
    delete two;
    delete three;

    // Wait for user input before closing the console
    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}