#include "../headers/Scheduler.h"
#include <iostream>

void Scheduler::addTask(const Task& task) {
    taskQueue.push(task);
}

void Scheduler::executeTask() {
    if (!taskQueue.isEmpty()) {
        Task task = taskQueue.pop();
        completedTasks.push(task);
        history.add(task);
    }
}

void Scheduler::displayHistory() {
    history.printHistory();
}