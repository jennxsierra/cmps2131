// Jennessa Sierra
// CMPS2131-1
// 29/09/2024

#include <iostream>
#include <string>

// Implementation of a queue data structure using a singly linked list
// Assumptions:
// 1. The queue is a singly linked list with a front and rear pointer using the FIFO (First-In-First-Out) principle
// 2. Each node in the queue represents an order with a customer name, items, quantities, and a pointer to the next order
// 3. Orders can be placed at the rear of the queue (regular order) or at the front of the queue (express order)

// Represents a customer's order in the queue
class Order {
public:
    std::string customerName; // Name of the customer
    std::string* items; // Array of items in the order
    int* quantities; // Array of quantities for each item
    int itemCount; // Number of items in the order
    Order* next; // Pointer to the next order in the queue

    // Constructor to initialize the order
    // Using new and delete operators for dynamic memory allocation
    // https://www.geeksforgeeks.org/new-and-delete-operators-in-cpp-for-dynamic-memory/
    // https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/
    Order(const std::string& name, int itemCount)
        : customerName(name), itemCount(itemCount), next(nullptr) {
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

    // Adds a new order at the rear of the queue
    void placeOrder(const std::string& name, std::string* items, const int* quantities, int itemCount) {
        Order* newOrder = new Order(name, itemCount);
        for (int i = 0; i < itemCount; ++i) {
            newOrder->items[i] = items[i];
            newOrder->quantities[i] = quantities[i];
        }
        if (rear) {
            rear->next = newOrder;
        } else {
            front = newOrder;
        }
        rear = newOrder;
        count++;
    }

    // Adds a new order at the front of the queue
    void placeExpressOrder(const std::string& name, std::string* items, const int* quantities, int itemCount) {
        Order* newOrder = new Order(name, itemCount);
        for (int i = 0; i < itemCount; ++i) {
            newOrder->items[i] = items[i];
            newOrder->quantities[i] = quantities[i];
        }
        if (front) {
            newOrder->next = front;
            front = newOrder;
        } else {
            front = rear = newOrder;
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
            std::cout << "\nOrder " << orderNumber++ << ":\n";
            std::cout << "---------------\n";
            std::cout << "    Name: " << current->customerName << "\n";
            for (int i = 0; i < current->itemCount; ++i) {
                std::cout << "    Item " << (i + 1) << ": " << current->items[i] << " (quantity: " << current->quantities[i] << ")\n";
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

// Displays the menu options for the user
void displayMenu() {
    std::cout << "\n-- Menu Options --\n";
    std::cout << "1) Place Order\n";
    std::cout << "2) Place Express Order\n";
    std::cout << "3) Process Next Order\n";
    std::cout << "4) Pending Orders\n";
    std::cout << "5) Pending Orders Count\n";
    std::cout << "6) Stop Program\n";
    std::cout << "\nEnter option number (1-6): ";
}

int main() {
    OrderQueue queue;
    int option;
    std::string establishmentName;

    std::cout << "Enter the name of the establishment: ";
    std::getline(std::cin, establishmentName);

    std::cout << "\n-- Welcome to the " << establishmentName << " Management System! --\n";

    do {
        displayMenu();
        std::cin >> option;
        std::cin.ignore(); // Ignore newline character

        // Logic for each menu option
        if (option == 1 || option == 2) {
            std::string name;
            std::cout << "\nEnter customer name: ";
            std::getline(std::cin, name);

            int itemCount;
            std::cout << "Enter number of items: ";
            std::cin >> itemCount;
            std::cin.ignore(); // Ignore newline character

            std::string* items = new std::string[itemCount];
            int* quantities = new int[itemCount];

            for (int i = 0; i < itemCount; ++i) {
                std::cout << "\nEnter item name: ";
                std::getline(std::cin, items[i]);
                std::cout << "Enter quantity of " << items[i] << ": ";
                std::cin >> quantities[i];
                std::cin.ignore(); // Ignore newline character
            }

            if (option == 1) {
                queue.placeOrder(name, items, quantities, itemCount);
            } else {
                queue.placeExpressOrder(name, items, quantities, itemCount);
            }
            std::cout << "\nOrder has been added to system!\n";

            // Clean up memory
            delete[] items;
            delete[] quantities;
        } else if (option == 3) {
            queue.processNextOrder();
        } else if (option == 4) {
            queue.displayPendingOrders();
        } else if (option == 5) {
            queue.displayPendingOrdersCount();
        } else if (option == 6) {
            std::cout << "\nExiting program...\n";
            std::system("pause");
        } else {
            std::cout << "\nInvalid option. Please try again.\n";
        }
    } while (option != 6);

    return 0;
}