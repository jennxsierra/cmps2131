// History Header File

// The History class logs the history of task operations. It maintains a stack of completed tasks and a list of
// all tasks created. It also provides methods to log new, modified, and completed tasks, remove tasks, and display
// the task history log and completed tasks log.

// logNewTask: adds a new task to the history log list.
// removeTask: removes a task from history log list and completed tasks stack based on the task ID.
// logModifiedTask: updates the details of a modified task in the history log list
// logCompletedTask: adds completed task to completed tasks stack and updates its status in the history log list.
// displayTaskHistory: displays the history log list, sorted by their creation time.
// displayCompletedTasks: displays the completed tasks stack, sorted by their completion time.

#ifndef CMPS2131_HISTORY_H
#define CMPS2131_HISTORY_H

#include "Task.h"
#include <iostream>
#include <stack>
#include <list>

class History {
private:
    // The Stack template is used to store completed tasks, with the following template parameters:
    // 1. Task: The type of elements stored in the stack
    // 2. std::deque<Task>: By default, the standard deque container is used to store elements since no specific
    //    container is specified
    // https://cplusplus.com/reference/stack/stack/
    std::stack<Task> completedTasks;

    // The List template is used to store all tasks, with the following template parameters:
    // 1. Task: The type of elements stored in the list
    // 2. std::allocator<Task>: By default, the standard allocator is used to manage memory since no specific
    //    allocator is specified
    // https://cplusplus.com/reference/list/list/
    std::list<Task> allTasks;

public:
    void logNewTask(const Task& task);
    void removeTask(int taskID);
    void logModifiedTask(const Task& task);
    void logCompletedTask(const Task& task);
    void displayTaskHistory() const;
    void displayCompletedTasks() const;
};


#endif //CMPS2131_HISTORY_H