# C++ Data Structures and Algorithms (DSA) Repository

Welcome to the C++ DSA repository! This repository contains a comprehensive collection of C++ implementations for various data structures, algorithms, and STL (Standard Template Library) components. It's designed to serve as a complete resource for learning and practicing DSA concepts in C++.

## Repository Structure

The repository is organized into the following main categories:

### 1. [STL/](./STL/) - Standard Template Library
Complete guide to C++ Standard Template Library including:
- Containers (vector, list, deque, stack, queue, priority_queue)
- Iterators
- Algorithms
- Strings
- Maps and Sets
- Bitset and Utility Functions
- IO Streams

### 2. [Data-Structures/](./Data-Structures/) - Custom Data Structures
Implementations of fundamental data structures:
- Arrays and Vectors
- Linked Lists (Singly, Doubly, Circular)
- Stacks and Queues
- Trees (Binary Trees, Binary Search Trees, AVL Trees)
- Graphs (Adjacency List, Adjacency Matrix)
- Hash Tables
- Heaps (Min-Heap, Max-Heap)
- Trie
- Disjoint Set Union (Union-Find)

### 3. [Algorithms/](./Algorithms/) - Algorithm Implementations
Comprehensive algorithm collection:
- Sorting Algorithms (Bubble, Selection, Insertion, Merge, Quick, Heap)
- Searching Algorithms (Linear, Binary, Jump, Interpolation)
- Recursion and Backtracking
- Dynamic Programming
- Greedy Algorithms
- Graph Algorithms (BFS, DFS, Dijkstra's, Floyd-Warshall, Kruskal's)
- String Algorithms (Pattern Matching, Manipulation)

### 4. [Dynamic-Programming/](./Dynamic-Programming/) - DP Problems
Classic dynamic programming problems with solutions:
- Fibonacci Numbers
- Longest Common Subsequence (LCS)
- Longest Increasing Subsequence (LIS)
- Knapsack Problems (0/1, Unbounded)
- Matrix Chain Multiplication
- Coin Change Problem
- Edit Distance

### 5. [Concepts/](./Concepts/) - C++ Fundamentals
Key C++ programming concepts:
- Object-Oriented Programming (OOP)
- Templates and Generics
- Memory Management (Stack vs Heap, Smart Pointers)
- Exception Handling
- File I/O Operations
- Lambda Functions and STL Algorithms
- Modern C++ Features (C++11 and beyond)

## Getting Started

### Prerequisites
- C++ compiler (GCC, Clang, MSVC)
- C++11 or later standard support
- Basic understanding of C++ programming

### Compilation and Execution

Each file in the repository is a complete, standalone program. To compile and run any example:

```bash
# Using GCC
g++ filename.cpp -o filename -std=c++11
./filename

# Using Clang
clang++ filename.cpp -o filename -std=c++11
./filename
```

## Learning Path

### Beginner Level
1. Start with [Concepts/](./Concepts/) - Understand C++ fundamentals
2. Explore [STL/](./STL/) - Learn about the standard library
3. Study [Data-Structures/](./Data-Structures/) - Implement basic data structures
4. Practice [Algorithms/](./Algorithms/) - Learn sorting and searching

### Intermediate Level
1. Dive into [Dynamic-Programming/](./Dynamic-Programming/)
2. Study graph and tree algorithms
3. Learn about advanced data structures (Trie, DSU, AVL Trees)

### Advanced Level
1. Master complex algorithmic techniques
2. Practice with competitive programming problems
3. Explore modern C++ features

## Example Programs

Each category contains well-commented, easy-to-understand examples. Here's a quick preview:

### STL Vector Example
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    
    // Add elements
    vec.push_back(6);
    vec.push_back(7);
    
    // Access elements
    cout << "First element: " << vec[0] << endl;
    cout << "Last element: " << vec.back() << endl;
    
    // Iterate through vector
    cout << "All elements: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Binary Search Tree Example
```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;
    
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }
    
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }
    
public:
    BST() : root(nullptr) {}
    
    void insert(int value) {
        root = insert(root, value);
    }
    
    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    
    cout << "Inorder traversal: ";
    tree.inorderTraversal();
    
    return 0;
}
```

## Contributing

Feel free to contribute to this repository by:
- Adding new algorithms or data structures
- Improving existing implementations
- Adding more detailed explanations
- Fixing any bugs

## License

This repository is open-source and available under the MIT License.

## Acknowledgments

This repository is inspired by various DSA resources and textbooks, with a focus on practical, hands-on implementation in C++.

## Contact

For any questions or suggestions, please feel free to reach out.

---

**Happy Coding!** 🚀
