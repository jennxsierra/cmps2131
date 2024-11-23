// Scheduler Header File

// The Scheduler class manages the task scheduling operations and provides methods to add, delete, modify, execute,
// and display tasks, as well as to display the task scheduler menu and run the scheduler.

// It uses a private min-heap priority queue to store tasks, a History object to log task operations, and a static
// variable to generate unique task IDs. The priority queue is sorted based on the Task class's comparison operators,
// which compare tasks based on their priority and deadline.

// inputTaskDetails: prompts the user for task details and returns a Task object with the given ID.
// displayTaskDetails: displays the details of a task.
// searchTask: searches for a task in the priority queue based on the task ID.
// addTask: adds a task to the priority queue and logs it in the history.
// deleteTask: removes a task from the priority queue and the history based on the task ID.
// modifyTask: allows the user to modify an existing task's details.
// completeTask: executes a task and logs it in the history as completed.
// displayOngoingTasks: displays all tasks currently in the priority queue.
// displayMenu: displays the task scheduler menu options.
// run: executes the task scheduler menu and its operations.

#ifndef CMPS2131_SCHEDULER_H
#define CMPS2131_SCHEDULER_H

#include "Task.h"
#include "headers/History.h"
#include <iostream>
#include <queue>
#include <vector>
#include <optional>
#include <limits>
#include <iomanip>
#include <sstream>
#include <regex>

class Scheduler {
private:
    // The priority queue template is used and its template parameters are:
    // 1. Task: The type of elements stored in the queue
    // 2. std::vector<Task>: The underlying container used to store the elements
    // 3. std::greater<>: The comparison function object that defines the order of the elements,
    //    which uses the operator overloads in the Task class to compare tasks
    // https://cplusplus.com/reference/queue/priority_queue/
    std::priority_queue<Task, std::vector<Task>, std::greater<>> taskQueue;
    History history;
    static int nextTaskID;
    static Task inputTaskDetails(const std::string& prompt, int id);
    static void displayTaskDetails(const Task& task, int index);

    // Uses an optional return type to indicate that the task may or may not be found
    // https://builtin.com/articles/stdoptional
    std::optional<Task> searchTask();

public:
    static Task inputTask();
    void addTask(const Task& task);
    void deleteTask();
    void modifyTask();
    void completeTask();
    void displayOngoingTasks() const;
    static void displayMenu();
    void run();
};


#endif //CMPS2131_SCHEDULER_H