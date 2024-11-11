#ifndef CMPS2131_HISTORYLOG_H
#define CMPS2131_HISTORYLOG_H
#include "Task.h"

class HistoryNode {
public:
    Task task;
    HistoryNode* next;
    HistoryNode* prev;
    explicit HistoryNode(Task t) : task(t), next(nullptr), prev(nullptr) {}
};

class HistoryLog {
private:
    HistoryNode* head;
    HistoryNode* tail;

public:
    HistoryLog() : head(nullptr), tail(nullptr) {}
    ~HistoryLog();
    void add(const Task& task);
    void remove(const Task& task);
    void printHistory() const;
};

#endif //CMPS2131_HISTORYLOG_H
