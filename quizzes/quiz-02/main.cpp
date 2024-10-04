#include <iostream>

class Node {
public:
    int data;
    Node* next;
};

// Function to check if the queue is empty
bool isEmpty(Node* front) {
    return front == nullptr;
}

// Function to insert a new node at the rear of the queue
void enqueue(Node*& front, Node*& rear, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    std::cout << "Enqueued " << value << " to the queue." << std::endl;
}

// Function to remove a node from the front of the queue
void dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) {
        std::cout << "\nQueue is empty, cannot dequeue." << std::endl;
        return;
    }

    Node* temp = front;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    std::cout << "Dequeued " << temp->data << " from the queue." << std::endl;
    delete temp;
}

// Function to print the contents of the queue
void printQueue(Node* front) {
    if (isEmpty(front)) {
        std::cout << "\nQueue is empty." << std::endl;
        return;
    }

    Node* current = front;
    std::cout << "\nQueue: ";
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n" << std::endl;
}

int main() {
    // Declaration of front and rear pointers
    Node* front = nullptr;
    Node* rear = nullptr;

    // Enqueue elements
    enqueue(front, rear, 10);
    enqueue(front, rear, 20);
    enqueue(front, rear, 30);

    // Print current queue
    printQueue(front);

    // Dequeue an element
    dequeue(front, rear);
    dequeue(front, rear);
    printQueue(front);

    // Check if queue is empty
    std::cout << "Is queue empty? " << (isEmpty(front) ? "Yes\n" : "No\n") << std::endl;

    return 0;
}
