#include <iostream>

// Node class for the BST using singly linked list
class Node {
public:
    int data;
    Node* left;
    Node* right;
};

// Function to insert a new node in the BST
Node* insertNode(Node*& root, int value) {
    if (root == nullptr) {
        root = new Node();
        root->data = value;
        root->left = root->right = nullptr;
    } else if (value <= root->data) {
        root->left = insertNode(root->left, value);
    } else {
        root->right = insertNode(root->right, value);
    }
    return root;
}

// Helper function to search for a node in the BST
Node* searchNode(Node* root, int key) {
    if (root == nullptr || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return searchNode(root->left, key);
    }
    return searchNode(root->right, key);
}

// Function to find the inorder predecessor of a given key
void inorderPredecessor(Node* root, int key) {
    Node* targNode{searchNode(root, key)};
    if (targNode == nullptr) {
        std::cout << "Node not found in the BST." << std::endl;
        return;
    }

    // Case 1: If the left subtree of the current node is not empty
    if (targNode->left != nullptr) {
        Node* temp{targNode->left};
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        std::cout << "Inorder Predecessor of " << key << " is " << temp->data << std::endl;
    } else {
        // Case 2: If the left subtree of the current node is empty
        Node* predecessor{nullptr};
        Node* ancestor{root};
        while (ancestor != targNode) {
            if (targNode->data > ancestor->data) {
                predecessor = ancestor;
                ancestor = ancestor->right;
            } else {
                ancestor = ancestor->left;
            }
        }
        if (predecessor == nullptr) {
            std::cout << "No inorder predecessor found for " << key << std::endl;
        } else {
            std::cout << "Inorder Predecessor of " << key << " is " << predecessor->data << std::endl;
        }
    }
}

// Function to find the inorder successor of a given key
void inorderSuccessor(Node* root, int key) {
    Node* targNode{searchNode(root, key)};
    if (targNode == nullptr) {
        std::cout << "Node not found in the BST." << std::endl;
        return;
    }

    // Case 1: If the right subtree of the current node is not empty
    if (targNode->right != nullptr) {
        Node* temp{targNode->right};
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        std::cout << "Inorder Successor of " << key << " is " << temp->data << std::endl;
    } else {
        // Case 2: If the right subtree of the current node is empty
        Node* successor{nullptr};
        Node* ancestor{root};

        while (ancestor != targNode) {
            if (targNode->data < ancestor->data) {
                successor = ancestor;
                ancestor = ancestor->left;
            } else {
                ancestor = ancestor->right;
            }
        }
        if (successor == nullptr) {
            std::cout << "No inorder successor found for " << key << std::endl;
        } else {
            std::cout << "Inorder Successor of " << key << " is " << successor->data << std::endl;
        }
    }
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

    // BST Structure
    //          15
    //         /  \
    //        10   20
    //       / \   / \
    //      8  12 17 25
    //    /         /
    //   3         22

    // Inorder Traversal: 3 8 10 12 15 17 20 22 25

    inorderPredecessor(root, 3);
    inorderSuccessor(root, 3);

    std::cout << std::endl;

    inorderPredecessor(root, 8);
    inorderSuccessor(root, 8);

    std::cout << std::endl;

    inorderPredecessor(root, 10);
    inorderSuccessor(root, 10);

    std::cout << std::endl;

    inorderPredecessor(root, 17);
    inorderSuccessor(root, 17);

    std::cout << std::endl;

    inorderPredecessor(root, 25);
    inorderSuccessor(root, 25);

    std::cout << std::endl;

    inorderPredecessor(root, 20);
    inorderSuccessor(root, 20);

    return 0;
}