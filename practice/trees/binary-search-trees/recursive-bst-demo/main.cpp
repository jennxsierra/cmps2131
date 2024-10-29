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

// MISC FUNCTIONS
int findMin(Node* root);
int findMax(Node* root);
int findDiffMinMax(Node* root);
int nodeCount(Node* root);
int treeHeight(Node* root);

// TEXTBOOK QUESTIONS
bool isBST(Node* root);
int leafCount(Node* root);
int singleParentCount(Node* root);
int lessThanCount(Node* root, int key);

// PRACTICE QUESTIONS
void printOddNodes(Node* root);
void printEvenNodes(Node* root);
void printKeysInRange(Node* root, int low, int high);
int findKthSmallest(Node* root, int k);
int findKthLargest(Node* root, int k);
int findMedian(Node* root);

int main () {
    Node* root{nullptr};
    insertNode(root, 55);
    insertNode(root, 30);
    insertNode(root, 25);
    insertNode(root, 40);
    insertNode(root, 75);
    insertNode(root, 60);
    insertNode(root, 85);

    std::cout << "Inorder Traversal: ";
    printInorder(root);
    std::cout << std::endl;

    std::cout << "Preorder Traversal: ";
    printPreorder(root);
    std::cout << std::endl;

    std::cout << "Postorder Traversal: ";
    printPostorder(root);
    std::cout << std::endl;

    std::cout << "\n\tTextbook Questions:" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Is the binary tree a BST? " << (isBST(root) ? "Yes" : "No") << std::endl;
    std::cout << "Number of leaf nodes: " << leafCount(root) << std::endl;
    std::cout << "Number of nodes with only one child: " << singleParentCount(root) << std::endl;
    std::cout << "Number of nodes with values less than 50: " << lessThanCount(root, 50) << std::endl;

    std::cout << "\n\tAdditional Functions:" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Minimum value in the BST: " << findMin(root) << std::endl;
    std::cout << "Maximum value in the BST: " << findMax(root) << std::endl;
    std::cout << "Difference between min and max values: " << findDiffMinMax(root) << std::endl;
    std::cout << "Number of nodes in the BST: " << nodeCount(root) << std::endl;
    std::cout << "Height of the BST: " << treeHeight(root) << std::endl;

    std::cout << "\n\tPractice Questions:" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Odd nodes in the BST: ";
    printOddNodes(root);
    std::cout << std::endl;

    std::cout << "Even nodes in the BST: ";
    printEvenNodes(root);
    std::cout << std::endl;

    std::cout << "Keys in the BST within the range 30-60: ";
    printKeysInRange(root, 30, 60);
    std::cout << std::endl;

    std::cout << "3rd smallest element in the BST: " << findKthSmallest(root, 3) << std::endl;
    std::cout << "3rd largest element in the BST: " << findKthLargest(root, 3) << std::endl;
    std::cout << "Median of the BST: " << findMedian(root) << std::endl;

    std::cout << "\n\tDeleting nodes from the BST:" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    deleteNode(root, 25);
    std::cout << "Inorder Traversal after deleting 25: ";
    printInorder(root);
    std::cout << std::endl;

    deleteNode(root, 75);
    std::cout << "Inorder Traversal after deleting 75: ";
    printInorder(root);
    std::cout << std::endl;

    deleteNode(root, 55);
    std::cout << "Inorder Traversal after deleting 55: ";
    printInorder(root);
    std::cout << std::endl;

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

// Function to find the minimum value in the BST
int findMin(Node* root) {
    if (root == nullptr) {
        std::cout << "Tree is empty." << std::endl;
        return -1;
    }
    while (root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

// Function to find the maximum value in the BST
int findMax(Node* root) {
    if (root == nullptr) {
        std::cout << "Tree is empty." << std::endl;
        return -1;
    }
    while (root->right != nullptr) {
        root = root->right;
    }
    return root->data;
}

// Function to find the difference between the minimum and maximum values in the BST
int findDiffMinMax(Node* root) {
    return findMax(root) - findMin(root);
}

// Function to count the number of nodes in the BST
int nodeCount(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + nodeCount(root->left) + nodeCount(root->right);
}

// Function to find the height of the BST
int treeHeight(Node* root) {
    if (root == nullptr) {
        return -1;
    }
    return 1 + std::max(treeHeight(root->left), treeHeight(root->right));
}

// Function to check if the given binary tree is a BST
bool isBST(Node* root) {
    if (root == nullptr) {
        return true;
    }
    if (root->left != nullptr && findMax(root->left) > root->data) {
        return false;
    }
    if (root->right != nullptr && findMin(root->right) <= root->data) {
        return false;
    }
    if (!isBST(root->left) || !isBST(root->right)) {
        return false;
    }
    return true;
}

// Function to count the number of leaf nodes in the BST
int leafCount(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    return leafCount(root->left) + leafCount(root->right);
}

// Function to count the number of nodes with only one child in the BST
int singleParentCount(Node* root) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
        return 0;
    }
    if (root->left == nullptr || root->right == nullptr) {
        return 1 + singleParentCount(root->left) + singleParentCount(root->right);
    }
    return singleParentCount(root->left) + singleParentCount(root->right);
}

// Function to count the number of nodes with values less than a given key
int lessThanCount(Node* root, int key) {
    if (root == nullptr) {
        return 0;
    }
    if (root->data < key) {
        return 1 + lessThanCount(root->left, key) + lessThanCount(root->right, key);
    }
    return lessThanCount(root->left, key);
}

// Function to print the odd nodes in the BST
void printOddNodes(Node* root) {
    if (root == nullptr) {
        return;
    }
    printOddNodes(root->left);
    if (root->data % 2 != 0) {
        std::cout << root->data << " ";
    }
    printOddNodes(root->right);
}

// Function to print the even nodes in the BST
void printEvenNodes(Node* root) {
    if (root == nullptr) {
        return;
    }
    printEvenNodes(root->left);
    if (root->data % 2 == 0) {
        std::cout << root->data << " ";
    }
    printEvenNodes(root->right);
}

// Function to print the keys in the BST within a given range
void printKeysInRange(Node* root, int low, int high) {
    if (root == nullptr) {
        return;
    }
    if (root->data > low) {
        printKeysInRange(root->left, low, high);
    }
    if (root->data >= low && root->data <= high) {
        std::cout << root->data << " ";
    }
    if (root->data < high) {
        printKeysInRange(root->right, low, high);
    }
}

// Function to find the kth smallest element in the BST
int findKthSmallest(Node* root, int k) {
    if (root == nullptr) {
        return -1;
    }
    int leftCount{nodeCount(root->left)};
    if (leftCount == k - 1) {
        return root->data;
    }
    if (leftCount >= k) {
        return findKthSmallest(root->left, k);
    }
    return findKthSmallest(root->right, k - leftCount - 1);
}

// Function to find the kth largest element in the BST
int findKthLargest(Node* root, int k) {
    if (root == nullptr) {
        return -1;
    }
    int rightCount{nodeCount(root->right)};
    if (rightCount == k - 1) {
        return root->data;
    }
    if (rightCount >= k) {
        return findKthLargest(root->right, k);
    }
    return findKthLargest(root->left, k - rightCount - 1);
}

// Function to find the median of the BST
int findMedian(Node* root) {
    int count{nodeCount(root)};
    if (count % 2 != 0) {
        return findKthSmallest(root, count / 2 + 1);
    }
    return (findKthSmallest(root, count / 2) + findKthSmallest(root, count / 2 + 1)) / 2;
}