#ifndef CMPS2131_PQUEUE_H
#define CMPS2131_PQUEUE_H
#include "Task.h"
#include <vector>

class PQueue {
private:
    std::vector<Task> heap;
    void heapifyUp();
    void heapifyDown();

public:
    void push(const Task& task);
    Task pop();
    [[nodiscard]] Task peek() const;
    [[nodiscard]] bool isEmpty() const { return heap.empty(); }
};


#endif //CMPS2131_PQUEUE_H
