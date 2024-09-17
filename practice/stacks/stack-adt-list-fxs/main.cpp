#include <iostream>

// Creating a node
class Node {
public:
    int data;
    Node* next;
};

// Function to push an element onto the stack (insert at the beginning of the linked list)
void push(Node*& top, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = top;  // Point to the current top
    top = newNode;        // Update the top to the new node
    std::cout << "Pushed " << value << " to the stack." << std::endl;
}

// Function to pop an element from the stack (remove from the beginning of the linked list)
void pop(Node*& top) {
    if (top == nullptr) {
        std::cout << "Stack is empty, cannot pop." << std::endl;
        return;
    }
    Node* temp = top;
    top = top->next;  // Move top to the next node
    std::cout << "Popped " << temp->data << " from the stack." << std::endl;
    delete temp;  // Delete the popped node
}

// Function to return the top element of the stack without popping it
int top(Node* top) {
    if (top == nullptr) {
        std::cout << "Stack is empty." << std::endl;
        return -1;  // Return an error value if stack is empty
    }
    return top->data;  // Return the value at the top
}

// Function to check if the stack is empty
bool isEmpty(Node* top) {
    return top == nullptr;
}

// Function to print the stack's contents
void printStack(Node* top) {
    if (isEmpty(top)) {
        std::cout << "Stack is empty." << std::endl;
        return;
    }
    Node* current = top;
    std::cout << "Stack contents: ";
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
    Node* stackTop = nullptr;  // Initialize an empty stack (top is nullptr)

    // Push elements onto the stack
    push(stackTop, 10);
    push(stackTop, 20);
    push(stackTop, 30);

    // Print current stack
    printStack(stackTop);

    // Pop top element and print
    pop(stackTop);
    printStack(stackTop);

    // Check the top element
    std::cout << "Top element is: " << top(stackTop) << std::endl;

    // Check if stack is empty
    std::cout << "Is stack empty? " << (isEmpty(stackTop) ? "Yes" : "No") << std::endl;

    return 0;
}
