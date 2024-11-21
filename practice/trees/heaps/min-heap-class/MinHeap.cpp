#include "MinHeap.h"

void MinHeap::printHeap() const {
    std::cout << "Heap: ";
    for (int i = 0; i < heapArr.size(); i++) {
        std::cout << "[" << i << "]" << heapArr[i] << " ";
    }
    std::cout << std::endl;
}

int MinHeap::leftChild(int i) {
    return 2 * i + 1;
}

int MinHeap::rightChild(int i) {
    return 2 * i + 2;
}

int MinHeap::parent(int i) {
    return (i - 1) / 2;
}

void MinHeap::insert(int key) {
    std::cout << "Inserting: " << key << std::endl;

    heapArr.push_back(key);
    reheapUp(static_cast<int>(heapArr.size() - 1));
}

void MinHeap::deleteMin() {
    if (heapArr.empty()) {
        std::cout << "Heap is empty" << std::endl;
        return;
    }

    std::cout << "Deleting: " << heapArr[0] << std::endl;

    heapArr[0] = heapArr.back();
    heapArr.pop_back();
    reheapDown(0, static_cast<int>(heapArr.size() - 1));
}

void MinHeap::reheapUp(int i) {
    int parentIndex = parent(i);

    while (i > 0 && heapArr[i] < heapArr[parentIndex]) {
        std::swap(heapArr[i], heapArr[parentIndex]);
        i = parentIndex;
        parentIndex = parent(i);
    }
}

void MinHeap::reheapDown(int root, int bottom) {
    int minChild;
    int rightChildIndex = rightChild(root);
    int leftChildIndex = leftChild(root);

    if (leftChildIndex <= bottom) {
        if (leftChildIndex == bottom) {
            minChild = leftChildIndex;
        } else {
            if (heapArr[leftChildIndex] >= heapArr[rightChildIndex]) {
                minChild = rightChildIndex;
            } else {
                minChild = leftChildIndex;
            }
        }

        if (heapArr[root] > heapArr[minChild]) {
            std::swap(heapArr[root], heapArr[minChild]);
            reheapDown(minChild, bottom);
        }
    }
}

int MinHeap::search(int key) const {
    for (int i = 0; i < heapArr.size(); i++) {
        if (heapArr[i] == key) {
            return i;
        }
    }

    return -1;
}

void MinHeap::deleteNode(int key) {
    int index = search(key);

    if (index < 0) {
        std::cout << "Key not found" << std::endl;
        return;
    }

    std::cout << "Deleting: " << key << std::endl;

    heapArr[index] = heapArr.back();
    heapArr.pop_back();

    reheapDown(index, static_cast<int>(heapArr.size() - 1));
}
