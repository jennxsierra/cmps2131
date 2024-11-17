#include "../headers/Scheduler.h"
#include <iostream>
#include <limits>

void Scheduler::addTask(const Task& task) {
    taskQueue.push(task);
}

void Scheduler::executeTask() {
    if (!taskQueue.isEmpty()) {
        Task task = taskQueue.pop();
        completedTasks.push(task);
        history.add(task);
    }
}

void Scheduler::displayHistory() {
    history.printHistory();
}

void Scheduler::displayMenu() {
    std::cout << "\n--- Task Scheduler Menu ---\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. Execute Next Task\n";
    std::cout << "3. View Completed Tasks History\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

Task Scheduler::inputTask() {
    int priority, deadline, timeLeft;
    std::string taskName, description;

    std::cout << "\nEnter task details:\n";
    std::cout << "Task Name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::getline(std::cin, taskName);
    std::cout << "Description: ";
    std::getline(std::cin, description);
    std::cout << "Priority (lower number = higher priority): ";
    std::cin >> priority;
    std::cout << "Deadline (in time units): ";
    std::cin >> deadline;
    std::cout << "Time Left (in time units): ";
    std::cin >> timeLeft;

    return Task(priority, taskName, description, deadline, timeLeft);
}

void Scheduler::run() {
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Task task = inputTask();
                addTask(task);
                std::cout << "Task added successfully!\n";
                break;
            }
            case 2: {
                try {
                    executeTask();
                    std::cout << "Task executed successfully!\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 3: {
                std::cout << "\n--- Completed Tasks History ---\n";
                displayHistory();
                break;
            }
            case 4: {
                std::cout << "Exiting the Task Scheduler. Goodbye!\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 4);
}