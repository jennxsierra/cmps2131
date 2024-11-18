#include "headers/Scheduler.h"

Task Scheduler::inputTaskDetails(const std::string& prompt, bool clearBuffer) {
    int priority;
    std::string taskName, description, deadlineStr;
    std::tm tm = {};
    std::regex dateTimeRegex(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})");

    std::cout << "\n--- " << prompt << " ---\n";
    if (clearBuffer) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Task Name: ";
    std::getline(std::cin, taskName);
    std::cout << "Description: ";
    std::getline(std::cin, description);

    while (true) {
        std::cout << "Priority [1 = Highest, 5 = Lowest]: ";
        std::cin >> priority;
        if (std::cin.fail() || priority < 1 || priority > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid priority.\nEnter a number between 1 and 5.\n";
        } else {
            break;
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        std::cout << "Deadline (YYYY-MM-DD HH:MM:SS) [24-hour format]: ";
        std::getline(std::cin, deadlineStr);
        if (!std::regex_match(deadlineStr, dateTimeRegex)) {
            std::cout << "Invalid date/time format. Enter in the format YYYY-MM-DD HH:MM:SS.\n";
        } else {
            std::istringstream ss(deadlineStr);
            ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
            if (ss.fail()) {
                std::cout << "Failed to parse date/time. Please try again.\n";
            } else {
                break;
            }
        }
    }

    auto deadline = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return Task(priority, taskName, description, deadline);
}

void Scheduler::addTask(const Task& task) {
    taskQueue.push(task);
    history.logNewTask(task);
}

void Scheduler::executeTask() {
    if (taskQueue.empty()) {
        throw std::runtime_error("\nNo tasks to execute.");
    }

    Task task = taskQueue.top();
    taskQueue.pop();
    task.setCompletedTime(std::chrono::system_clock::now());
    history.logCompletedTask(task);
}

void Scheduler::displayOngoingTasks() const {
    if (taskQueue.empty()) {
        std::cout << "\nNo tasks in the queue.\n";
        return;
    }

    std::priority_queue<Task, std::vector<Task>, std::greater<>> tempQueue = taskQueue;
    std::cout << "\n--- Tasks in Queue ---\n\n";

    int index = 1;
    while (!tempQueue.empty()) {
        const Task& task = tempQueue.top();
        auto timeLeft = task.getTimeLeft();
        auto days = std::chrono::duration_cast<std::chrono::days>(timeLeft).count();
        auto hours = std::chrono::duration_cast<std::chrono::hours>(timeLeft).count() % 24;
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(timeLeft).count() % 60;

        std::time_t deadlineTime = std::chrono::system_clock::to_time_t(task.getDeadline());
        std::tm* deadlineTm = std::localtime(&deadlineTime);
        char deadlineStr[20];
        std::strftime(deadlineStr, sizeof(deadlineStr), "%Y-%m-%d %H:%M:%S", deadlineTm);

        std::cout << index++ << ". " << task.getName() << " [Priority: " << task.getPriority() << "]\n";
        std::cout << "--------------------------------------\n";
        std::cout << "Description: " << task.getDescription() << "\n";
        std::cout << "Deadline: " << deadlineStr << "\n";
        std::cout << "Time Left: " << days << " days, " << hours << " hours, " << minutes << " minutes\n\n";
        tempQueue.pop();
    }
}

void Scheduler::modifyTask() {
    if (taskQueue.empty()) {
        std::cout << "\nNo tasks to modify.\n";
        return;
    }

    std::string taskName;
    std::cout << "Enter the name of the task to modify: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, taskName);

    std::priority_queue<Task, std::vector<Task>, std::greater<>> tempQueue;
    bool found = false;

    while (!taskQueue.empty()) {
        Task task = taskQueue.top();
        taskQueue.pop();

        if (task.getName() == taskName) {
            found = true;
            Task modifiedTask = inputTaskDetails("Modify Task Details", false);
            task.setName(modifiedTask.getName());
            task.setPriority(modifiedTask.getPriority());
            task.setDescription(modifiedTask.getDescription());
            task.setDeadline(modifiedTask.getDeadline());
        }
        tempQueue.push(task);
    }

    if (found) {
        std::cout << "\nTask modified successfully!\n";
    } else {
        std::cout << "\nTask not found.\n";
    }

    taskQueue = tempQueue;
}

void Scheduler::displayMenu() {
    std::cout << "\n--- Task Scheduler Menu ---\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. Modify Task\n";
    std::cout << "3. Execute Next Task\n";
    std::cout << "4. View Ongoing Tasks\n";
    std::cout << "5. View Completed Tasks\n";
    std::cout << "6. View Task History Log\n";
    std::cout << "7. Exit\n";
    std::cout << "\nEnter your choice: ";
}

Task Scheduler::inputTask() {
    return inputTaskDetails("Enter Task Details", true);
}

void Scheduler::run() {
    int choice;

    do {
        Scheduler::displayMenu();
        while (!(std::cin >> choice) || choice < 1 || choice > 7) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice.\n\nEnter a number between 1 and 7: ";
        }

        switch (choice) {
            case 1: {
                Task task = Scheduler::inputTask();
                this->addTask(task);
                std::cout << "\nTask added successfully!\n";
                break;
            }
            case 2: {
                this->modifyTask();
                break;
            }
            case 3: {
                try {
                    this->executeTask();
                    std::cout << "\nTask executed successfully!\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 4: {
                this->displayOngoingTasks();
                break;
            }
            case 5: {
                history.displayCompletedTasks();
                break;
            }
            case 6: {
                history.displayTaskHistory();
                break;
            }
            case 7: {
                std::cout << "\nExiting the Task Scheduler. Goodbye!\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 7);
}