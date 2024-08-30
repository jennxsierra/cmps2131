// Jennessa Sierra
// CMPS2131-1
// Singly Linked List Demo

#include <iostream>
using namespace std;

// Creating a node
class Node {
public:
    int value;
    Node* next;
};

// PRINTING FUNCTIONS
void printList(Node* head); // Print the list
void printListReverse(Node* head); // Print the list in reverse
void printOddNumbers(Node* head); // Print all nodes with odd numbers in the list

// MISCELLANEOUS FUNCTIONS
void doubleList(Node* head); // Double each of the nodes values

// INSERTING FUNCTIONS
void insertAtBeginning(Node*& head, int newValue); // Insert a new node at the beginning
void insertAtEnd(Node*& head, int newValue); // Insert a new node at the end
void insertAfterValue(Node* head, int targValue, int newValue); // Insert a new node after first node with target value
void insertAfterNode(Node* head, int pos, int newValue); // Insert a new node after a given node

// DELETING FUNCTIONS
void deleteFromBeginning(Node*& head); // Delete the first node
void deleteFromEnd(Node*& head); // Delete the last node
void deleteAtPos(Node*& head, int pos); // Delete a node at a given position

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
    cout << "After inserting 0 at the beginning: ";
    printList(head);

    // Insert a new node at the end
    insertAtEnd(head, 4);
    cout << "After inserting 4 at the end: ";
    printList(head);

    // Insert a new node after the first node with the value of two
    insertAfterValue(head, 2, 5);
    cout << "After inserting 5 after the first node with the value of two: ";
    printList(head);

    // Insert a new node after the third node
    insertAfterNode(head, 3, 6);
    cout << "After inserting 6 after the fourth node: ";
    printList(head);

    // Delete the first node
    deleteFromBeginning(head);
    cout << "After deletion at beginning: ";
    printList(head);

    // Delete the last node
    deleteFromEnd(head);
    cout << "After deletion at end: ";
    printList(head);

    // Delete the node third node
    deleteAtPos(head, 2);
    cout << "After deletion at third node: ";
    printList(head);

    // Print all odd numbers in the list
    cout << "Print odd numbers in the list: ";
    printOddNumbers(head);

    // Print the list in reverse
    cout << "Print list in reverse: ";
    printListReverse(head);

    // Double each of the nodes values
    doubleList(head);
    cout << "\nDoubled list: ";
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

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
}

void printListReverse(Node* head) {
    if (head == nullptr) {
        return;
    }

    // Recursive call to print the list in reverse
    printListReverse(head->next);
    std::cout << head->value << " ";
}

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

void doubleList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        current->value *= 2;
        current = current->next;
    }
}

void insertAtBeginning(Node*& head, int newValue) {
    Node* newNode = new Node();
    newNode->value = newValue;

    newNode->next = head; // Point new node's next to the current head
    head = newNode;       // Update head to point to the new node
}

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

void insertAfterValue(Node* head, int targValue, int newValue) {
    // Check if list is empty
    if (head == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }

    // Traverse to the node with the target value
    while(head != nullptr && head->value != targValue) {
        head = head->next;
    }

    // If the target value is not found
    if (head == nullptr) {
        cout << "The target value was not found in the list." << endl;
        return;
    }

    // If the target value is at the end of the list
    if (head->next == nullptr) {
        insertAtEnd(head, newValue);
        return;
    }

    // Create the new node
    Node* newNode = new Node();
    newNode->value = newValue;

    // Insert the new node after the node with the target value
    newNode->next = head->next;
    head->next = newNode;
}

void insertAfterNode(Node* head, int pos, int newValue) {
    // Check if list is empty
    if (head == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }

    // Insert at the beginning if pos is 0
    if (pos == 0) {
        insertAtBeginning(head, newValue);
        return;
    }

    Node* current = head;
    // Traverse to the node at the given position
    for (int i = 0; i < pos; i++) {
        if (current == nullptr) {
            cout << "The list is not long enough." << endl;
            return;
        }
        current = current->next;
    }

    // Insert at end if pos is at the end of the list
    if (current == nullptr) {
        insertAtEnd(head, newValue);
        return;
    }

    // Create the new node
    Node* newNode = new Node();
    newNode->value = newValue;

    // Insert the new node after the current node
    newNode->next = current->next;
    current->next = newNode;
}

void deleteFromBeginning(Node*& head) {
    if (head == nullptr) return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

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

void deleteAtPos(Node*& head, int pos) {
    // Check if position is valid
    if (head == nullptr || pos < 0) {
        cout << "Invalid position." << endl;
        return;
    }

    // Delete at beginning if pos is 0
    if (pos == 0) {
        deleteFromBeginning(head);
        return;
    }

    // Traverse to the node before the position
    Node* current = head;
    for (int i = 0; i < pos - 1; i++) {
        if (current == nullptr) {
            cout << "The list is not long enough." << endl;
            return;
        }
        current = current->next;
    }

    // Check if the node exists
    if (current == nullptr || current->next == nullptr) {
        cout << "The node does not exist." << endl;
        return;
    }

    // Delete the node
    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
}
