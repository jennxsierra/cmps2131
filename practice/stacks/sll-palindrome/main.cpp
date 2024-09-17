#include <iostream>
#include <cctype>
#include <string>

// Creating a node structure for the linked list-based stack
class Node {
public:
    char value;
    Node* next;
};

// Function to push an element onto the stack
void push(Node*& top, char value) {
    Node* newNode = new Node();
    newNode->value = value;
    newNode->next = top;
    top = newNode;
}

// Function to pop an element from the stack
void pop(Node*& top) {
    if (top == nullptr) {
        std::cout << "Stack is empty, cannot pop." << std::endl;
        return;
    }
    Node* temp = top;
    top = top->next;
    delete temp;
}

// Function to return the top element of the stack without popping it
char top(Node* top) {
    if (top == nullptr) {
        std::cout << "Stack is empty." << std::endl;
        return '\0'; // Return null character if stack is empty
    }
    return top->value;
}

// Function to check if the stack is empty
bool isEmpty(Node* top) {
    return top == nullptr;
}

// Function to check if a string is a palindrome
bool isPalindrome(std::string input) {
    Node* stackTop = nullptr;
    int length = input.length();
    int mid = length / 2;

    // Push the first half of the string onto the stack (ignoring non-alphabetic characters)
    for (int i = 0; i < mid; ++i) {
        if (std::isalpha(input[i])) {  // Only consider alphabetic characters
            push(stackTop, std::toupper(input[i])); // Push the uppercase version for case insensitivity
        }
    }

    // Adjust if the length of the string is odd
    if (length % 2 != 0) {
        mid++;
    }

    // Compare the second half of the string with the stack
    for (int i = mid; i < length; ++i) {
        if (std::isalpha(input[i])) {
            char currentChar = std::toupper(input[i]);
            if (currentChar != top(stackTop)) {
                return false;
            }
            pop(stackTop);
        }
    }

    return true;
}

int main() {
    std::string testWord;
    std::cout << "Enter a string (end with '.'): ";
    std::getline(std::cin, testWord, '.');

    if (isPalindrome(testWord)) {
        std::cout << "The string is a palindrome." << std::endl;
    } else {
        std::cout << "The string is not a palindrome." << std::endl;
    }

    std::cin.get();  // Consume the newline character left in the input buffer
    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
