#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <stdexcept>

class Task {
public:
    int priority;
    std::string description;

    Task(int p, std::string  desc) : priority(p), description(std::move(desc)) {}
};

class PriorityQueue {
private:
    std::vector<Task> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index].priority > heap[parentIndex].priority) {
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = static_cast<int>(heap.size());
        while (index < size) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < size && heap[leftChild].priority > heap[largest].priority) {
                largest = leftChild;
            }
            if (rightChild < size && heap[rightChild].priority > heap[largest].priority) {
                largest = rightChild;
            }
            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    void insertTask(int priority, const std::string& description) {
        Task newTask(priority, description);
        heap.push_back(newTask);
        heapifyUp(static_cast<int>(heap.size()) - 1);
    }

    std::string getHighestPriorityTask() {
        if (heap.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        std::string highestPriorityTask = heap[0].description;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return highestPriorityTask;
    }
};

int main() {
    PriorityQueue pq;
    pq.insertTask(5, "Complete project report");
    pq.insertTask(2, "Check emails");
    pq.insertTask(10, "Prepare presentation");
    std::cout << "Highest priority task: " << pq.getHighestPriorityTask() << std::endl;

    return 0;
}