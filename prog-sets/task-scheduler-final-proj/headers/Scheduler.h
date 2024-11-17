#ifndef CMPS2131_SCHEDULER_H
#define CMPS2131_SCHEDULER_H
#include "PQueue.h"
#include "Stack.h"
#include "Task.h"
#include "HistoryLog.h"

class Scheduler {
private:
    PQueue taskQueue;
    Stack completedTasks;
    HistoryLog history;

public:
    void addTask(const Task& task);
    void executeTask();
    void displayHistory();

    static void displayMenu() ;
    static Task inputTask() ;
    void run();
};

#endif //CMPS2131_SCHEDULER_H
