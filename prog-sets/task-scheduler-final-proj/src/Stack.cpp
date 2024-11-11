#include "../headers/Stack.h"
#include <stdexcept> // std::out_of_range

Stack::~Stack() {
    while (top) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::push(const Task& task) {
    StackNode* newNode = new StackNode(task);
    newNode->next = top;
    top = newNode;
}

Task Stack::pop() {
    if (top == nullptr) throw std::out_of_range("Stack is empty.");
    StackNode* temp = top;
    Task poppedTask = top->task;
    top = top->next;
    delete temp;
    return poppedTask;
}

Task Stack::peek() const {
    if (top == nullptr) throw std::out_of_range("Stack is empty.");
    return top->task;
}