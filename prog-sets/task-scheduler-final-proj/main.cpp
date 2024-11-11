#include <iostream>
#include "headers/Scheduler.h"

int main() {
    Scheduler scheduler;

    // Add tasks
    scheduler.addTask(Task(1, "Task1", "Description of Task1", 10, 5));
    scheduler.addTask(Task(2, "Task2", "Description of Task2", 12, 3));
    scheduler.addTask(Task(3, "Task3", "Description of Task3", 15, 1));

    // Execute tasks
    scheduler.executeTask();
    scheduler.executeTask();

    // Display completed tasks history
    std::cout << "Completed Tasks:" << std::endl;
    scheduler.displayHistory();

    return 0;
}