#include "../headers/HistoryLog.h"
#include <iostream>
#include <stdexcept>

HistoryLog::~HistoryLog() {
    HistoryNode* current = head;
    while (current) {
        HistoryNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void HistoryLog::add(const Task& task) {
    HistoryNode* newNode = new HistoryNode(task);
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
}

void HistoryLog::remove(const Task& task) {
    HistoryNode* current = head;
    while (current) {
        if (current->task.priority == task.priority) {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;
            delete current;
            return;
        }
        current = current->next;
    }
}

void HistoryLog::printHistory() const {
    HistoryNode* current = head;
    while (current) {
        std::cout << "Task: " << current->task.taskName
                  << ", Description: " << current->task.description
                  << ", Priority: " << current->task.priority << std::endl;
        current = current->next;
    }
}