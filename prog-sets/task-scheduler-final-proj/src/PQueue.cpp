#include "../headers/PQueue.h"
#include <stdexcept> // std::out_of_range

void PQueue::heapifyUp() {
    int index = heap.size() - 1;
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap[index] < heap[parentIndex]) {
            std::swap(heap[index], heap[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

void PQueue::heapifyDown() {
    int index = 0;
    int size = heap.size();
    while (2 * index + 1 < size) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < size && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

void PQueue::push(const Task& task) {
    heap.push_back(task);
    heapifyUp();
}

Task PQueue::pop() {
    if (heap.empty()) throw std::out_of_range("Queue is empty.");
    Task root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown();
    return root;
}

Task PQueue::peek() const {
    if (heap.empty()) throw std::out_of_range("Queue is empty.");
    return heap[0];
}