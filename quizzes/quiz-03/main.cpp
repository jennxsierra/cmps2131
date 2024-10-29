#include <iostream>

class Node {
public:
    int data;
    Node* left;
    Node* right;
};

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

Node* findParentOfLargest(Node* root) {
    if (root == nullptr || root->right == nullptr) {
        return nullptr; // No parent if tree is empty or root is the largest node
    }

    Node* parent = nullptr;
    Node* current = root;

    while (current->right != nullptr) {
        parent = current;
        current = current->right;
    }

    return parent;
}

int main () {
    Node* root{nullptr};
    insertNode(root, 10);
    insertNode(root, 5);
    insertNode(root, 20);
    insertNode(root, 15);
    insertNode(root, 30);
    insertNode(root, 35);

    Node* parent = findParentOfLargest(root);
    if (parent != nullptr) {
        std::cout << "Parent of the largest node is: " << parent->data << std::endl;
    } else {
        std::cout << "The largest node is the root or the tree is empty." << std::endl;
    }

    return 0;
}