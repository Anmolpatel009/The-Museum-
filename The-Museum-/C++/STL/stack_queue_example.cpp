/*
C++ STL Stack, Queue, and Priority Queue Example
================================================
This file demonstrates the usage of stack, queue, and priority_queue
in C++ STL, including all major operations and best practices.
*/

#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <functional>

using namespace std;

// Function to print a stack (inefficient but demonstrative)
template <typename T>
void printStack(stack<T> st) {
    cout << "Stack contents: ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

// Function to print a queue (inefficient but demonstrative)
template <typename T>
void printQueue(queue<T> q) {
    cout << "Queue contents: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

// Function to print a priority queue (inefficient but demonstrative)
template <typename T>
void printPriorityQueue(priority_queue<T> pq) {
    cout << "Priority Queue contents: ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}

int main() {
    cout << "=== C++ STL Stack, Queue, and Priority Queue Example ===\n\n";
    
    // =========================================================================
    // 1. Stack Example (LIFO - Last In First Out)
    // =========================================================================
    cout << "1. Stack Operations (LIFO):\n";
    
    stack<int> st;
    
    // Push elements onto stack
    st.push(10);
    st.push(20);
    st.push(30);
    st.push(40);
    st.push(50);
    cout << "   After push operations:\n";
    printStack(st);
    
    // Stack properties
    cout << "   Stack size: " << st.size() << endl;
    cout << "   Is stack empty? " << (st.empty() ? "Yes" : "No") << endl;
    cout << "   Top element: " << st.top() << endl;
    
    // Pop elements from stack
    st.pop();
    cout << "   After pop operation:\n";
    printStack(st);
    
    // Empty the stack
    while (!st.empty()) {
        st.pop();
    }
    cout << "   After emptying stack:\n";
    cout << "   Stack size: " << st.size() << endl;
    cout << "   Is stack empty? " << (st.empty() ? "Yes" : "No") << endl;
    
    cout << endl;
    
    // =========================================================================
    // 2. Queue Example (FIFO - First In First Out)
    // =========================================================================
    cout << "2. Queue Operations (FIFO):\n";
    
    queue<string> q;
    
    // Enqueue elements
    q.push("Apple");
    q.push("Banana");
    q.push("Cherry");
    q.push("Date");
    cout << "   After enqueue operations:\n";
    printQueue(q);
    
    // Queue properties
    cout << "   Queue size: " << q.size() << endl;
    cout << "   Is queue empty? " << (q.empty() ? "Yes" : "No") << endl;
    cout << "   Front element: " << q.front() << endl;
    cout << "   Back element: " << q.back() << endl;
    
    // Dequeue element
    q.pop();
    cout << "   After dequeue operation:\n";
    printQueue(q);
    
    // Empty the queue
    while (!q.empty()) {
        q.pop();
    }
    cout << "   After emptying queue:\n";
    cout << "   Queue size: " << q.size() << endl;
    cout << "   Is queue empty? " << (q.empty() ? "Yes" : "No") << endl;
    
    cout << endl;
    
    // =========================================================================
    // 3. Priority Queue Example (Heap-based)
    // =========================================================================
    cout << "3. Priority Queue Operations (Max-Heap by default):\n";
    
    priority_queue<int> pq;
    
    // Push elements
    pq.push(30);
    pq.push(10);
    pq.push(50);
    pq.push(20);
    pq.push(40);
    cout << "   After push operations:\n";
    printPriorityQueue(pq);
    
    // Priority queue properties
    cout << "   Priority queue size: " << pq.size() << endl;
    cout << "   Is priority queue empty? " << (pq.empty() ? "Yes" : "No") << endl;
    cout << "   Top element: " << pq.top() << endl;
    
    // Pop elements
    pq.pop();
    cout << "   After pop operation:\n";
    printPriorityQueue(pq);
    
    // Empty the priority queue
    while (!pq.empty()) {
        pq.pop();
    }
    cout << "   After emptying priority queue:\n";
    cout << "   Priority queue size: " << pq.size() << endl;
    cout << "   Is priority queue empty? " << (pq.empty() ? "Yes" : "No") << endl;
    
    cout << endl;
    
    // =========================================================================
    // 4. Min-Heap Priority Queue
    // =========================================================================
    cout << "4. Min-Heap Priority Queue:\n";
    
    // Using greater<> to create a min-heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(50);
    minHeap.push(20);
    minHeap.push(40);
    cout << "   After push operations:\n";
    
    // Print min-heap
    priority_queue<int, vector<int>, greater<int>> tempMinHeap = minHeap;
    cout << "   Min-heap contents: ";
    while (!tempMinHeap.empty()) {
        cout << tempMinHeap.top() << " ";
        tempMinHeap.pop();
    }
    cout << endl;
    
    cout << "   Top element (minimum): " << minHeap.top() << endl;
    
    cout << endl;
    
    // =========================================================================
    // 5. Queue with Custom Container (Deque)
    // =========================================================================
    cout << "5. Queue with Custom Container (Deque):\n";
    
    deque<string> dq = {"First", "Second", "Third"};
    queue<string, deque<string>> customQueue(dq);
    
    cout << "   Initial queue from deque:\n";
    printQueue(customQueue);
    
    customQueue.push("Fourth");
    customQueue.push("Fifth");
    cout << "   After pushing elements:\n";
    printQueue(customQueue);
    
    cout << endl;
    
    // =========================================================================
    // 6. Stack with Custom Container (Vector)
    // =========================================================================
    cout << "6. Stack with Custom Container (Vector):\n";
    
    vector<int> vec = {1, 2, 3};
    stack<int, vector<int>> customStack(vec);
    
    cout << "   Initial stack from vector:\n";
    printStack(customStack);
    
    customStack.push(4);
    customStack.push(5);
    cout << "   After pushing elements:\n";
    printStack(customStack);
    
    cout << endl;
    
    // =========================================================================
    // 7. Practical Examples
    // =========================================================================
    cout << "7. Practical Examples:\n";
    
    // Example 1: Check for balanced parentheses using stack
    cout << "   Example 1: Check if parentheses are balanced\n";
    
    string expression1 = "(a + b) * (c - d)";
    string expression2 = "((a + b) * (c - d";
    
    auto isBalanced = [](const string& str) {
        stack<char> st;
        for (char c : str) {
            if (c == '(') {
                st.push(c);
            } else if (c == ')') {
                if (st.empty()) {
                    return false;
                }
                st.pop();
            }
        }
        return st.empty();
    };
    
    cout << "   Expression 1: " << expression1 << endl;
    cout << "   Balanced: " << (isBalanced(expression1) ? "Yes" : "No") << endl;
    cout << "   Expression 2: " << expression2 << endl;
    cout << "   Balanced: " << (isBalanced(expression2) ? "Yes" : "No") << endl;
    
    cout << endl;
    
    // Example 2: Reverse a string using stack
    cout << "   Example 2: Reverse a string using stack\n";
    
    string original = "Hello World!";
    stack<char> charStack;
    
    for (char c : original) {
        charStack.push(c);
    }
    
    string reversed;
    while (!charStack.empty()) {
        reversed += charStack.top();
        charStack.pop();
    }
    
    cout << "   Original: " << original << endl;
    cout << "   Reversed: " << reversed << endl;
    
    cout << endl;
    
    // =========================================================================
    // 8. Complex Data Types
    // =========================================================================
    cout << "8. Complex Data Types:\n";
    
    // Stack of vectors
    stack<vector<int>> stackOfVectors;
    stackOfVectors.push({1, 2, 3});
    stackOfVectors.push({4, 5});
    stackOfVectors.push({6});
    
    cout << "   Stack of vectors:\n";
    stack<vector<int>> tempStack = stackOfVectors;
    while (!tempStack.empty()) {
        cout << "   ";
        for (int num : tempStack.top()) {
            cout << num << " ";
        }
        cout << endl;
        tempStack.pop();
    }
    
    cout << endl;
    
    // Priority queue of strings (lexicographical order)
    priority_queue<string> stringPriorityQueue;
    stringPriorityQueue.push("Banana");
    stringPriorityQueue.push("Apple");
    stringPriorityQueue.push("Cherry");
    stringPriorityQueue.push("Date");
    
    cout << "   Priority queue of strings:\n";
    priority_queue<string> tempStringPQ = stringPriorityQueue;
    while (!tempStringPQ.empty()) {
        cout << "   " << tempStringPQ.top() << endl;
        tempStringPQ.pop();
    }
    
    cout << endl;
    
    // =========================================================================
    // 9. Performance Comparison
    // =========================================================================
    cout << "9. Performance Comparison:\n";
    
    const int numOperations = 1000000;
    
    // Measure stack performance
    clock_t start = clock();
    stack<int> performanceStack;
    for (int i = 0; i < numOperations; ++i) {
        performanceStack.push(i);
    }
    while (!performanceStack.empty()) {
        performanceStack.pop();
    }
    double stackTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "   Stack operations (" << numOperations << " push/pop): " 
         << stackTime << " seconds\n";
    
    // Measure queue performance
    start = clock();
    queue<int> performanceQueue;
    for (int i = 0; i < numOperations; ++i) {
        performanceQueue.push(i);
    }
    while (!performanceQueue.empty()) {
        performanceQueue.pop();
    }
    double queueTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "   Queue operations (" << numOperations << " push/pop): " 
         << queueTime << " seconds\n";
    
    // Measure priority queue performance
    start = clock();
    priority_queue<int> performancePQ;
    for (int i = 0; i < numOperations; ++i) {
        performancePQ.push(i);
    }
    while (!performancePQ.empty()) {
        performancePQ.pop();
    }
    double pqTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "   Priority queue operations (" << numOperations << " push/pop): " 
         << pqTime << " seconds\n";
    
    cout << endl;
    
    cout << "=== Example Completed ===\n";
    return 0;
}

/*
Key Takeaways:
1. Stack: LIFO structure, O(1) push/pop, no iteration
2. Queue: FIFO structure, O(1) push/pop, no iteration
3. Priority Queue: Heap-based, O(log n) push/pop, always accesses top element
4. Use stack for expression evaluation, parentheses balancing
5. Use queue for BFS, task scheduling
6. Use priority queue for scheduling, finding min/max in dynamic data
7. All are container adapters that use other containers internally (default: deque for stack/queue, vector for priority_queue)
*/
