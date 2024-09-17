#include <iostream>

// Creating a node
class Node {
public:
    int data;
    Node* next;
};

// Function to enqueue (insert) an element at the rear of the queue
void enqueue(Node*& front, Node*& rear, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (rear == nullptr) {  // Queue is empty, new node becomes both front and rear
        front = rear = newNode;
    } else {
        rear->next = newNode;  // Link the current rear to the new node
        rear = newNode;        // Update the rear to the new node
    }
    std::cout << "Enqueued " << value << " to the queue." << std::endl;
}

// Function to dequeue (remove) an element from the front of the queue
void dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) {  // Queue is empty
        std::cout << "Queue is empty, cannot dequeue." << std::endl;
        return;
    }

    Node* temp = front;  // Temporarily store the front node
    front = front->next; // Move the front pointer to the next node

    if (front == nullptr) {  // If the front is now null, the queue is empty, so update rear
        rear = nullptr;
    }

    std::cout << "Dequeued " << temp->data << " from the queue." << std::endl;
    delete temp;  // Delete the dequeued node
}

// Function to return the front element without dequeuing
int frontElement(Node* front) {
    if (front == nullptr) {
        std::cout << "Queue is empty." << std::endl;
        return -1;  // Return an error value if the queue is empty
    }
    return front->data;
}

// Function to check if the queue is empty
bool isEmpty(Node* front) {
    return front == nullptr;
}

// Function to print the contents of the queue
void printQueue(Node* front) {
    if (isEmpty(front)) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }

    Node* current = front;
    std::cout << "Queue contents: ";
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
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
    printQueue(front);

    // Check the front element
    std::cout << "Front element is: " << frontElement(front) << std::endl;

    // Check if queue is empty
    std::cout << "Is queue empty? " << (isEmpty(front) ? "Yes" : "No") << std::endl;

    // Wait for user input
    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return 0;
}
