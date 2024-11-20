// Task Class Implementation

#include "headers/Task.h"

// Task Constructor creates a new task with the given ID, priority, name, description, and deadline
// Sets the created time to the current time and the modified time to a minimum value using
// std::chrono::system_clock that provides the current time from the computer's internal clock
// https://cplusplus.com/reference/chrono/
Task::Task(int taskID, int taskPrio, const std::string& taskName, const std::string& tDesc,
           const std::chrono::system_clock::time_point& taskDLine)
    : id(taskID), priority(taskPrio), name(taskName), description(tDesc), deadline(taskDLine), status("Ongoing"),
    createdTime(std::chrono::system_clock::now()), modifiedTime(std::chrono::system_clock::time_point::min()) {
    if (priority < 1 || priority > 5) {
        // Throw an exception if the priority is not between 1-5
        // https://cplusplus.com/reference/stdexcept/invalid_argument/
        throw std::invalid_argument("Priority must be between 1-5.");
    }
}

// Getters for Task Class
int Task::getID() const {
    return id;
}

int Task::getPriority() const {
    return priority;
}

std::string Task::getName() const {
    return name;
}

std::string Task::getStatus() const {
    return status;
}

std::string Task::getDescription() const {
    return description;
}

// Time Functions in the Task class use std::chrono to handle time-related operations
// std::chrono::system_clock::time_point is a type representing a point in time
std::chrono::system_clock::time_point Task::getDeadline() const {
    return deadline;
}

// std::chrono::duration is a type representing a time interval, and the <double> template
// parameter specifies the duration type as double for floating-point seconds
std::chrono::duration<double> Task::getTimeLeft() const {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double>>(deadline - now);
}

std::chrono::system_clock::time_point Task::getCreatedTime() const {
    return createdTime;
}

std::chrono::system_clock::time_point Task::getModifiedTime() const {
    return modifiedTime;
}

std::chrono::system_clock::time_point Task::getCompletedTime() const {
    return completedTime;
}

// Setters for Task Class
void Task::setName(const std::string& taskName) {
    // this-> is a pointer to the current object,
    // and it is used to access the object's attributes
    // https://www.geeksforgeeks.org/this-pointer-in-c/
    this->name = taskName;
}

void Task::setStatus(const std::string& taskStatus) {
    this->status = taskStatus;
}

void Task::setDescription(const std::string& taskDesc) {
    this->description = taskDesc;
}

void Task::setPriority(int taskPrio) {
    if (taskPrio < 1 || taskPrio > 5) { // Check if the priority is within the valid range
        throw std::invalid_argument("Priority must be between 1 and 5.");
    }
    this->priority = taskPrio;
}

void Task::setDeadline(const std::chrono::system_clock::time_point& taskDLine) {
    this->deadline = taskDLine;
}

void Task::setModifiedTime(const std::chrono::system_clock::time_point& time) {
    modifiedTime = time;
}

void Task::setCompletedTime(const std::chrono::system_clock::time_point& time) {
    completedTime = time;
}

// Overloaded Operators for Task Class
// Greater-than and less-than operators are overloaded to compare tasks based on their priority
// and deadline. If the priorities are equal, the tasks are compared based on their deadlines
// https://www.programiz.com/cpp-programming/operator-overloading
bool Task::operator>(const Task& other) const {
    if (priority == other.priority) {
        return deadline > other.deadline;
    }
    return priority > other.priority;
}

bool Task::operator<(const Task& other) const {
    if (priority == other.priority) {
        return deadline < other.deadline;
    }
    return priority < other.priority;
}