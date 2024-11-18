#include "headers/History.h"

void History::logCompletedTask(const Task& task) {
    completedTasks.push(task);
}

void History::displayHistory() const {
    if (completedTasks.empty()) {
        std::cout << "\nNo completed tasks yet.\n";
        return;
    }

    std::stack<Task> tempStack = completedTasks;
    std::cout << "\n--- Completed Tasks History ---\n\n";

    int index = 1;
    while (!tempStack.empty()) {
        const Task& task = tempStack.top();

        std::time_t deadlineTime = std::chrono::system_clock::to_time_t(task.getDeadline());
        std::tm* deadlineTm = std::localtime(&deadlineTime);
        char deadlineStr[20];
        std::strftime(deadlineStr, sizeof(deadlineStr), "%Y-%m-%d %H:%M:%S", deadlineTm);

        std::time_t completedTime = std::chrono::system_clock::to_time_t(task.getCompletedTime());
        std::tm* completedTm = std::localtime(&completedTime);
        char completedStr[20];
        std::strftime(completedStr, sizeof(completedStr), "%Y-%m-%d %H:%M:%S", completedTm);

        std::cout << index++ << ". " << task.getName() << " - [Completed]\n";
        std::cout << "--------------------------------------\n";
        std::cout << "Priority: " << task.getPriority() << "\n";
        std::cout << "Description: " << task.getDescription() << "\n";
        std::cout << "Deadline: " << deadlineStr << "\n";
        std::cout << "Completed At: " << completedStr << "\n\n";
        tempStack.pop();
    }
}
