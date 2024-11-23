// Scheduler Header File

// The Scheduler class manages the task scheduling operations and provides methods to add, delete, modify, execute,
// and display tasks, as well as to display the task scheduler menu and run the scheduler.

// It uses a private min-heap priority queue to store tasks, a History object to log task operations, and a static
// variable to generate unique task IDs. It also uses private static methods to input task details and display task
// details. The priority queue is sorted based on the Task class's comparison operators, which compare tasks based on
// their priority and deadline.

// The inputTask function prompts the user to enter task details and returns a new Task object.
// The addTask function adds a task to the priority queue and logs it in the history.
// The deleteTask function removes a task from the priority queue and the history based on the task ID.
// The modifyTask function allows the user to modify an existing task's details.
// The executeTask function executes the next task in the priority queue and logs it as completed in the history.
// The displayOngoingTasks function displays all tasks currently in the priority queue.
// The displayMenu function displays the task scheduler menu options.
// The run function runs the task scheduler, allowing the user to interact with the menu and perform various operations.

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

    // The search function uses an optional return type to indicate that the task may or may not be found
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