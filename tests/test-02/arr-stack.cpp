#include <iostream>
using namespace std;

class Stack {
    int* stack;
    int n;

public:
    Stack(int size) {
        n = size;
        stack = new int[n];
        stack[n-1] = -1;
    }

    ~Stack() {
        delete[] stack;
    }

    // Push operation
    void push(int value) {
        if (isFull()) {
            cout << "Stack is full" << endl;
            return;
        }
        stack[++stack[n-1]] = value;
    }

    // Pop operation
    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return stack[stack[n-1]--];
    }

    // Check if the stack is empty
    bool isEmpty() {
        return stack[n-1] == -1;
    }

    // Check if the stack is full
    bool isFull() {
        return stack[n-1] == n - 2;
    }

    // Print the stack
    void printStack() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack elements: ";
        for (int i = 0; i <= stack[n-1]; i++) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack s(5);

    s.push(10);
    s.push(20);
    s.push(30);

    s.printStack();

    cout << "Popped element: " << s.pop() << endl;
    s.printStack();

    cout << "Is stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;
    cout << "Is stack full? " << (s.isFull() ? "Yes" : "No") << endl;

    return 0;
}