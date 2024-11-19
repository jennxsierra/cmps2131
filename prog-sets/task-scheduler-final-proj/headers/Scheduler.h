#ifndef CMPS2131_SCHEDULER_H
#define CMPS2131_SCHEDULER_H

#include "Task.h"
#include "headers/History.h"
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <iomanip>
#include <sstream>
#include <regex>

class Scheduler {
private:
    std::priority_queue<Task, std::vector<Task>, std::greater<>> taskQueue;
    History history;
    static int nextTaskID;
    static Task inputTaskDetails(const std::string& prompt, int id);
    static void displayTaskDetails(const Task& task, int index);

public:
    void addTask(const Task& task);
    void executeTask();
    static Task inputTask();
    void modifyTask();
    void displayOngoingTasks() const;
    static void displayMenu();
    void run();
};

#endif //CMPS2131_SCHEDULER_H