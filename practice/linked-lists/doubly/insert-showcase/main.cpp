#include <iostream>

class Node {
public:
    int value;
    Node* next;
    Node* prev;
};

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void insertAtBeginning(Node*& head, int newValue) {
    Node* newNode = new Node(newValue);
    newNode->next = head;
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
}

void insertAtEnd(Node*& head, int newValue) {
    Node* newNode = new Node(newValue);
    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

void insertAfter(Node* prevNode, int newValue) {
    if (prevNode == nullptr) {
        std::cout << "The given previous node cannot be NULL" << std::endl;
        return;
    }

    Node* newNode = new Node(newValue);
    newNode->next = prevNode->next;
    newNode->prev = prevNode;

    if (prevNode->next != nullptr) {
        prevNode->next->prev = newNode;
    }
    prevNode->next = newNode;
}

void printOddNumbers(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value % 2 != 0) {
            std::cout << current->value << " ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

void doubleList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        current->value *= 2;
        current = current->next;
    }
}

int main() {
    Node* head = nullptr;
    Node* one = new Node(1);
    Node* two = new Node(2);
    Node* three = new Node(3);

    one->next = two;
    two->prev = one;
    two->next = three;
    three->prev = two;

    head = one;

    std::cout << "Original list: ";
    printList(head);

    insertAtBeginning(head, 4);
    std::cout << "List after insertion at the beginning: ";
    printList(head);

    insertAtEnd(head, 5);
    std::cout << "List after insertion at the end: ";
    printList(head);

    insertAfter(three, 6);
    std::cout << "List after insertion after the third node: ";
    printList(head);

    std::cout << "Odd numbers in the list: ";
    printOddNumbers(head);

    doubleList(head);
    std::cout << "List after doubling each value: ";
    printList(head);

    delete one;
    delete two;
    delete three;

    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return 0;
}