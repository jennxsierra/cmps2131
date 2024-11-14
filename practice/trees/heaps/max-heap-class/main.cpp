#include <iostream>
#include "MaxHeap.h"

int main() {
    int arr[] = {12, 11, 23, 15, 6, 71};
    MaxHeap maxHeap{};

    for (int i : arr) {
        maxHeap.insert(i);
    }

    maxHeap.printHeap();
    maxHeap.deleteMax();
    maxHeap.printHeap();

    maxHeap.insert(50);
    maxHeap.printHeap();

    maxHeap.deleteNode(15);
    maxHeap.printHeap();

    return 0;
}