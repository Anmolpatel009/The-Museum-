/*
C++ Binary Search Tree Implementation - Comprehensive Guide
============================================================
This file demonstrates a complete implementation of a Binary Search Tree (BST)
with various operations including insertion, deletion, traversal, and utility
functions.
*/

#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

// =========================================================================
// Binary Search Tree Node Structure
// =========================================================================
template <typename T>
struct BSTNode {
    T data;
    BSTNode* left;
    BSTNode* right;
    int height; // For AVL tree calculations
    
    BSTNode(const T& value) 
        : data(value), left(nullptr), right(nullptr), height(1) {}
};

// =========================================================================
// Binary Search Tree Class
// =========================================================================
template <typename T>
class BinarySearchTree {
private:
    BSTNode<T>* root;
    
    // Helper functions
    BSTNode<T>* insertRecursive(BSTNode<T>* node, const T& value);
    BSTNode<T>* deleteRecursive(BSTNode<T>* node, const T& value);
    BSTNode<T>* findMinNode(BSTNode<T>* node);
    BSTNode<T>* findRecursive(BSTNode<T>* node, const T& value) const;
    void inorderRecursive(BSTNode<T>* node) const;
    void preorderRecursive(BSTNode<T>* node) const;
    void postorderRecursive(BSTNode<T>* node) const;
    int getHeight(BSTNode<T>* node) const;
    int getSize(BSTNode<T>* node) const;
    void clearRecursive(BSTNode<T>* node);
    bool isBalancedRecursive(BSTNode<T>* node) const;
    BSTNode<T>* mirrorRecursive(BSTNode<T>* node);
    int getLevel(BSTNode<T>* node, const T& value, int level) const;
    int countLeavesRecursive(BSTNode<T>* node) const;
    void printLevelOrderRecursive(BSTNode<T>* node) const;
    
public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}
    
    // Destructor
    ~BinarySearchTree() {
        clear();
    }
    
    // Basic operations
    void insert(const T& value);
    void remove(const T& value);
    bool contains(const T& value) const;
    T findMin() const;
    T findMax() const;
    
    // Traversal methods
    void inorder() const;
    void preorder() const;
    void postorder() const;
    void levelOrder() const;
    void inorderIterative() const;
    void preorderIterative() const;
    void postorderIterative() const;
    
    // Utility functions
    bool isEmpty() const;
    int getHeight() const;
    int getSize() const;
    void clear();
    int getLevel(const T& value) const;
    bool isBalanced() const;
    void mirror();
    int countLeaves() const;
    void printTree() const;
    
    // Advanced operations
    bool isBST() const;
    bool isBSTRecursive(BSTNode<T>* node, T* minVal, T* maxVal) const;
};

// =========================================================================
// Private Helper Methods
// =========================================================================

template <typename T>
BSTNode<T>* BinarySearchTree<T>::insertRecursive(BSTNode<T>* node, const T& value) {
    if (node == nullptr) {
        return new BSTNode<T>(value);
    }
    
    if (value < node->data) {
        node->left = insertRecursive(node->left, value);
    } else if (value > node->data) {
        node->right = insertRecursive(node->right, value);
    }
    
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return node;
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::deleteRecursive(BSTNode<T>* node, const T& value) {
    if (node == nullptr) {
        return node;
    }
    
    if (value < node->data) {
        node->left = deleteRecursive(node->left, value);
    } else if (value > node->data) {
        node->right = deleteRecursive(node->right, value);
    } else {
        // Node to be deleted found
        
        // Case 1: No children or only one child
        if (node->left == nullptr) {
            BSTNode<T>* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            BSTNode<T>* temp = node->left;
            delete node;
            return temp;
        }
        
        // Case 2: Node has two children - find inorder successor (min in right subtree)
        BSTNode<T>* temp = findMinNode(node->right);
        node->data = temp->data;
        node->right = deleteRecursive(node->right, temp->data);
    }
    
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return node;
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::findMinNode(BSTNode<T>* node) {
    BSTNode<T>* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::findRecursive(BSTNode<T>* node, const T& value) const {
    if (node == nullptr || node->data == value) {
        return node;
    }
    
    if (value < node->data) {
        return findRecursive(node->left, value);
    }
    
    return findRecursive(node->right, value);
}

template <typename T>
void BinarySearchTree<T>::inorderRecursive(BSTNode<T>* node) const {
    if (node != nullptr) {
        inorderRecursive(node->left);
        cout << node->data << " ";
        inorderRecursive(node->right);
    }
}

template <typename T>
void BinarySearchTree<T>::preorderRecursive(BSTNode<T>* node) const {
    if (node != nullptr) {
        cout << node->data << " ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }
}

template <typename T>
void BinarySearchTree<T>::postorderRecursive(BSTNode<T>* node) const {
    if (node != nullptr) {
        postorderRecursive(node->left);
        postorderRecursive(node->right);
        cout << node->data << " ";
    }
}

template <typename T>
int BinarySearchTree<T>::getHeight(BSTNode<T>* node) const {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

template <typename T>
int BinarySearchTree<T>::getSize(BSTNode<T>* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getSize(node->left) + getSize(node->right);
}

template <typename T>
void BinarySearchTree<T>::clearRecursive(BSTNode<T>* node) {
    if (node != nullptr) {
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }
}

template <typename T>
bool BinarySearchTree<T>::isBalancedRecursive(BSTNode<T>* node) const {
    if (node == nullptr) {
        return true;
    }
    
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    
    if (abs(leftHeight - rightHeight) <= 1 &&
        isBalancedRecursive(node->left) &&
        isBalancedRecursive(node->right)) {
        return true;
    }
    
    return false;
}

template <typename T>
BSTNode<T>* BinarySearchTree<T>::mirrorRecursive(BSTNode<T>* node) {
    if (node == nullptr) {
        return nullptr;
    }
    
    BSTNode<T>* temp = node->left;
    node->left = mirrorRecursive(node->right);
    node->right = mirrorRecursive(temp);
    
    return node;
}

template <typename T>
int BinarySearchTree<T>::getLevel(BSTNode<T>* node, const T& value, int level) const {
    if (node == nullptr) {
        return -1;
    }
    
    if (node->data == value) {
        return level;
    }
    
    int leftLevel = getLevel(node->left, value, level + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }
    
    return getLevel(node->right, value, level + 1);
}

template <typename T>
int BinarySearchTree<T>::countLeavesRecursive(BSTNode<T>* node) const {
    if (node == nullptr) {
        return 0;
    }
    
    if (node->left == nullptr && node->right == nullptr) {
        return 1;
    }
    
    return countLeavesRecursive(node->left) + countLeavesRecursive(node->right);
}

// =========================================================================
// Public Methods
// =========================================================================

template <typename T>
void BinarySearchTree<T>::insert(const T& value) {
    root = insertRecursive(root, value);
}

template <typename T>
void BinarySearchTree<T>::remove(const T& value) {
    root = deleteRecursive(root, value);
}

template <typename T>
bool BinarySearchTree<T>::contains(const T& value) const {
    return findRecursive(root, value) != nullptr;
}

template <typename T>
T BinarySearchTree<T>::findMin() const {
    if (isEmpty()) {
        throw runtime_error("Tree is empty");
    }
    
    BSTNode<T>* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->data;
}

template <typename T>
T BinarySearchTree<T>::findMax() const {
    if (isEmpty()) {
        throw runtime_error("Tree is empty");
    }
    
    BSTNode<T>* current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->data;
}

template <typename T>
void BinarySearchTree<T>::inorder() const {
    if (isEmpty()) {
        cout << "Tree is empty" << endl;
        return;
    }
    inorderRecursive(root);
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::preorder() const {
    if (isEmpty()) {
        cout << "Tree is empty" << endl;
        return;
    }
    preorderRecursive(root);
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::postorder() const {
    if (isEmpty()) {
        cout << "Tree is empty" << endl;
        return;
    }
    postorderRecursive(root);
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::levelOrder() const {
    if (isEmpty()) {
        cout << "Tree is empty" << endl;
        return;
    }
    
    queue<BSTNode<T>*> q;
    q.push(root);
    
    while (!q.empty()) {
        BSTNode<T>* node = q.front();
        q.pop();
        
        cout << node->data << " ";
        
        if (node->left != nullptr) {
            q.push(node->left);
        }
        
        if (node->right != nullptr) {
            q.push(node->right);
        }
    }
    
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::inorderIterative() const {
    if (isEmpty()) {
        cout << "Tree is empty" << endl;
        return;
    }
    
    stack<BSTNode<T>*> s;
    BSTNode<T>* current = root;
    
    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }
        
        current = s.top();
        s.pop();
        cout << current->data << " ";
        current = current->right;
    }
    
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::preorderIterative() const {
    if (isEmpty()) {
        cout << "Tree is empty" << endl;
        return;
    }
    
    stack<BSTNode<T>*> s;
    s.push(root);
    
    while (!s.empty()) {
        BSTNode<T>* node = s.top();
        s.pop();
        cout << node->data << " ";
        
        if (node->right != nullptr) {
            s.push(node->right);
        }
        
        if (node->left != nullptr) {
            s.push(node->left);
        }
    }
    
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::postorderIterative() const {
    if (isEmpty()) {
        cout << "Tree is empty" << endl;
        return;
    }
    
    stack<BSTNode<T>*> s1, s2;
    s1.push(root);
    
    while (!s1.empty()) {
        BSTNode<T>* node = s1.top();
        s1.pop();
        s2.push(node);
        
        if (node->left != nullptr) {
            s1.push(node->left);
        }
        
        if (node->right != nullptr) {
            s1.push(node->right);
        }
    }
    
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
    
    cout << endl;
}

template <typename T>
bool BinarySearchTree<T>::isEmpty() const {
    return root == nullptr;
}

template <typename T>
int BinarySearchTree<T>::getHeight() const {
    return getHeight(root);
}

template <typename T>
int BinarySearchTree<T>::getSize() const {
    return getSize(root);
}

template <typename T>
void BinarySearchTree<T>::clear() {
    clearRecursive(root);
    root = nullptr;
}

template <typename T>
int BinarySearchTree<T>::getLevel(const T& value) const {
    return getLevel(root, value, 1);
}

template <typename T>
bool BinarySearchTree<T>::isBalanced() const {
    return isBalancedRecursive(root);
}

template <typename T>
void BinarySearchTree<T>::mirror() {
    root = mirrorRecursive(root);
}

template <typename T>
int BinarySearchTree<T>::countLeaves() const {
    return countLeavesRecursive(root);
}

template <typename T>
bool BinarySearchTree<T>::isBSTRecursive(BSTNode<T>* node, T* minVal, T* maxVal) const {
    if (node == nullptr) {
        return true;
    }
    
    if ((minVal != nullptr && node->data <= *minVal) ||
        (maxVal != nullptr && node->data >= *maxVal)) {
        return false;
    }
    
    return isBSTRecursive(node->left, minVal, &node->data) &&
           isBSTRecursive(node->right, &node->data, maxVal);
}

template <typename T>
bool BinarySearchTree<T>::isBST() const {
    return isBSTRecursive(root, nullptr, nullptr);
}

template <typename T>
void BinarySearchTree<T>::printTree() const {
    if (isEmpty()) {
        cout << "Tree is empty" << endl;
        return;
    }
    
    queue<BSTNode<T>*> q;
    q.push(root);
    int level = 0;
    
    while (!q.empty()) {
        int levelSize = q.size();
        cout << "Level " << level << ": ";
        
        for (int i = 0; i < levelSize; ++i) {
            BSTNode<T>* node = q.front();
            q.pop();
            
            cout << node->data << "(" << getHeight(node) << ") ";
            
            if (node->left != nullptr) {
                q.push(node->left);
            }
            
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        
        cout << endl;
        level++;
    }
}

// =========================================================================
// Main Function for Testing
// =========================================================================
int main() {
    cout << "=== C++ Binary Search Tree Implementation ===\n\n";
    
    BinarySearchTree<int> bst;
    
    // Insert elements
    cout << "1. Inserting elements: 50, 30, 70, 20, 40, 60, 80\n";
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    // Tree structure
    cout << "\n2. Tree structure:\n";
    bst.printTree();
    
    // Basic properties
    cout << "\n3. Tree properties:\n";
    cout << "Size: " << bst.getSize() << endl;
    cout << "Height: " << bst.getHeight() << endl;
    cout << "Min value: " << bst.findMin() << endl;
    cout << "Max value: " << bst.findMax() << endl;
    cout << "Is balanced: " << (bst.isBalanced() ? "Yes" : "No") << endl;
    cout << "Leaves count: " << bst.countLeaves() << endl;
    
    // Search operations
    cout << "\n4. Search operations:\n";
    int searchValue = 40;
    cout << "Contains " << searchValue << ": " << (bst.contains(searchValue) ? "Yes" : "No") << endl;
    cout << searchValue << " is at level: " << bst.getLevel(searchValue) << endl;
    
    // Tree traversals
    cout << "\n5. Tree traversals:\n";
    cout << "Inorder (Recursive): ";
    bst.inorder();
    cout << "Inorder (Iterative): ";
    bst.inorderIterative();
    cout << "Preorder (Recursive): ";
    bst.preorder();
    cout << "Preorder (Iterative): ";
    bst.preorderIterative();
    cout << "Postorder (Recursive): ";
    bst.postorder();
    cout << "Postorder (Iterative): ";
    bst.postorderIterative();
    cout << "Level order: ";
    bst.levelOrder();
    
    // Delete operation
    cout << "\n6. Delete operations:\n";
    cout << "Deleting 20 (leaf node):\n";
    bst.remove(20);
    bst.printTree();
    
    cout << "Deleting 70 (node with two children):\n";
    bst.remove(70);
    bst.printTree();
    
    cout << "Deleting 50 (root node):\n";
    bst.remove(50);
    bst.printTree();
    
    // Check if still BST
    cout << "\n7. Tree properties after deletions:\n";
    cout << "Is valid BST: " << (bst.isBST() ? "Yes" : "No") << endl;
    cout << "Size: " << bst.getSize() << endl;
    cout << "Height: " << bst.getHeight() << endl;
    
    // Clear and test empty tree
    cout << "\n8. Clearing the tree:\n";
    bst.clear();
    cout << "Is empty: " << (bst.isEmpty() ? "Yes" : "No") << endl;
    cout << "Size: " << bst.getSize() << endl;
    
    return 0;
}

/*
Key Takeaways:
1. Binary Search Tree: Left subtree < root < right subtree for all nodes
2. Average time complexity: O(log n) for insert, delete, search
3. Worst case O(n) for unbalanced tree (chain-like structure)
4. Traversal methods:
   - Inorder: Left -> Root -> Right (sorted order for BST)
   - Preorder: Root -> Left -> Right
   - Postorder: Left -> Right -> Root
   - Level order: BFS traversal
5. Important properties:
   - Height: Maximum depth from root to any leaf
   - Size: Total number of nodes
   - Balance: Difference in height of left and right subtrees <= 1
6. Deletion cases:
   - Node with 0 children: Simply remove
   - Node with 1 child: Replace with child
   - Node with 2 children: Replace with inorder successor (min in right subtree)
*/
