#ifndef CMPS2131_HISTORY_H
#define CMPS2131_HISTORY_H

#include "Task.h"
#include <stack>
#include <iostream>

class History {
private:
    std::stack<Task> completedTasks;

public:
    void logCompletedTask(const Task& task);
    void displayHistory() const;
};


#endif //CMPS2131_HISTORY_H
