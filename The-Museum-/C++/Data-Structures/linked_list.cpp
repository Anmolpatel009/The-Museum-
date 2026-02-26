/*
C++ Linked List Implementation - Comprehensive Guide
====================================================
This file demonstrates implementations of singly linked list,
doubly linked list, and circular linked list in C++.
*/

#include <iostream>
#include <stdexcept>

using namespace std;

// =========================================================================
// 1. Singly Linked List Implementation
// =========================================================================
template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t size;
    
public:
    // Constructor
    SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Destructor
    ~SinglyLinkedList() {
        clear();
    }
    
    // Check if list is empty
    bool isEmpty() const {
        return size == 0;
    }
    
    // Get current size
    size_t getSize() const {
        return size;
    }
    
    // Add element to front
    void pushFront(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    
    // Add element to back
    void pushBack(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    // Add element at specific position (0-based)
    void insertAt(size_t index, const T& value) {
        if (index > size) {
            throw out_of_range("Index out of bounds");
        }
        
        if (index == 0) {
            pushFront(value);
            return;
        }
        
        if (index == size) {
            pushBack(value);
            return;
        }
        
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        
        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
    
    // Remove element from front
    void popFront() {
        if (isEmpty()) {
            throw out_of_range("List is empty");
        }
        
        Node* temp = head;
        head = head->next;
        delete temp;
        
        size--;
        
        if (isEmpty()) {
            tail = nullptr;
        }
    }
    
    // Remove element from back
    void popBack() {
        if (isEmpty()) {
            throw out_of_range("List is empty");
        }
        
        if (size == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        
        size--;
    }
    
    // Remove element at specific position (0-based)
    void removeAt(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of bounds");
        }
        
        if (index == 0) {
            popFront();
            return;
        }
        
        if (index == size - 1) {
            popBack();
            return;
        }
        
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
    }
    
    // Get element at specific position (0-based)
    T& getAt(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of bounds");
        }
        
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        
        return current->data;
    }
    
    // Find first occurrence of value
    size_t find(const T& value) const {
        Node* current = head;
        size_t index = 0;
        
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        
        return size; // Not found
    }
    
    // Clear all elements
    void clear() {
        while (!isEmpty()) {
            popFront();
        }
    }
    
    // Reverse the list
    void reverse() {
        if (size <= 1) {
            return;
        }
        
        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;
        
        while (current != nullptr) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        
        swap(head, tail);
    }
    
    // Print the list
    void print() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* current = head;
        cout << "Singly Linked List: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// =========================================================================
// 2. Doubly Linked List Implementation
// =========================================================================
template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t size;
    
public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Destructor
    ~DoublyLinkedList() {
        clear();
    }
    
    // Check if list is empty
    bool isEmpty() const {
        return size == 0;
    }
    
    // Get current size
    size_t getSize() const {
        return size;
    }
    
    // Add element to front
    void pushFront(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    
    // Add element to back
    void pushBack(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    // Add element at specific position (0-based)
    void insertAt(size_t index, const T& value) {
        if (index > size) {
            throw out_of_range("Index out of bounds");
        }
        
        if (index == 0) {
            pushFront(value);
            return;
        }
        
        if (index == size) {
            pushBack(value);
            return;
        }
        
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        
        Node* newNode = new Node(value);
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        size++;
    }
    
    // Remove element from front
    void popFront() {
        if (isEmpty()) {
            throw out_of_range("List is empty");
        }
        
        Node* temp = head;
        head = head->next;
        
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        
        delete temp;
        size--;
    }
    
    // Remove element from back
    void popBack() {
        if (isEmpty()) {
            throw out_of_range("List is empty");
        }
        
        Node* temp = tail;
        tail = tail->prev;
        
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        
        delete temp;
        size--;
    }
    
    // Remove element at specific position (0-based)
    void removeAt(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of bounds");
        }
        
        if (index == 0) {
            popFront();
            return;
        }
        
        if (index == size - 1) {
            popBack();
            return;
        }
        
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
    }
    
    // Get element at specific position (0-based)
    T& getAt(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of bounds");
        }
        
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        
        return current->data;
    }
    
    // Find first occurrence of value
    size_t find(const T& value) const {
        Node* current = head;
        size_t index = 0;
        
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        
        return size; // Not found
    }
    
    // Clear all elements
    void clear() {
        while (!isEmpty()) {
            popFront();
        }
    }
    
    // Reverse the list
    void reverse() {
        if (size <= 1) {
            return;
        }
        
        Node* current = head;
        Node* temp = nullptr;
        
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        
        swap(head, tail);
    }
    
    // Print the list
    void print() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* current = head;
        cout << "Doubly Linked List: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    // Print list in reverse order (using prev pointers)
    void printReverse() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* current = tail;
        cout << "Reverse Doubly Linked List: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

// =========================================================================
// 3. Circular Singly Linked List Implementation
// =========================================================================
template <typename T>
class CircularLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    size_t size;
    
public:
    // Constructor
    CircularLinkedList() : head(nullptr), size(0) {}
    
    // Destructor
    ~CircularLinkedList() {
        clear();
    }
    
    // Check if list is empty
    bool isEmpty() const {
        return size == 0;
    }
    
    // Get current size
    size_t getSize() const {
        return size;
    }
    
    // Add element to front
    void pushFront(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = newNode;
            head->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            newNode->next = head;
            temp->next = newNode;
            head = newNode;
        }
        size++;
    }
    
    // Add element to back
    void pushBack(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = newNode;
            head->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
        size++;
    }
    
    // Remove element from front
    void popFront() {
        if (isEmpty()) {
            throw out_of_range("List is empty");
        }
        
        if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            Node* toDelete = head;
            head = head->next;
            temp->next = head;
            delete toDelete;
        }
        size--;
    }
    
    // Remove element from back
    void popBack() {
        if (isEmpty()) {
            throw out_of_range("List is empty");
        }
        
        if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            while (temp->next->next != head) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = head;
        }
        size--;
    }
    
    // Print the list
    void print() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* current = head;
        cout << "Circular Linked List: ";
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }
    
    // Clear all elements
    void clear() {
        while (!isEmpty()) {
            popFront();
        }
    }
};

// =========================================================================
// 4. Main Function for Testing
// =========================================================================
int main() {
    cout << "=== C++ Linked List Implementation Example ===\n\n";
    
    // Test Singly Linked List
    cout << "1. Testing Singly Linked List:\n";
    SinglyLinkedList<int> singlyList;
    singlyList.pushBack(10);
    singlyList.pushBack(20);
    singlyList.pushFront(5);
    singlyList.print();
    cout << "Size: " << singlyList.getSize() << endl;
    
    singlyList.insertAt(2, 15);
    singlyList.print();
    
    cout << "Element at index 2: " << singlyList.getAt(2) << endl;
    cout << "Finding 20: index = " << singlyList.find(20) << endl;
    
    singlyList.popFront();
    singlyList.popBack();
    singlyList.print();
    
    singlyList.reverse();
    singlyList.print();
    
    cout << endl;
    
    // Test Doubly Linked List
    cout << "2. Testing Doubly Linked List:\n";
    DoublyLinkedList<string> doublyList;
    doublyList.pushBack("Apple");
    doublyList.pushBack("Banana");
    doublyList.pushFront("Cherry");
    doublyList.print();
    
    doublyList.insertAt(1, "Date");
    doublyList.print();
    doublyList.printReverse();
    
    cout << "Size: " << doublyList.getSize() << endl;
    cout << "Element at index 2: " << doublyList.getAt(2) << endl;
    
    doublyList.removeAt(1);
    doublyList.print();
    
    cout << endl;
    
    // Test Circular Linked List
    cout << "3. Testing Circular Linked List:\n";
    CircularLinkedList<double> circularList;
    circularList.pushBack(1.5);
    circularList.pushBack(2.5);
    circularList.pushFront(0.5);
    circularList.print();
    
    cout << "Size: " << circularList.getSize() << endl;
    
    circularList.popFront();
    circularList.popBack();
    circularList.print();
    
    cout << endl;
    
    cout << "=== All Tests Completed ===\n";
    return 0;
}

/*
Key Takeaways:
1. Singly Linked List: Each node has next pointer, O(1) front operations, O(n) middle/back operations
2. Doubly Linked List: Each node has prev and next pointers, O(1) operations at both ends
3. Circular Linked List: Last node points back to first, useful for circular buffers
4. All implementations include common operations: insert, remove, find, reverse, clear
5. Always manage memory properly in linked list implementations to avoid leaks
6. Linked lists offer dynamic memory allocation and efficient insertions/deletions
7. Random access is O(n) compared to O(1) for arrays
*/
