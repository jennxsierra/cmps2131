#include <iostream>

// Node class for the BST using singly linked list
class Node {
public:
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to insert a new node in the BST
Node* insertNode(Node*& root, int value) {
    if (root == nullptr) {
        root = createNode(value);
    } else if (value <= root->data) {
        root->left = insertNode(root->left, value);
    } else {
        root->right = insertNode(root->right, value);
    }
    return root;
}

// Function to traverse the BST in inorder
void inorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left); // Traverse the left subtree
    std::cout << root->data << " "; // Visit the node and print the data
    inorderTraversal(root->right); // Traverse the right subtree
}

// Function to traverse the BST in preorder
void preorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    std::cout << root->data << " "; // Visit the node and print the data
    preorderTraversal(root->left); // Traverse the left subtree
    preorderTraversal(root->right); // Traverse the right subtree
}

// Function to traverse the BST in postorder
void postorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    postorderTraversal(root->left); // Traverse the left subtree
    postorderTraversal(root->right); // Traverse the right subtree
    std::cout << root->data << " "; // Visit the node and print the data
}

int main() {
    Node* root = nullptr;
    root = insertNode(root, 15);
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 8);
    root = insertNode(root, 12);
    root = insertNode(root, 17);
    root = insertNode(root, 25);
    root = insertNode(root, 3);
    root = insertNode(root, 22);

    std::cout << "Inorder Traversal: ";
    inorderTraversal(root);
    std::cout << std::endl;

    std::cout << "Preorder Traversal: ";
    preorderTraversal(root);
    std::cout << std::endl;

    std::cout << "Postorder Traversal: ";
    postorderTraversal(root);
    std::cout << std::endl;

    return 0;
}