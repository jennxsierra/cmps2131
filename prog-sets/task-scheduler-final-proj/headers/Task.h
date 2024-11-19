#ifndef CMPS2131_TASK_H
#define CMPS2131_TASK_H

#include <iostream>
#include <string>
#include <chrono>

class Task {
private:
    int id;
    int priority;
    std::string name;
    std::string description;
    std::chrono::system_clock::time_point deadline;
    std::chrono::system_clock::time_point completedTime;
    std::string status;


public:
    Task(int taskID, int taskPrio, const std::string& taskName, const std::string& tDesc,
         const std::chrono::system_clock::time_point& taskDLine);

    // Getters
    [[nodiscard]] int getID() const;
    [[nodiscard]] int getPriority() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDescription() const;
    [[nodiscard]] std::chrono::system_clock::time_point getDeadline() const;
    [[nodiscard]] std::chrono::duration<double> getTimeLeft() const;
    [[nodiscard]] std::chrono::system_clock::time_point getCompletedTime() const;
    [[nodiscard]] std::string getStatus() const;

    // Setters
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setPriority(int priority);
    void setDeadline(const std::chrono::system_clock::time_point& deadline);
    void setCompletedTime(const std::chrono::system_clock::time_point& time);
    void setStatus(const std::string& status);

    // Operator overloads for priority comparison
    bool operator>(const Task& other) const;
    bool operator<(const Task& other) const;

};


#endif //CMPS2131_TASK_H
