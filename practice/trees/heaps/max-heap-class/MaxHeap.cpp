#include "MaxHeap.h"

void MaxHeap::printHeap() const {
    std::cout << "Heap: ";
    for (int i = 0; i < heapArr.size(); i++) {
        std::cout << "[" << i << "]" << heapArr[i] << " ";
    }
    std::cout << std::endl;
}

int MaxHeap::leftChild(int i) {
    return 2 * i + 1;
}

int MaxHeap::rightChild(int i) {
    return 2 * i + 2;
}

int MaxHeap::parent(int i) {
    return (i - 1) / 2;
}

void MaxHeap::insert(int key) {
    std::cout << "Inserting: " << key << std::endl;

    heapArr.push_back(key);
    reheapUp(static_cast<int>(heapArr.size() - 1));
}

void MaxHeap::deleteMax() {
    if (heapArr.empty()) {
        std::cout << "Heap is empty" << std::endl;
        return;
    }

    std::cout << "Deleting: " << heapArr[0] << std::endl;

    heapArr[0] = heapArr.back();
    heapArr.pop_back();
    reheapDown(0, static_cast<int>(heapArr.size() - 1));
}

void MaxHeap::reheapUp(int i) {
    int parentIndex = parent(i);

    while (i > 0 && heapArr[i] > heapArr[parentIndex]) {
        std::swap(heapArr[i], heapArr[parentIndex]);
        i = parentIndex;
        parentIndex = parent(i);
    }
}

void MaxHeap::reheapDown(int root, int bottom) {
    int maxChild;
    int rightChildIndex = rightChild(root);
    int leftChildIndex = leftChild(root);

    if (leftChildIndex <= bottom) {
        if (leftChildIndex == bottom) {
            maxChild = leftChildIndex;
        } else {
            if (heapArr[leftChildIndex] <= heapArr[rightChildIndex]) {
                maxChild = rightChildIndex;
            } else {
                maxChild = leftChildIndex;
            }
        }

        if (heapArr[root] < heapArr[maxChild]) {
            std::swap(heapArr[root], heapArr[maxChild]);
            reheapDown(maxChild, bottom);
        }
    }
}

int MaxHeap::search(int key) const {
    for (int i = 0; i < heapArr.size(); i++) {
        if (heapArr[i] == key) {
            return i;
        }
    }

    return -1;
}

void MaxHeap::deleteNode(int key) {
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