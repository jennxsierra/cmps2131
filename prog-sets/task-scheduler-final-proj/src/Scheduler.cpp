// Scheduler Class Implementation

#include "headers/Scheduler.h"

// Static variable to generate unique task IDs
int Scheduler::nextTaskID = 1;

// Static method for user input of task details
Task Scheduler::inputTaskDetails(const std::string& prompt, int id) {
    int priority; // Holds the priority of the task (1-5).
    std::string taskName, description, deadlineStr; // Strings for task details.
    std::tm tm = {}; // Struct to store parsed date and time.

    // Create a regular expression to validate the date/time format using std::regex
    // \d{} matches digits, - matches the hyphen, and : matches the colon
    // https://cplusplus.com/reference/regex/
    // https://cplusplus.com/reference/regex/ECMAScript/
    std::regex dateTimeRegex(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})");

    std::cout << "\n--- " << prompt << " ---\n";
    // Ignore any leftover input to ensure clean input reading.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Task Name: ";
    std::getline(std::cin, taskName); // Get the task name from the user.

    std::cout << "Description: ";
    std::getline(std::cin, description); // Get the task description from the user.

    while (true) {
        // Prompt for the task priority, which must be between 1 (highest) and 5 (lowest).
        std::cout << "Priority [1 = Highest, 5 = Lowest]: ";
        std::cin >> priority;

        // Validate the input: it must be an integer between 1 and 5.
        if (std::cin.fail() || priority < 1 || priority > 5) {
            std::cin.clear(); // Clear the error flag.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input.
            std::cout << "Invalid priority.\nEnter a number between 1 and 5.\n";
        } else {
            break; // Input is valid, exit the loop.
        }
    }

    // Clear the input buffer to prepare for reading the deadline string.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        // Prompt for the deadline in the format "YYYY-MM-DD HH:MM:SS".
        std::cout << "Deadline [YYYY-MM-DD HH:MM:SS (24H)]: ";
        std::getline(std::cin, deadlineStr);

        // Validate the input format using the dateTimeRegex regular expression.
        if (!std::regex_match(deadlineStr, dateTimeRegex)) {
            std::cout << "Invalid date/time format. Enter in the format YYYY-MM-DD HH:MM:SS.\n\n";
        } else {
            // Use std::istringstream to create a string stream from the string that
            // can be treated as an input stream for parsing and then use std::get_time
            // to extract the date and time components into the tm struct
            // https://cplusplus.com/reference/sstream/istringstream/istringstream/
            std::istringstream ss(deadlineStr);
            ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

            // Check if parsing was successful using the fail flag of the stringstream
            // https://cplusplus.com/reference/ios/ios/fail/
            if (ss.fail()) {
                std::cout << "Failed to parse date/time. Please try again.\n\n";
            } else {
                break; // Date/time is valid, exit the loop.
            }
        }
    }

    // Convert the tm struct into a time_t value using std::mktime
    // then into a std::chrono::system_clock::time_point for the deadline using from_time_t
    // https://cplusplus.com/reference/chrono/system_clock/from_time_t/
    // https://cplusplus.com/reference/ctime/mktime/
    auto deadline = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    // Create and return a Task object initialized with the provided details.
    return {id, priority, taskName, description, deadline};
}

// Static method to display task details
void Scheduler::displayTaskDetails(const Task& task, int i) {
    auto timeLeft = task.getTimeLeft(); // Get the time left until the deadline

    // Convert the remaining time to days, hours, and minutes using
    // std::chrono::duration_cast and modulo operations to extract the components
    // https://cplusplus.com/reference/chrono/duration_cast/
    auto days = std::chrono::duration_cast<std::chrono::days>(timeLeft).count();
    auto hours = std::chrono::duration_cast<std::chrono::hours>(timeLeft).count() % 24;
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(timeLeft).count() % 60;

    // Convert the chrono time_point to a time_t type
    std::time_t deadlineTime = std::chrono::system_clock::to_time_t(task.getDeadline());
    char deadlineStr[20]; // Array for storing the formatted deadline string

    // Convert time_t to a tm struct representing the local time
    // then format the tm struct as a string using std::strftime
    std::tm* deadlineTm = std::localtime(&deadlineTime);
    std::strftime(deadlineStr, sizeof(deadlineStr), "%Y-%m-%d %H:%M:%S", deadlineTm);

    // Display the task details
    std::cout << i << ". " << task.getName() << " [Priority: " << task.getPriority() << "]\n";
    std::cout << "--------------------------------------\n";
    std::cout << "Task ID: #00" << task.getID() << "\n";
    std::cout << "Description: " << task.getDescription() << "\n";
    std::cout << "Status: " << task.getStatus() << "\n";
    std::cout << "Deadline: " << deadlineStr << "\n";
    std::cout << "Time Left: " << days << " days, " << hours << " hours, " << minutes << " minutes\n\n";
}

// Method to search for a task by ID and return it if found
std::optional<Task> Scheduler::searchTask() {
    std::string input;
    int taskId;
    std::cout << "Enter Task ID [Ex: #000]: ";
    std::cin >> input; // Get the task ID from the user

    // Remove the '#' character if present using substr which
    // returns a substring starting from the specified position
    // https://cplusplus.com/reference/string/string/substr/
    if (input[0] == '#') {
        input = input.substr(1);
    }

    // Use try-catch block and std::stoi to convert the input string to an integer
    // and handle invalid argument exceptions if the input is not a valid integer
    // https://cplusplus.com/reference/stdexcept/invalid_argument/
    // https://cplusplus.com/reference/string/stoi/
    try {
        taskId = std::stoi(input);
    } catch (const std::invalid_argument& e) {
        std::cout << "\nInvalid Task ID format.\n";
        return std::nullopt; // Return an empty optional if the conversion fails
    }

    // Create a temporary priority queue to store tasks
    std::priority_queue<Task, std::vector<Task>, std::greater<>> tempQueue;
    std::optional<Task> foundTask; // Optional Task to store the found task

    // Iterate through the tasks in the queue to find and delete the specified task
    while (!taskQueue.empty()) {
        // Get the top task from the queue
        Task task = taskQueue.top();
        taskQueue.pop();

        // Check if the task ID matches the input ID
        if (task.getID() == taskId) {
            foundTask = task; // Store the found task in the optional
        } else {
            // If the task ID does not match, add it to the temporary queue
            tempQueue.push(task);
        }
    }

    // If the task was not found, restore the tasks from the temporary queue
    if (!foundTask) {
        taskQueue = tempQueue;
    } else { // If the task was found, restore the tasks and add the found task back to the queue
        while (!tempQueue.empty()) {
            taskQueue.push(tempQueue.top());
            tempQueue.pop();
        }
    }

    // Return the found task if it exists, otherwise return an empty optional
    return foundTask;
}

// Calls the inputTaskDetails method to prompt the user for task details and returns the created Task object
Task Scheduler::inputTask() {
    return inputTaskDetails("Enter Task Details", nextTaskID++);
}

// Adds a task to the priority queue using emplace and logs it in the history
void Scheduler::addTask(const Task& task) {
    taskQueue.emplace(task);
    history.logNewTask(task);
}

// Deletes a task from the priority queue and the history based on the task ID
void Scheduler::deleteTask() {
    if (taskQueue.empty()) { // Check if the queue is empty
        std::cout << "\nNo tasks to delete.\n";
        return;
    }

    // Search for the task in the queue
    auto taskOpt = searchTask();
    if (!taskOpt) {
        std::cout << "\nTask not found.\n";
        return;
    }

    // Get the task details and display them to the user
    const Task& task = taskOpt.value();
    std::cout << "\n\t--- Task Details ---\n\n";
    displayTaskDetails(task, 1);

    // Prompt the user for confirmation to delete the task
    char confirmation;
    while (true) {
        std::cout << "Delete this Task? [Y/N]: ";
        std::cin >> confirmation;
        confirmation = tolower(confirmation);
        if (confirmation == 'y' || confirmation == 'n') break;
        std::cout << "Invalid input. Please enter 'Y' or 'N'.\n";
    }

    // If confirmed, remove the task from the history and queue
    if (confirmation == 'y') {
        history.removeTask(task.getID());
        std::cout << "\nTask deleted successfully!\n";
    } else { // If not confirmed, add the task back to the queue
        std::cout << "\nTask deletion canceled.\n";
        taskQueue.push(task);
    }
}

// Modifies an existing task's details using a similar approach to deleting a task
void Scheduler::modifyTask() {
    if (taskQueue.empty()) {
        std::cout << "\nNo tasks to modify.\n";
        return;
    }

    auto taskOpt = searchTask();
    if (!taskOpt) {
        std::cout << "\nTask not found.\n";
        return;
    }

    const Task& task = taskOpt.value();
    std::cout << "\n\t--- Task Details ---\n\n";
    displayTaskDetails(task, 1);

    char confirmation;
    while (true) {
        std::cout << "Modify this Task? [Y/N]: ";
        std::cin >> confirmation;
        confirmation = tolower(confirmation);
        if (confirmation == 'y' || confirmation == 'n') break;
        std::cout << "Invalid input. Please enter 'Y' or 'N'.\n";
    }

    if (confirmation == 'y') {
        // Remove the task and rebuild the queue without the modified task
        std::vector<Task> tasks;
        while (!taskQueue.empty()) {
            if (taskQueue.top().getID() != task.getID()) {
                tasks.push_back(taskQueue.top());
            }
            taskQueue.pop();
        }

        // Create modified task by getting new details from the user
        Task modifiedTask = inputTaskDetails("Modify Task Details", task.getID());
        history.logModifiedTask(modifiedTask);
        tasks.push_back(modifiedTask); // Add the modified task to the queue

        // Rebuild the queue
        for (const auto& t : tasks) {
            taskQueue.push(t);
        }

        std::cout << "\nTask modified successfully!\n";
    } else { // If not confirmed, add the task back to the queue
        std::cout << "\nTask modification canceled.\n";
        taskQueue.push(task);
    }
}

// Executes either the next task in the priority queue or a specific task based on user choice
void Scheduler::completeTask() {
    if (taskQueue.empty()) { // Check if the queue is empty
        std::cout << "\nNo tasks to complete.\n";
        return;
    }

    // Prompt the user to complete the next task or search for a specific task
    char choice;
    while (true) {
        std::cout << "Complete Next Task or Search for Task? [N/S]: ";
        std::cin >> choice;
        choice = tolower(choice);
        if (choice == 'n' || choice == 's') break;
        std::cout << "Invalid choice. Please enter 'N' or 'S'.\n";
    }

    Task task;
    bool found = false;

    if (choice == 's') { // Search for a specific task
        auto taskOpt = searchTask();
        if (taskOpt) {
            task = taskOpt.value();
            found = true;
        }
    } else { // Get the next task in the queue
        task = taskQueue.top();
        found = true;
    }

    if (found) { // If the task is found, display its details and prompt the user for confirmation
        std::cout << "\n\t--- Task to Complete ---\n\n";
        displayTaskDetails(task, 1);

        char confirmation;
        while (true) {
            std::cout << "Complete this Task? [Y/N]: ";
            std::cin >> confirmation;
            confirmation = tolower(confirmation);
            if (confirmation == 'y' || confirmation == 'n') break;
            std::cout << "Invalid input. Please enter 'Y' or 'N'.\n";
        }

        if (confirmation == 'y') {
            // Mark the task as completed and log it in the history
            if (choice != 's') {
                taskQueue.pop(); // Remove from the queue ONLY if it's the next task
            }
            task.setCompletedTime(std::chrono::system_clock::now());
            task.setStatus("Completed");
            history.logCompletedTask(task);
            std::cout << "\nTask completed successfully!\n";
        } else { // If not confirmed, add the task back to the queue
            std::cout << "\nTask completion canceled.\n";
            if (choice == 's') {
                taskQueue.push(task);
            }
        }
    } else { // If the task is not found, inform the user
        std::cout << "\nTask not found.\n";
    }
}

// Displays all ongoing tasks currently in the priority queue
void Scheduler::displayOngoingTasks() const {
    if (taskQueue.empty()) {
        std::cout << "\nNo tasks in the queue.\n";
        return;
    }

    // Create a temporary copy of the priority queue to avoid modifying the original
    std::priority_queue<Task, std::vector<Task>, std::greater<>> tempQueue = taskQueue;
    std::cout << "\n\t--- Tasks in Queue ---\n\n";
    int index = 1; // Counter for numbering the tasks

    // Display the details of each task in the queue while it is not empty
    while (!tempQueue.empty()) {
        const Task& task = tempQueue.top();
        displayTaskDetails(task, index++);
        tempQueue.pop();
    }
}

// Displays the task scheduler menu options
void Scheduler::displayMenu() {
    std::cout << "\n--- Task Scheduler Menu ---\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. Delete Task\n";
    std::cout << "3. Modify Task\n";
    std::cout << "4. Complete Task\n";
    std::cout << "5. View Ongoing Tasks\n";
    std::cout << "6. View Completed Tasks\n";
    std::cout << "7. View Task History Log\n";
    std::cout << "8. Exit\n";
    std::cout << "\nEnter your choice: ";
}

// Runs the task scheduler, using a do-while loop and a switch-case statement,
// allowing the user to interact with the menu and perform various operations
void Scheduler::run() {
    int choice;

    do {
        Scheduler::displayMenu();
        while (!(std::cin >> choice) || choice < 1 || choice > 8) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice.\n\nEnter a number between 1 and 8: ";
        }

        switch (choice) {
            case 1: {
                Task task = Scheduler::inputTask();
                this->addTask(task);
                std::cout << "\nTask added successfully!\n";
                break;
            }
            case 2: {
                this->deleteTask();
                break;
            }
            case 3: {
                this->modifyTask();
                break;
            }
            case 4: {
                this->completeTask();
                break;
            }
            case 5: {
                this->displayOngoingTasks();
                break;
            }
            case 6: {
                history.displayCompletedTasks();
                break;
            }
            case 7: {
                history.displayTaskHistory();
                break;
            }
            case 8: {
                std::cout << "\nExiting Task Scheduler. Goodbye!\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 8);
}