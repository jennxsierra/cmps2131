#ifndef CMPS2131_HISTORY_H
#define CMPS2131_HISTORY_H

#include "Task.h"
#include <iostream>
#include <stack>
#include <list>

class History {
private:
    std::stack<Task> completedTasks;
    std::list<Task> allTasks;

public:
    void logNewTask(const Task& task);
    void logModifiedTask(const Task& task);
    void logCompletedTask(const Task& task);
    void displayTaskHistory() const;
    void displayCompletedTasks() const;
};


#endif //CMPS2131_HISTORY_H
