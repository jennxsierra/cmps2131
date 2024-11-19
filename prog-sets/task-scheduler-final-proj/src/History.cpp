#include "headers/History.h"

void History::logNewTask(const Task& task) {
    allTasks.push_back(task);
}

void History::logCompletedTask(const Task& task) {
    completedTasks.emplace(task);

    for (auto& t : allTasks) {
        if (t.getID() == task.getID()) {
            t.setCompletedTime(task.getCompletedTime());
            t.setStatus("Completed");
        }
    }
}

void History::displayTaskHistory() const {
    if (allTasks.empty()) {
        std::cout << "\nNo tasks in the history.\n";
        return;
    }

    std::cout << "\n--- All Tasks History ---\n\n";
    int index = 1;
    for (const auto& task : allTasks) {
        std::time_t deadlineTime = std::chrono::system_clock::to_time_t(task.getDeadline());
        char deadlineStr[20];
        std::strftime(deadlineStr, sizeof(deadlineStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&deadlineTime));

        std::cout << index++ << ". " << task.getName() << " [" << task.getStatus() << "]\n";
        std::cout << "Priority: " << task.getPriority() << "\n";
        std::cout << "Description: " << task.getDescription() << "\n";
        std::cout << "Deadline: " << deadlineStr << "\n";

        if (task.getCompletedTime().time_since_epoch().count() != 0) {
            std::time_t completedTime = std::chrono::system_clock::to_time_t(task.getCompletedTime());
            char completedStr[20];
            std::strftime(completedStr, sizeof(completedStr), "%Y-%m-%d %H:%M:%S",
                          std::localtime(&completedTime));
            std::cout << "Completed At: " << completedStr << "\n";
        }

        std::cout << "--------------------------------------\n";
    }
}

void History::displayCompletedTasks() const {
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
        std::time_t completedTime = std::chrono::system_clock::to_time_t(task.getCompletedTime());
        char deadlineStr[20], completedStr[20];
        std::strftime(deadlineStr, sizeof(deadlineStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&deadlineTime));
        std::strftime(completedStr, sizeof(completedStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&completedTime));

        std::cout << index++ << ". " << task.getName() << " [" << task.getStatus() << "]\n";
        std::cout << "Priority: " << task.getPriority() << "\n";
        std::cout << "Deadline: " << deadlineStr << "\n";
        std::cout << "Completed At: " << completedStr << "\n\n";

        tempStack.pop();
    }
}
