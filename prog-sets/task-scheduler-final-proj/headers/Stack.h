#ifndef CMPS2131_STACK_H
#define CMPS2131_STACK_H
#include "Task.h"

class StackNode {
public:
    Task task;
    StackNode* next;
    StackNode(Task t) : task(t), next(nullptr) {}
};

class Stack {
private:
    StackNode* top;

public:
    Stack() : top(nullptr) {}
    ~Stack();
    void push(const Task& task);
    Task pop();
    Task peek() const;
    bool isEmpty() const { return top == nullptr; }
};

#endif //CMPS2131_STACK_H
