// Task Header File

// The Task Class represents a Task object in the task scheduler application. Each task has an ID, priority, name,
// status, description, and various timestamps (created, modified, completed). The class provides methods to access
// and modify these attributes, as well as operator overloads for priority comparison.

// The Task constructor initializes a task with the given ID, priority, name, description, and deadline. It also sets
// the created time to the current time and initializes the modified time to a minimum value.

// The getID function returns the task's ID.
// The getPriority function returns the task's priority.
// The getName function returns the task's name.
// The getStatus function returns the task's status.
// The getDescription function returns the task's description.
// The getDeadline function returns the task's deadline.
// The getTimeLeft function returns the time left until the task's deadline.
// The getCreatedTime function returns the task's creation time.
// The getModifiedTime function returns the task's last modified time.
// The getCompletedTime function returns the task's completion time.

// The setName function sets the task's name.
// The setStatus function sets the task's status.
// The setDescription function sets the task's description.
// The setPriority function sets the task's priority, ensuring it is between 1 and 5.
// The setDeadline function sets the task's deadline.
// The setModifiedTime function sets the task's last modified time.
// The setCompletedTime function sets the task's completion time.

// The operator> and operator< overloads compare tasks based on their priority and deadline.

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
    std::string status;
    std::string description;
    std::chrono::system_clock::time_point deadline;
    std::chrono::system_clock::time_point createdTime;
    std::chrono::system_clock::time_point modifiedTime;
    std::chrono::system_clock::time_point completedTime;


public:
    Task(int taskID, int taskPrio, const std::string& taskName, const std::string& tDesc,
         const std::chrono::system_clock::time_point& taskDLine);

    // Getters
    [[nodiscard]] int getID() const;
    [[nodiscard]] int getPriority() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getStatus() const;
    [[nodiscard]] std::string getDescription() const;
    [[nodiscard]] std::chrono::system_clock::time_point getDeadline() const;
    [[nodiscard]] std::chrono::duration<double> getTimeLeft() const;
    [[nodiscard]] std::chrono::system_clock::time_point getCreatedTime() const;
    [[nodiscard]] std::chrono::system_clock::time_point getModifiedTime() const;
    [[nodiscard]] std::chrono::system_clock::time_point getCompletedTime() const;

    // Setters
    void setName(const std::string& name);
    void setStatus(const std::string& status);
    void setDescription(const std::string& description);
    void setPriority(int priority);
    void setDeadline(const std::chrono::system_clock::time_point& deadline);
    void setModifiedTime(const std::chrono::system_clock::time_point& time);
    void setCompletedTime(const std::chrono::system_clock::time_point& time);

    // Operator overloads for priority comparison
    bool operator>(const Task& other) const;
    bool operator<(const Task& other) const;

};


#endif //CMPS2131_TASK_H
