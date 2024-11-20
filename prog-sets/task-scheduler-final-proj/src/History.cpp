// History Class Implementation

#include "headers/History.h"

// Adds a new task to the list of all tasks at the end of the list
// https://cplusplus.com/reference/list/list/push_back/
void History::logNewTask(const Task& task) {
    allTasks.push_back(task);
}

// Removes a task with the specified ID from both the list of all tasks (allTasks)
// and the stack of completed tasks (completedTasks)
// 1. In allTasks: Uses std::remove_if to find and erase the task with the matching ID
// 2. In completedTasks: Iterates through the stack, skipping the task with the matching ID,
//    and reconstructs the stack without that task
// https://cplusplus.com/reference/algorithm/remove_if/
// https://cplusplus.com/reference/list/list/erase/
void History::removeTask(int taskID) {
    allTasks.erase(std::remove_if(allTasks.begin(), allTasks.end(),
        [taskID](const Task& task) { return task.getID() == taskID; }), allTasks.end());

    std::stack<Task> tempStack;
    while (!completedTasks.empty()) {
        Task task = completedTasks.top();
        completedTasks.pop();
        if (task.getID() != taskID) {
            tempStack.push(task);
        }
    }
    completedTasks = tempStack;
}

// Updates the details of a modified task in the list of all tasks by iterating
// using `auto&`, which allows accessing each task by reference without specifying
// the type explicitly (useful for cleaner and type-safe code)
// https://cplusplus.com/forum/beginner/271440/
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

// Adds a completed task to the completedTasks stack using emplace(), which constructs
// the Task object directly in place, avoiding unnecessary copies for better performance
// https://cplusplus.com/reference/stack/stack/emplace/
void History::logCompletedTask(const Task& task) {
    completedTasks.emplace(task);

    for (auto& t : allTasks) {
        if (t.getID() == task.getID()) {
            t.setCompletedTime(task.getCompletedTime());
            t.setStatus("Completed");
        }
    }
}

// Displays the history of all tasks sorted by their creation time
void History::displayTaskHistory() const {
    if (allTasks.empty()) { // Check if the task history is empty
        std::cout << "\nNo tasks in the history.\n";
        return;
    }

    // Copy all tasks to a vector and sort them by creation time
    std::vector<Task> sortedTasks(allTasks.begin(), allTasks.end());
    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task& a, const Task& b) {
        return a.getCreatedTime() < b.getCreatedTime(); // Sort in ascending order
    });

    std::cout << "\n\t--- All Tasks History ---\n";
    int index = 1; // Counter for numbering the tasks

    for (const auto& task : sortedTasks) {
        // Convert chrono time points to std::time_t for formatting since
        // std::strftime requires a time_t type
        // https://cplusplus.com/reference/chrono/system_clock/to_time_t/
        std::time_t deadlineTime = std::chrono::system_clock::to_time_t(task.getDeadline());
        std::time_t createdTime = std::chrono::system_clock::to_time_t(task.getCreatedTime());
        std::time_t modifiedTime = std::chrono::system_clock::to_time_t(task.getModifiedTime());

        // Format time as "YYYY-MM-DD HH:MM:SS" string using std::strftime
        // which takes a char array, its size, and a tm struct as arguments
        // std::localtime converts a time_t type to a tm struct
        // https://cplusplus.com/reference/ctime/strftime/
        // https://cplusplus.com/reference/ctime/tm/
        char deadlineStr[20], createdStr[20], modifiedStr[20];
        std::strftime(deadlineStr, sizeof(deadlineStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&deadlineTime)); // Format deadline time
        std::strftime(createdStr, sizeof(createdStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&createdTime)); // Format creation time
        std::strftime(modifiedStr, sizeof(modifiedStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&modifiedTime)); // Format modification time

        // Print task details with a numbered index
        std::cout << "\n" << index++ << ". " << task.getName() << " [" << task.getStatus() << "]\n";
        std::cout << "--------------------------------------\n";
        std::cout << "Task ID: #00" << task.getID() << "\n";
        std::cout << "Priority: " << task.getPriority() << "\n";
        std::cout << "Description: " << task.getDescription() << "\n";
        std::cout << "Deadline: " << deadlineStr << "\n";
        std::cout << "Created At: " << createdStr << "\n";

        // Check if the task has been modified before printing its modified time
        if (task.getModifiedTime() != std::chrono::system_clock::time_point::min()) {
            std::cout << "Modified At: " << modifiedStr << "\n";
        }

        // Check if the task is completed by examining the duration since epoch,
        // which is 0 for default-constructed time points if the task is ongoing
        // https://cplusplus.com/reference/chrono/time_point/time_since_epoch/
        if (task.getCompletedTime().time_since_epoch().count() != 0) {
            std::time_t completedTime = std::chrono::system_clock::to_time_t(task.getCompletedTime());
            char completedStr[20];
            std::strftime(completedStr, sizeof(completedStr), "%Y-%m-%d %H:%M:%S",
                          std::localtime(&completedTime)); // Format completion time
            std::cout << "Completed At: " << completedStr << "\n";
        }
    }
}

// Displays the history of completed tasks sorted by their completion time
void History::displayCompletedTasks() const {
    // Check if there are no completed tasks and inform the user
    if (completedTasks.empty()) {
        std::cout << "\nNo completed tasks yet.\n";
        return;
    }

    std::vector<Task> sortedTasks; // Vector to store completed tasks for sorting
    std::stack<Task> tempStack = completedTasks; // Create a copy of the stack to avoid modifying the original

    // Transfer tasks from the stack to the vector
    while (!tempStack.empty()) {
        sortedTasks.push_back(tempStack.top()); // Add the top task of the stack to the vector
        tempStack.pop(); // Remove the top task from the temporary stack
    }

    // Sort the completed tasks in descending order of their completion time
    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const Task& a, const Task& b) {
        return a.getCompletedTime() > b.getCompletedTime(); // More recently completed tasks appear first
    });

    std::cout << "\n\t--- Completed Tasks History ---\n\n";
    int index = 1; // Counter for numbering the tasks

    // Iterate through the sorted tasks and display their details
    for (const auto& task : sortedTasks) {
        // Convert deadline and completion time points to std::time_t for formatting
        std::time_t deadlineTime = std::chrono::system_clock::to_time_t(task.getDeadline());
        std::time_t completedTime = std::chrono::system_clock::to_time_t(task.getCompletedTime());

        // Format time points into readable strings using "YYYY-MM-DD HH:MM:SS"
        char deadlineStr[20], completedStr[20];
        std::strftime(deadlineStr, sizeof(deadlineStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&deadlineTime));
        std::strftime(completedStr, sizeof(completedStr), "%Y-%m-%d %H:%M:%S",
                      std::localtime(&completedTime));

        // Display task details
        std::cout << index++ << ". " << task.getName() << " [" << task.getStatus() << "]\n";
        std::cout << "--------------------------------------\n";
        std::cout << "Task ID: #00" << task.getID() << "\n";
        std::cout << "Priority: " << task.getPriority() << "\n";
        std::cout << "Deadline: " << deadlineStr << "\n";
        std::cout << "Completed At: " << completedStr << "\n\n";
    }
}
