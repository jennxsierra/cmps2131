#include <iostream>

class Node {
public:
    int data{};
    int priority{0}; // Default to lowest priority
};

class ArrPriorityQueue {
public:
    void Enqueue(int value, int priority = 0) {
        // Check if the queue is full
        if (toLast >= MAX_SIZE) {
            std::cout << "Queue is full.\n";
            return;
        }

        // Check if the priority provided is valid
        if (priority < 0) {
            std::cout << "Invalid priority.\n";
            return;
        }

        // Create a new node
        Node* newPtr = new Node();
        newPtr->data = value;
        newPtr->priority = priority;

        // Insert at end if the queue is empty or if priority is 0
        if (toLast == -1 || priority == 0) {
            pQueue[++toLast] = newPtr;
            return;
        }

        // Find correct position for the new node based on priority
        int indexToInsert = 0;
        while (indexToInsert <= toLast && priority <= pQueue[indexToInsert]->priority) {
            ++indexToInsert;
        }

        // Shift all nodes to create space for the new node
        for (int i = toLast + 1; i > indexToInsert; --i) {
            pQueue[i] = pQueue[i - 1];
        }

        pQueue[indexToInsert] = newPtr;
        ++toLast;
    }

    // Remove the first node since it has the highest priority
    void Dequeue() {
        // Check if the queue is empty
        if (toLast == -1) {
            std::cout << "Queue is empty.\n";
            return;
        }

        delete pQueue[0]; // Delete the first node
        --toLast;

        // Shift all elements to the left
        for (int i = 0; i <= toLast; ++i) {
            pQueue[i] = pQueue[i + 1];
        }

        pQueue[toLast + 1] = nullptr; // Clear the last element
    }

    void printQueue() {
        std::cout << "Array Priority Queue: ";
        for (int i = 0; i <= toLast; ++i) {
            std::cout << pQueue[i]->data << "(" << pQueue[i]->priority << ") ";
        }
        std::cout << '\n';
    }

private:
    static constexpr int MAX_SIZE{100};
    Node* pQueue[MAX_SIZE] = {nullptr};
    int toLast{-1}; // Keeps track of the queue's length
};

int main() {
    ArrPriorityQueue test{};

    test.Enqueue(5, 0);
    test.Enqueue(6, 0);
    test.Enqueue(7, 1);
    test.Enqueue(8, 1);
    test.Enqueue(9, 2);
    test.Enqueue(10, 1);

    test.printQueue();

    test.Dequeue();
    test.Dequeue();
    test.Dequeue();
    test.Dequeue();

    test.printQueue();

    return 0;
}
