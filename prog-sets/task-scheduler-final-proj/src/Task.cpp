#include "headers/Task.h"

Task::Task(int taskID, int taskPrio, const std::string& taskName, const std::string& tDesc,
           const std::chrono::system_clock::time_point& taskDLine)
    : id(taskID), priority(taskPrio), name(taskName), description(tDesc), deadline(taskDLine), status("Ongoing") {
    if (priority < 1 || priority > 5) {
        throw std::invalid_argument("Priority must be between 1 and 5.");
    }
}

int Task::getID() const {
    return id;
}

int Task::getPriority() const {
    return priority;
}

std::string Task::getName() const {
    return name;
}

std::string Task::getDescription() const {
    return description;
}

std::chrono::system_clock::time_point Task::getDeadline() const {
    return deadline;
}

std::chrono::duration<double> Task::getTimeLeft() const {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double>>(deadline - now);
}

std::chrono::system_clock::time_point Task::getCompletedTime() const {
    return completedTime;
}

std::string Task::getStatus() const {
    return status;
}

void Task::setName(const std::string& taskName) {
    this->name = taskName;
}

void Task::setDescription(const std::string& taskDesc) {
    this->description = taskDesc;
}

void Task::setPriority(int taskPrio) {
    if (taskPrio < 1 || taskPrio > 5) {
        throw std::invalid_argument("Priority must be between 1 and 5.");
    }
    this->priority = taskPrio;
}

void Task::setDeadline(const std::chrono::system_clock::time_point& taskDLine) {
    this->deadline = taskDLine;
}

void Task::setCompletedTime(const std::chrono::system_clock::time_point& time) {
    completedTime = time;
}

void Task::setStatus(const std::string& taskStatus) {
    this->status = taskStatus;
}

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