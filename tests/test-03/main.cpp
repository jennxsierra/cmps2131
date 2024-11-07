#include <iostream>

class Node {
public:
    int data;
    Node* left;
    Node* right;
};

void insertNode(Node*& root, int value);
void printNodesWithLessValue(Node* root, int key);

int main () {
    Node* root{nullptr};
    insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 70);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 60);
    insertNode(root, 80);
    insertNode(root, 85);

    std::cout << "Nodes with less value than 70: ";
    printNodesWithLessValue(root, 70);
    std::cout << std::endl;

    return 0;
}

void insertNode(Node*& root, int value) {
    if (root == nullptr) {
        root = new Node();
        root->data = value;
        root->left = root->right = nullptr;
    } else if (value <= root->data) {
        insertNode(root->left, value);
    } else {
        insertNode(root->right, value);
    }
}

void printNodesWithLessValue(Node* root, int key) {
    if (root == nullptr) {
        return;
    }

    printNodesWithLessValue(root->left, key);

    if (root->data < key) {
        std::cout << root->data << " ";
    }

    printNodesWithLessValue(root->right, key);
}