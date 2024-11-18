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
    static Task inputTaskDetails(const std::string& prompt, bool clearBuffer);

public:
    void addTask(const Task& task);
    void executeTask();
    void displayOngoingTasks() const;
    void modifyTask();
    static void displayMenu() ;
    static Task inputTask() ;
    void run();
};


#endif //CMPS2131_SCHEDULER_H
