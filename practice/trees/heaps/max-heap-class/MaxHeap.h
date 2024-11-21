#include <vector>
#include <iostream>

#ifndef CMPS2131_MAXHEAP_H
#define CMPS2131_MAXHEAP_H

class MaxHeap {
public:
    MaxHeap() = default;
    void printHeap() const;
    static int leftChild(int);
    static int rightChild(int);
    static int parent(int);
    void insert(int);
    void deleteMax();
    void reheapUp(int);
    void reheapDown(int, int);
    [[nodiscard]] int search(int) const;
    void deleteNode(int);

private:
    std::vector<int> heapArr{};
};

#endif //CMPS2131_MAXHEAP_H
