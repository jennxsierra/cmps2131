// Jennessa Sierra
// CMPS2131-1
// 13/10/2024

#include <iostream>
#include <string>
#include <limits> // For std::numeric_limits
#include <cctype> // For std::isdigit
#include <algorithm> // For std::any_of

// Implementation of a priority queue data structure using a singly linked list
// Assumptions:
// 1. The priority queue is a singly linked list with a front and rear pointer using the FIFO (First-In-First-Out) principle
// 2. Each node in the queue represents an order with a customer name, items, quantities, and priority
// 3. Express orders always have the highest priority.
// 4. Regular orders have increasing priority, but are processed after express orders.

// Represents a customer's order in the queue
class Order {
public:
    std::string customerName; // Name of the customer
    std::string* items; // Array of items in the order
    int* quantities; // Array of quantities for each item
    int itemCount; // Number of items in the order
    int priority; // Priority of the order (1 for express, 2+ for regular)
    Order* next; // Pointer to the next order in the queue

    // Constructor to initialize the order
    // Using new and delete operators for dynamic memory allocation
    // https://www.geeksforgeeks.org/new-and-delete-operators-in-cpp-for-dynamic-memory/
    // https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/
    Order(const std::string& name, int itemCount, int priority)
        : customerName(name), itemCount(itemCount), priority(priority), next(nullptr) {
        items = new std::string[itemCount];
        quantities = new int[itemCount];
    }

    // Destructor to clean up memory
    // https://www.learncpp.com/cpp-tutorial/destructors/
    ~Order() {
        delete[] items;
        delete[] quantities;
    }
};

// Represents a queue of orders in the diner using a singly linked list
class OrderQueue {
private:
    Order* front; // Node at the front of the queue
    Order* rear; // Node at the rear of the queue
    int count; // Number of orders in the queue

public:
    // Constructor to initialize an empty queue
    OrderQueue() : front(nullptr), rear(nullptr), count(0) {}

    // Destructor to clean up all orders in the queue
    ~OrderQueue() {
        while (front != nullptr) {
            Order* temp = front;
            front = front->next;
            delete temp;
        }
    }

    // Adds a new order to the end of the queue
    void placeOrder(const std::string& name, std::string* items, const int* quantities, int itemCount) {
        // Regular orders have increasing priority starting from 2
        // This is to ensure that express orders always have the highest priority
        Order* newOrder = new Order(name, itemCount, count + 2);
        for (int i = 0; i < itemCount; ++i) {
            newOrder->items[i] = items[i];
            newOrder->quantities[i] = quantities[i];
        }

        if (!rear) {
            front = rear = newOrder;
        } else {
            rear->next = newOrder;
            rear = newOrder;
        }
        count++;
    }

    // Adds a new express order at the front of the queue
    void placeExpressOrder(const std::string& name, std::string* items, const int* quantities, int itemCount) {
        Order* newOrder = new Order(name, itemCount, 1); // Express orders have the highest priority
        for (int i = 0; i < itemCount; ++i) {
            newOrder->items[i] = items[i];
            newOrder->quantities[i] = quantities[i];
        }

        if (!front) {
            front = rear = newOrder;
        } else {
            newOrder->next = front;
            front = newOrder;
        }
        count++;
    }

    // Processes the order at the front of the queue and removes it
    void processNextOrder() {
        if (!front) {
            std::cout << "\nThere are currently no orders to process.\n";
            return;
        }
        std::cout << "\n-- Next Order --\n";
        std::cout << "    Name: " << front->customerName << "\n";
        for (int i = 0; i < front->itemCount; ++i) {
            std::cout << "    Items: " << front->items[i] << " (quantity: " << front->quantities[i] << ")\n";
        }

        char processOrder;
        std::cout << "\nProcess this Order? (y/n): ";
        std::cin >> processOrder;
        std::cin.ignore(); // Ignore newline character

        if (processOrder == 'y' || processOrder == 'Y') {
            Order* temp = front;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            delete temp;
            count--;
            std::cout << "Order has been processed!\n";
        } else {
            std::cout << "Order has not been processed.\n";
        }
    }

    // Displays all orders in the queue with their details
    void displayPendingOrders() const {
        if (!front) {
            std::cout << "\nThere are currently no pending orders.\n";
            return;
        }
        Order* current = front;
        int orderNumber = 1;
        while (current) {
            std::cout << "\n" << (current->priority == 1 ? "[Express] Order " : "Order ") << orderNumber++ << ":\n";
            std::cout << "-------------------\n";
            std::cout << "    Name: " << current->customerName << "\n";
            for (int i = 0; i < current->itemCount; ++i) {
                std::cout << "    Item " << orderNumber - 1 << "." << (i + 1) << ": " << current->items[i] <<
                " (quantity: " << current->quantities[i] << ")\n";
            }
            current = current->next;
        }
    }

    // Displays the number of orders in the queue
    void displayPendingOrdersCount() const {
        if (count == 1) {
            std::cout << "\nThere is " << count << " pending order in the system.\n";
        } else {
            std::cout << "\nThere are " << count << " pending orders in the system.\n";
        }
    }
};

// Represents a management system for a restaurant that handles orders
class MgmtSystem {
private:
    OrderQueue queue;
    std::string establishmentName;

    // Displays the menu options for the user
    static void displayMenu() {
        std::cout << "\n-- Menu Options --\n";
        std::cout << "1) Place Order\n";
        std::cout << "2) Place Express Order\n";
        std::cout << "3) Process Next Order\n";
        std::cout << "4) Pending Orders\n";
        std::cout << "5) Pending Orders Count\n";
        std::cout << "6) Stop Program\n";
        std::cout << "\nEnter option number (1-6): ";
    }


    // Function to check if a string contains any digits
    // https://stackoverflow.com/a/62360438
    static bool containsDigit(const std::string& str) {
        return std::any_of(str.begin(), str.end(), ::isdigit);
    }

    // Handles placing an order
    void handlePlaceOrder(bool isExpress) {
        std::string name;
        std::cout << "\nEnter customer name: ";
        std::getline(std::cin, name);
        while (containsDigit(name)) {
            std::cout << "Invalid input. Customer name should not contain numbers.\n";
            std::cout << "\nEnter customer name: ";
            std::getline(std::cin, name);
        }

        int itemCount;
        std::cout << "Enter number of items: ";
        while (!(std::cin >> itemCount) || itemCount <= 0) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input.\n"
                         "\nPlease enter a positive number: ";
        }
        std::cin.ignore(); // Ignore newline character

        std::string* items = new std::string[itemCount];
        int* quantities = new int[itemCount];

        for (int i = 0; i < itemCount; ++i) {
            std::cout << "\nEnter item name: ";
            std::getline(std::cin, items[i]);
            while (containsDigit(items[i])) {
                std::cout << "Invalid input. Item name should not contain numbers.\n";
                std::cout << "\nEnter item name: ";
                std::getline(std::cin, items[i]);
            }
            std::cout << "Enter quantity of " << items[i] << ": ";
            while (!(std::cin >> quantities[i]) || quantities[i] <= 0) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "Invalid input.\n"
                             "\nPlease enter a positive number: ";
            }
            std::cin.ignore(); // Ignore newline character
        }

        if (isExpress) {
            queue.placeExpressOrder(name, items, quantities, itemCount);
        } else {
            queue.placeOrder(name, items, quantities, itemCount);
        }
        std::cout << "\nOrder has been added to system!\n";

        // Clean up memory
        delete[] items;
        delete[] quantities;
    }

public:
    // Constructor to initialize the system with the establishment name
    explicit MgmtSystem(const std::string& name) : establishmentName(name) {}

    // Main driver program for the food order management system
    void driverProgram() {
        int option;

        std::cout << "\n-- Welcome to the " << establishmentName << " Management System! --\n";

        do {
            displayMenu();
            while (!(std::cin >> option) || option < 1 || option > 6) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "Invalid input.\n"
                             "\nEnter option number (1-6): ";
            }
            std::cin.ignore(); // Ignore newline character

            switch (option) {
                case 1:
                    handlePlaceOrder(false);
                    break;
                case 2:
                    handlePlaceOrder(true);
                    break;
                case 3:
                    queue.processNextOrder();
                    break;
                case 4:
                    queue.displayPendingOrders();
                    break;
                case 5:
                    queue.displayPendingOrdersCount();
                    break;
                case 6:
                    std::cout << "\nExiting program...\n";
                    std::system("pause");
                    break;
                default:
                    std::cout << "\nInvalid option. Please try again.\n";
                    break;
            }
        } while (option != 6);
    }
};

int main() {
    MgmtSystem restaurant{"McDonald's"};
    restaurant.driverProgram();

    return 0;
}