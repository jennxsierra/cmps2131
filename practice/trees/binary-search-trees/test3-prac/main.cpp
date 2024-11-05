#include <iostream>

// Node class for the BST using singly linked list
class Node {
public:
    int data;
    Node* left;
    Node* right;
};

// HELPER FUNCTIONS
Node* searchNode(Node* root, int key);
Node* inorderSuccessor(Node* root, int key);

// MODIFICATION FUNCTIONS
void insertNode(Node*& root, int value);
void deleteNode(Node*& root, int key);

// PRINTING FUNCTIONS
void printInorder(Node* root);
void printPreorder(Node* root);
void printPostorder(Node* root);

// PRACTICE FUNCTIONS
int countOddNodes(Node* root);
int countEvenNodes(Node* root);
bool isFullBinaryTree(Node* root);
int countDoubleParentNodes(Node* root);
int sumOfTreeNodes(Node* root);
int countNodesWithGreaterValue(Node* root, int key);
int countNodesWithLessValue(Node* root, int key);

int main () {
    Node* root{nullptr};
    insertNode(root, 72);
    insertNode(root, 65);
    insertNode(root, 84);
    insertNode(root, 69);
    insertNode(root, 67);
    insertNode(root, 83);

    std::cout << "Inorder Traversal: ";
    printInorder(root);
    std::cout << std::endl;

    std::cout << "Preorder Traversal: ";
    printPreorder(root);
    std::cout << std::endl;

    std::cout << "Postorder Traversal: ";
    printPostorder(root);
    std::cout << std::endl;

    std::cout << "\n\tPRACTICE QUESTIONS\n";
    std::cout << "-----------------------------\n";
    std::cout << "Number of odd nodes: " << countOddNodes(root) << std::endl;
    std::cout << "Number of even nodes: " << countEvenNodes(root) << std::endl;
    std::cout << "Is the tree a full binary tree? " << std::boolalpha << isFullBinaryTree(root) << std::endl;
    std::cout << "Number of nodes with two children: " << countDoubleParentNodes(root) << std::endl;
    std::cout << "Sum of all nodes: " << sumOfTreeNodes(root) << std::endl;
    std::cout << "Number of nodes with values greater than 70: " << countNodesWithGreaterValue(root, 70) << std::endl;
    std::cout << "Number of nodes with values less than 70: " << countNodesWithLessValue(root, 70) << std::endl;

    return 0;
}

// Helper function to search for a node in the BST
// Used in inorderSuccessor function
Node* searchNode(Node* root, int key) {
    if (root == nullptr || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return searchNode(root->left, key);
    }
    return searchNode(root->right, key);
}

// Helper function to find the inorder successor of a given key
// Used in deleteNode function
Node* inorderSuccessor(Node* root, int key) {
    Node* targNode{searchNode(root, key)};
    if (targNode == nullptr) {
        std::cout << "Node not found in the BST." << std::endl;
        return nullptr;
    }

    // Case 1: If the right subtree of the current node is not empty
    if (targNode->right != nullptr) {
        Node* temp{targNode->right};
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
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
        return successor;
    }
}

// Function to insert a new node in the BST
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

// Function to delete a node from the BST
void deleteNode(Node*& root, int key) {
    if (root == nullptr) {
        std::cout << "Node not found in the BST." << std::endl;
        return;
    }

    if (key < root->data) {
        deleteNode(root->left, key);
    } else if (key > root->data) {
        deleteNode(root->right, key);
    } else {
        // Case 1: Node has no children
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        // Case 2: Node has one child
        else if (root->left == nullptr) {
            Node* temp{root};
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            Node* temp{root};
            root = root->left;
            delete temp;
        }
        // Case 3: Node has two children
        else {
            Node* temp{inorderSuccessor(root, key)};
            root->data = temp->data;
            deleteNode(root->right, temp->data);
        }
    }
}

// Function to traverse the BST in inorder
void printInorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    printInorder(root->left); // Traverse the left subtree
    std::cout << root->data << " "; // Visit the node and print the data
    printInorder(root->right); // Traverse the right subtree
}

// Function to traverse the BST in preorder
void printPreorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    std::cout << root->data << " "; // Visit the node and print the data
    printPreorder(root->left); // Traverse the left subtree
    printPreorder(root->right); // Traverse the right subtree
}

// Function to traverse the BST in postorder
void printPostorder(Node* root) {
    if (root == nullptr) {
        return;
    }
    printPostorder(root->left); // Traverse the left subtree
    printPostorder(root->right); // Traverse the right subtree
    std::cout << root->data << " "; // Visit the node and print the data
}

// Function to count the number of odd nodes in the BST
int countOddNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->data % 2 != 0) {
        return 1 + countOddNodes(root->left) + countOddNodes(root->right);
    }
    return countOddNodes(root->left) + countOddNodes(root->right);
}

// Function to count the number of even nodes in the BST
int countEvenNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->data % 2 == 0) {
        return 1 + countEvenNodes(root->left) + countEvenNodes(root->right);
    }
    return countEvenNodes(root->left) + countEvenNodes(root->right);
}

// Function to check if the BST is a full binary tree
bool isFullBinaryTree(Node* root) {
    if (root == nullptr) {
        return true;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return true;
    }
    if (root->left != nullptr && root->right != nullptr) {
        return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
    }
    return false;
}

// Function to count the number of nodes with two children in the BST
int countDoubleParentNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left != nullptr && root->right != nullptr) {
        return 1 + countDoubleParentNodes(root->left) + countDoubleParentNodes(root->right);
    }
    return countDoubleParentNodes(root->left) + countDoubleParentNodes(root->right);
}

// Function to find the sum of all nodes in the BST
int sumOfTreeNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->data + sumOfTreeNodes(root->left) + sumOfTreeNodes(root->right);
}

// Function to count the number of nodes with values greater than a given key
int countNodesWithGreaterValue(Node* root, int key) {
    if (root == nullptr) {
        return 0;
    }
    if (root->data > key) {
        return 1 + countNodesWithGreaterValue(root->left, key) + countNodesWithGreaterValue(root->right, key);
    }
    return countNodesWithGreaterValue(root->right, key);
}

// Function to count the number of nodes with values less than a given key
int countNodesWithLessValue(Node* root, int key) {
    if (root == nullptr) {
        return 0;
    }
    if (root->data < key) {
        return 1 + countNodesWithLessValue(root->left, key) + countNodesWithLessValue(root->right, key);
    }
    return countNodesWithLessValue(root->left, key);
}