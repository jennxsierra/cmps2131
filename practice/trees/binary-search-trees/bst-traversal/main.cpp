// Program to traverse and search a Binary Search Tree (BST)
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

// Function to search for a value in the BST and return the node if found
Node* search(Node* root, int value) {
    Node* current = root;

    // Traverse the tree until the value is found or the current node is nullptr
    while (current != nullptr) {
        if (current->data == value) {
            return current;
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // If the value is not found, return nullptr
    return nullptr;
}

// Function to find the inorder successor of a given node
Node* inorderSuccessor(Node* root, int value) {
    Node *current = root;

    // Find the node with the given value using search function
    Node *targetNode = search(root, value);

    // If the node is not found, return nullptr
    if (targetNode == nullptr) {
        return nullptr;
    }

    // If the right subtree of the target node is not null
    if (targetNode->right != nullptr) {
        // Find the leftmost node in the right subtree
        current = targetNode->right;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    } else {
        // If the right subtree is null, find the ancestor of the target node
        Node *successor = nullptr;
        while (root != nullptr) {
            if (targetNode->data < root->data) {
                successor = root;
                root = root->left;
            } else if (targetNode->data > root->data) {
                root = root->right;
            } else {
                break;
            }
        }
        return successor;
    }
}

int main () {
    // Creating the BST
    Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(12);

    // Search for a value in the BST
    std::cout << "Searching for value 5 in the BST..." << std::endl;
    Node *searchResult = search(root, 5);
    std::cout << "Status: ";
    if (searchResult != nullptr) {
        std::cout << "Found" << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }

    //Find the inorder successor of that value
    std::cout << "Inorder successor of 5 is: ";
    Node *successor = inorderSuccessor(root, 5);
    if (successor != nullptr) {
        std::cout << successor->data << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }

    // Clean up the memory
    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}