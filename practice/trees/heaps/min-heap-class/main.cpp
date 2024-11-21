#include "MinHeap.h"

int main() {
    int arr[] = {12, 11, 23, 15, 6, 71};
    MinHeap minHeap{};

    for (int i : arr) {
        minHeap.insert(i);
    }

    minHeap.printHeap();

    minHeap.deleteMin();
    minHeap.printHeap();

    minHeap.insert(2);
    minHeap.printHeap();

    minHeap.deleteNode(15);
    minHeap.printHeap();

    return 0;
}
