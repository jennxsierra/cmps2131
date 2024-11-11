#ifndef CMPS2131_TASK_H
#define CMPS2131_TASK_H
#include <string>

class Task {
public:
    int priority;
    std::string taskName;
    std::string description;
    int deadline;
    int timeLeft;

    // Constructor to initialize task
    Task(int p, std::string name, std::string desc, int dline, int tLeft);

    // Comparison operator to compare priorities
    bool operator<(const Task& other) const;
};


#endif //CMPS2131_TASK_H
