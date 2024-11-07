#include <iostream>

// Node class for Max Heap
class MaxHeap {
private:
    // Pointer to array of elements in the heap
    int* heapArray;

    // Maximum possible size of the heap
    int maxSize;

    // Current number of elements in the heap
    int heapSize;

public:
    // Constructor
    explicit MaxHeap(int maxSize);

    // Destructor
    ~MaxHeap();

    // Heapifies a subtree taking given index as root
    void heapify(int i);

    // Returns the index of the parent of the element at index i
    static int parent(int i) {
        return (i - 1) / 2;
    }

    // Returns the index of the left child
    static int leftChild(int i) {
        return 2 * i + 1;
    }

    // Returns the index of the right child
    static int rightChild(int i) {
        return 2 * i + 2;
    }

    // Removes the root which is the maximum element
    int extractMax();

    // Increases the value of the element at index i to new value
    void increaseKey(int i, int newValue);

    // Returns the maximum element in the heap
    int getMax() {
        return heapArray[0];
    }

    // Returns the current size of the heap
    [[nodiscard]] int getSize() const {
        return heapSize;
    }

    // Inserts a new key 'k' into the heap
    void insertKey(int k);

    // Deletes a key stored at index i
    void deleteKey(int i);

    // Prints the heap
    void printHeap() {
        for (int i = 0; i < heapSize; i++) {
            std::cout << heapArray[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MaxHeap maxHeap(10);

    std::cout << "Inserting following elements into the heap: 3, 2, 15, 5, 4, 45" << std::endl;

    maxHeap.insertKey(3);
    maxHeap.insertKey(2);
    maxHeap.insertKey(15);
    maxHeap.insertKey(5);
    maxHeap.insertKey(4);
    maxHeap.insertKey(45);

    std::cout << "Heap: ";
    maxHeap.printHeap();
    std::cout << "The current size of the heap is: " << maxHeap.getSize() << std::endl;
    std::cout << "The maximum element in the heap is: " << maxHeap.getMax() << std::endl;

    std::cout << "\nDeleting the element at index 2." << std::endl;
    maxHeap.deleteKey(2);
    std::cout << "Heap: ";
    maxHeap.printHeap();
    std::cout << "The current size of the heap is: " << maxHeap.getSize() << std::endl;

    std::cout << "\nInserting 2 new elements into the heap: 12, 50" << std::endl;
    maxHeap.insertKey(12);
    maxHeap.insertKey(50);
    std::cout << "Heap: ";
    maxHeap.printHeap();
    std::cout << "The current size of the heap is: " << maxHeap.getSize() << std::endl;
    std::cout << "The maximum element in the heap is: " << maxHeap.getMax() << std::endl;

    return 0;
}

MaxHeap::MaxHeap(int maxSize) {
    // Constructor
    heapSize = 0;
    this->maxSize = maxSize;
    heapArray = new int[maxSize];
}

MaxHeap::~MaxHeap() {
    // Destructor
    delete[] heapArray;
}

void MaxHeap::heapify(int i) {
    int l = leftChild(i);
    int r = rightChild(i);
    int largest = i;

    if (l < heapSize && heapArray[l] > heapArray[i]) {
        largest = l;
    }

    if (r < heapSize && heapArray[r] > heapArray[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(heapArray[i], heapArray[largest]);
        heapify(largest);
    }
}

int MaxHeap::extractMax() {
    // Check if the heap is empty
    if (heapSize <= 0) {
        return -1;
    }

    if (heapSize == 1) {
        heapSize--;
        return heapArray[0];
    }

    // Store the maximum value
    int root = heapArray[0];
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;

    // Restore the heap property
    heapify(0);

    return root;
}

void MaxHeap::increaseKey(int i, int newValue) {
    // Check if the new value is less than the current value
    if (newValue < heapArray[i]) {
        return;
    }

    heapArray[i] = newValue;

    // Fix the heap property
    while (i != 0 && heapArray[parent(i)] < heapArray[i]) {
        std::swap(heapArray[i], heapArray[parent(i)]);
        i = parent(i);
    }
}

void MaxHeap::insertKey(int k) {
    // Check if the heap is full
    if (heapSize == maxSize) {
        std::cout << "\nOverflow: Could not insert key" << std::endl;
        return;
    }

    // Insert the new key at the end
    heapSize++;
    int i = heapSize - 1;
    heapArray[i] = k;

    // Fix the heap property
    while (i != 0 && heapArray[parent(i)] < heapArray[i]) {
        std::swap(heapArray[i], heapArray[parent(i)]);
        i = parent(i);
    }
}

void MaxHeap::deleteKey(int i) {
    // Check if the index is valid
    if (i < 0 || i >= heapSize) {
        std::cout << "\nInvalid index" << std::endl;
        return;
    }

    // Increase the key to the maximum value
    increaseKey(i, INT_MAX);

    // Remove the maximum element
    extractMax();
}