#include <iostream>
#include <cmath>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        int value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// Helper Function to convert string to integer
int stringToInt(const string& str) {
    int num = 0;
    for (char c : str) {
        num = num * 10 + (c - '0');
    }

    return num;
}

// Function to evaluate the postfix expression
int evaluateExpression(string postfix[], int size) {
    Stack stack;

    for (int i = 0; i < size; ++i) {
        string token = postfix[i];

        if (isdigit(token[0])) {
            int num = stringToInt(token);
            stack.push(num);
        } else {
            int x = stack.pop();
            int y = stack.pop();

            int result;

            switch (token[0]) {
                case '+':
                    result = y + x;
                    break;
                case '-':
                    result = y - x;
                    break;
                case '*':
                    result = y * x;
                    break;
                case '/':
                    result = y / x;
                    break;
                case '^':
                    result = pow(y, x);
                    break;
                default:
                    cout << "Invalid operator: " << token << endl;
                    return -1;
            }
            stack.push(result);
        }
    }

    return stack.pop();
}

int main() {
    string Postfix[] = {"8", "2", "3", "^", "/", "2", "3", "*", "+", "5", "1", "*", "-"};
    int size = sizeof(Postfix) / sizeof(Postfix[0]);

    int result = evaluateExpression(Postfix, size);
    cout << "The result of the postfix expression is: " << result << endl;

    return 0;
}