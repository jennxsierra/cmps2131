#include <iostream>

// Creating a node
class Node {
public:
    int data;
    Node* next;
};

void printList(Node* head); // Print the list

void deleteMid(Node*& head_ref); // Delete the middle node

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
    std::cout << "Original list: ";
    printList(head);

    //Delete the middle node
    deleteMid(head);

    // Print the list after deleting the middle node
    std::cout << "List after deleting the middle node: ";
    printList(head);

    // Wait for user input before closing the console
    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    // Clean up allocated memory
    delete one;
    delete two;
    delete three;
    delete four;
    delete five;

    return 0;
}

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void deleteMid(Node*& head_ref) {
    // If the list is empty, return
    if (head_ref == nullptr) {
        return;
    }

    // If the list contains only one node, delete it and update the head reference
    if (head_ref->next == nullptr) {
        delete head_ref;
        head_ref = nullptr;
        return;
    }

    // Initialize slow and fast pointers to reach the middle node
    // Slow pointer moves one node at a time, fast pointer moves two nodes at a time
    // When the fast pointer reaches the end of the list, the slow pointer will be at the middle node
    Node* slow = head_ref;
    Node* fast = head_ref;

    // Initialize a pointer to keep track of the previous node of the middle node
    Node* prev = nullptr;

    // Traverse the list to find the middle node
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    // Delete the middle node
    prev->next = slow->next;
    delete slow;
}