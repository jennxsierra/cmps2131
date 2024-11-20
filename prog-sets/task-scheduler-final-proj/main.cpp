// Final Project: Task Scheduler Program
// Name: Jennessa Sierra
// Class: Data Structures [CMPS2131-1]
// Semester: 2024-1
// Completion Date: 11/22/2024
// Description: A task scheduler that allows users to add, delete, modify, execute, and view tasks and their history.
//              It comprises three classes: Task, History, and Scheduler. Each class has specific attributes and methods
//              to manage tasks and their history that are detailed in their respective header and source files.
//              In brief, the data structures implemented are: a priority queue to store tasks based on their priority
//              and deadline, a stack to store all completed tasks, and a list to store a history of all tasks.

#include <iostream>
#include "headers/Scheduler.h"

int main() {
    std::cout << "Welcome to the Task Scheduler Program!\n";

    Scheduler scheduler;
    scheduler.run();

    return 0;
}
