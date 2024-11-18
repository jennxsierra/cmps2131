#include "headers/Task.h"

Task::Task(int priority, const std::string& name, const std::string& description,
           const std::chrono::system_clock::time_point& deadline)
    : priority(priority), name(name), description(description), deadline(deadline) {
    if (priority < 1 || priority > 5) {
        throw std::invalid_argument("Priority must be between 1 and 5.");
    }
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

void Task::setName(const std::string& name) {
    this->name = name;
}

void Task::setDescription(const std::string& description) {
    this->description = description;
}

void Task::setPriority(int priority) {
    if (priority < 1 || priority > 5) {
        throw std::invalid_argument("Priority must be between 1 and 5.");
    }
    this->priority = priority;
}

void Task::setDeadline(const std::chrono::system_clock::time_point& deadline) {
    this->deadline = deadline;
}

void Task::setCompletedTime(const std::chrono::system_clock::time_point& time) {
    completedTime = time;
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