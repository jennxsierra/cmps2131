#ifndef CMPS2131_TASK_H
#define CMPS2131_TASK_H

#include <string>
#include <chrono>
#include <iostream>

class Task {
private:
    int priority;
    std::string name;
    std::string description;
    std::chrono::system_clock::time_point deadline;
    std::chrono::system_clock::time_point completedTime;

public:
    Task(int priority, const std::string& name, const std::string& description,
         const std::chrono::system_clock::time_point& deadline);

    // Getters
    [[nodiscard]] int getPriority() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDescription() const;
    [[nodiscard]] std::chrono::system_clock::time_point getDeadline() const;
    [[nodiscard]] std::chrono::duration<double> getTimeLeft() const;
    [[nodiscard]] std::chrono::system_clock::time_point getCompletedTime() const;

    // Setters
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setPriority(int priority);
    void setDeadline(const std::chrono::system_clock::time_point& deadline);
    void setCompletedTime(const std::chrono::system_clock::time_point& time);

    // Operator overloads for priority comparison
    bool operator>(const Task& other) const;
    bool operator<(const Task& other) const;

};


#endif //CMPS2131_TASK_H
