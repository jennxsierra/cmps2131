#include "../headers/Task.h"

// Constructor definition
Task::Task(int p, std::string name, std::string desc, int dline, int tLeft)
    : priority(p), taskName(name), description(desc), deadline(dline), timeLeft(tLeft) {}

// Comparison operator definition (for priority queue)
bool Task::operator<(const Task& other) const {
    return priority < other.priority;  // Lower value means higher priority (Min Heap)
}