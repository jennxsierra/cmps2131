#include "headers/History.h"

void History::logNewTask(const Task& task) {
    allTasks.push_back(task);
}

void History::logModifiedTask(const Task& task) {
    for (auto& t : allTasks) {
        if (t.getID() == task.getID()) {
            t.setName(task.getName());
            t.setPriority(task.getPriority());
            t.setDescription(task.getDescription());
            t.setDeadline(task.getDeadline());
            t.setStatus(task.getStatus());
            t.setModifiedTime(std::chrono::system_clock::now());
        }
    }
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

    std::vector<Task> sortedTasks(allTasks.begin(), allTasks.end());
    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task& a, const Task& b) {
        return a.getCreatedTime() < b.getCreatedTime();
    });

    std::cout << "\n\t--- All Tasks History ---\n";
    int index = 1;
    for (const auto& task : sortedTasks) {
        std::time_t deadlineTime = std::chrono::system_clock::to_time_t(task.getDeadline());
        std::time_t createdTime = std::chrono::system_clock::to_time_t(task.getCreatedTime());
        std::time_t modifiedTime = std::chrono::system_clock::to_time_t(task.getModifiedTime());
        char deadlineStr[20], createdStr[20], modifiedStr[20];
        std::strftime(deadlineStr, sizeof(deadlineStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&deadlineTime));
        std::strftime(createdStr, sizeof(createdStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&createdTime));
        std::strftime(modifiedStr, sizeof(modifiedStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&modifiedTime));

        std::cout << "\n" << index++ << ". " << task.getName() << " [" << task.getStatus() << "]\n";
        std::cout << "--------------------------------------\n";
        std::cout << "Task ID: #00" << task.getID() << "\n";
        std::cout << "Priority: " << task.getPriority() << "\n";
        std::cout << "Description: " << task.getDescription() << "\n";
        std::cout << "Deadline: " << deadlineStr << "\n";
        std::cout << "Created At: " << createdStr << "\n";

        if (task.getModifiedTime() != std::chrono::system_clock::time_point::min()) {
            std::cout << "Modified At: " << modifiedStr << "\n";
        }

        if (task.getCompletedTime().time_since_epoch().count() != 0) {
            std::time_t completedTime = std::chrono::system_clock::to_time_t(task.getCompletedTime());
            char completedStr[20];
            std::strftime(completedStr, sizeof(completedStr), "%Y-%m-%d %H:%M:%S",
                          std::localtime(&completedTime));
            std::cout << "Completed At: " << completedStr << "\n";
        }
    }
}

void History::displayCompletedTasks() const {
    if (completedTasks.empty()) {
        std::cout << "\nNo completed tasks yet.\n";
        return;
    }

    std::vector<Task> sortedTasks;
    std::stack<Task> tempStack = completedTasks;
    while (!tempStack.empty()) {
        sortedTasks.push_back(tempStack.top());
        tempStack.pop();
    }

    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task& a, const Task& b) {
        return a.getCompletedTime() > b.getCompletedTime();
    });

    std::cout << "\n\t--- Completed Tasks History ---\n\n";
    int index = 1;
    for (const auto& task : sortedTasks) {
        std::time_t deadlineTime = std::chrono::system_clock::to_time_t(task.getDeadline());
        std::time_t completedTime = std::chrono::system_clock::to_time_t(task.getCompletedTime());
        char deadlineStr[20], completedStr[20];
        std::strftime(deadlineStr, sizeof(deadlineStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&deadlineTime));
        std::strftime(completedStr, sizeof(completedStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&completedTime));

        std::cout << index++ << ". " << task.getName() << " [" << task.getStatus() << "]\n";
        std::cout << "--------------------------------------\n";
        std::cout << "Task ID: #00" << task.getID() << "\n";
        std::cout << "Priority: " << task.getPriority() << "\n";
        std::cout << "Deadline: " << deadlineStr << "\n";
        std::cout << "Completed At: " << completedStr << "\n\n";
    }
}
