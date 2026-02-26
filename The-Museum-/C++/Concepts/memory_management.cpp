/*
C++ Memory Management - Comprehensive Guide
============================================
This file demonstrates all aspects of memory management in C++ including:
- Stack vs Heap memory
- Dynamic memory allocation (new/delete)
- Smart pointers
- Memory leaks detection
- RAII (Resource Acquisition Is Initialization)
- Memory debugging and optimization
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

// =========================================================================
// 1. Stack vs Heap Memory Basics
// =========================================================================

int globalVar = 10; // Global memory

void stackMemoryExample() {
    cout << "=== Stack Memory Example ===\n";
    
    int stackVar = 20; // Stack memory
    cout << "Stack variable address: " << &stackVar << endl;
    cout << "Stack variable value: " << stackVar << endl;
    
    // Static local variable - static memory
    static int staticVar = 30;
    cout << "Static variable address: " << &staticVar << endl;
    cout << "Static variable value: " << staticVar << endl;
    
    cout << "Global variable address: " << &globalVar << endl;
    cout << "Global variable value: " << globalVar << endl;
    cout << endl;
}

// =========================================================================
// 2. Dynamic Memory Allocation (new/delete)
// =========================================================================

void dynamicMemoryExample() {
    cout << "=== Dynamic Memory Allocation ===\n";
    
    // Single variable
    int* dynamicInt = new int;
    *dynamicInt = 42;
    cout << "Dynamic int address: " << dynamicInt << endl;
    cout << "Dynamic int value: " << *dynamicInt << endl;
    
    // Single variable with initialization
    double* dynamicDouble = new double(3.14159);
    cout << "Dynamic double address: " << dynamicDouble << endl;
    cout << "Dynamic double value: " << *dynamicDouble << endl;
    
    // Array
    int* dynamicArray = new int[5];
    for (int i = 0; i < 5; ++i) {
        dynamicArray[i] = i * 10;
    }
    cout << "Dynamic array address: " << dynamicArray << endl;
    cout << "Dynamic array elements: ";
    for (int i = 0; i < 5; ++i) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;
    
    // 2D array
    int rows = 3, cols = 4;
    int** dynamic2DArray = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        dynamic2DArray[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            dynamic2DArray[i][j] = i * cols + j;
        }
    }
    cout << "Dynamic 2D array: " << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << dynamic2DArray[i][j] << " ";
        }
        cout << endl;
    }
    
    // Deallocation
    delete dynamicInt;
    delete dynamicDouble;
    delete[] dynamicArray;
    
    for (int i = 0; i < rows; ++i) {
        delete[] dynamic2DArray[i];
    }
    delete[] dynamic2DArray;
    
    cout << "Dynamic memory deallocated successfully\n" << endl;
}

// =========================================================================
// 3. Memory Leaks Demonstration
// =========================================================================

void memoryLeakExample() {
    cout << "=== Memory Leaks Demonstration ===\n";
    
    // Leak 1: Forgetting to delete single variable
    int* leak1 = new int(100);
    cout << "Leak 1: " << *leak1 << " at " << leak1 << " (not deleted)\n";
    
    // Leak 2: Forgetting to delete array
    int* leak2 = new int[10];
    cout << "Leak 2: Array at " << leak2 << " (not deleted)\n";
    
    // Leak 3: Exception before deletion
    try {
        int* leak3 = new int(200);
        cout << "Leak 3: " << *leak3 << " at " << leak3 << " (exception before delete)\n";
        throw runtime_error("Exception occurred");
        delete leak3; // Never called
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    cout << endl;
}

// =========================================================================
// 4. Smart Pointers (C++11 and later)
// =========================================================================

class Resource {
private:
    string name;
    
public:
    Resource(string name) : name(name) {
        cout << "Resource " << name << " created at " << this << endl;
    }
    
    ~Resource() {
        cout << "Resource " << name << " destroyed at " << this << endl;
    }
    
    void doWork() {
        cout << "Resource " << name << " working" << endl;
    }
    
    string getName() const {
        return name;
    }
};

void smartPointersExample() {
    cout << "=== Smart Pointers ===\n";
    
    // 4.1 Unique Pointer - sole ownership
    cout << "\n1. Unique Pointer:\n";
    unique_ptr<Resource> uniquePtr1 = make_unique<Resource>("Unique1");
    cout << "Unique pointer address: " << uniquePtr1.get() << endl;
    uniquePtr1->doWork();
    
    // Move semantics (can't copy unique_ptr)
    unique_ptr<Resource> uniquePtr2 = move(uniquePtr1);
    if (uniquePtr1 == nullptr) {
        cout << "uniquePtr1 is now null" << endl;
    }
    uniquePtr2->doWork();
    
    // 4.2 Shared Pointer - shared ownership
    cout << "\n2. Shared Pointer:\n";
    shared_ptr<Resource> sharedPtr1 = make_shared<Resource>("Shared1");
    cout << "Reference count: " << sharedPtr1.use_count() << endl;
    
    shared_ptr<Resource> sharedPtr2 = sharedPtr1; // Copy
    cout << "Reference count after copy: " << sharedPtr1.use_count() << endl;
    
    shared_ptr<Resource> sharedPtr3 = move(sharedPtr1); // Move
    cout << "Reference count after move: " << sharedPtr2.use_count() << endl;
    
    sharedPtr2->doWork();
    sharedPtr3->doWork();
    
    // 4.3 Weak Pointer - non-owning reference
    cout << "\n3. Weak Pointer:\n";
    weak_ptr<Resource> weakPtr = sharedPtr2;
    cout << "Weak pointer count: " << sharedPtr2.use_count() << endl;
    
    if (auto locked = weakPtr.lock()) { // Check if resource exists
        cout << "Locked weak pointer - Resource exists: " << locked->getName() << endl;
    }
    
    sharedPtr2.reset(); // Decrement reference count
    sharedPtr3.reset(); // Decrement reference count
    
    if (auto locked = weakPtr.lock()) {
        cout << "Resource still exists" << endl;
    } else {
        cout << "Resource has been destroyed" << endl;
    }
    
    cout << endl;
}

// =========================================================================
// 5. RAII - Resource Acquisition Is Initialization
// =========================================================================

class FileHandler {
private:
    FILE* file;
    string filename;
    
public:
    FileHandler(string filename) : filename(filename) {
        file = fopen(filename.c_str(), "w");
        if (file == nullptr) {
            throw runtime_error("Failed to open file");
        }
        cout << "File " << filename << " opened" << endl;
    }
    
    ~FileHandler() {
        if (file != nullptr) {
            fclose(file);
            cout << "File " << filename << " closed" << endl;
        }
    }
    
    void write(const string& data) {
        if (file != nullptr) {
            fprintf(file, "%s", data.c_str());
        }
    }
};

void raiiExample() {
    cout << "=== RAII - Resource Acquisition Is Initialization ===\n";
    
    try {
        FileHandler file1("test1.txt");
        file1.write("Hello, RAII!");
        cout << "Data written to file1.txt" << endl;
        
        FileHandler file2("test2.txt");
        file2.write("Another file with RAII");
        cout << "Data written to file2.txt" << endl;
        
        // Files are automatically closed when going out of scope
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;
}

// =========================================================================
// 6. Memory Management with Containers
// =========================================================================

void containersMemoryExample() {
    cout << "=== Memory Management with Containers ===\n";
    
    // Vector manages its own memory
    vector<int> dynamicVector;
    cout << "Initial size: " << dynamicVector.size() << endl;
    cout << "Initial capacity: " << dynamicVector.capacity() << endl;
    
    for (int i = 0; i < 10; ++i) {
        dynamicVector.push_back(i * 10);
        cout << "Size: " << dynamicVector.size() << ", Capacity: " << dynamicVector.capacity() << endl;
    }
    
    dynamicVector.reserve(20); // Preallocate space
    cout << "After reserve(20): Capacity " << dynamicVector.capacity() << endl;
    
    dynamicVector.shrink_to_fit(); // Reduce capacity to match size
    cout << "After shrink_to_fit(): Capacity " << dynamicVector.capacity() << endl;
    
    cout << "Vector elements: ";
    for (int num : dynamicVector) {
        cout << num << " ";
    }
    cout << endl;
    
    dynamicVector.clear(); // Removes all elements but doesn't deallocate memory
    cout << "After clear(): Size " << dynamicVector.size() << ", Capacity " << dynamicVector.capacity() << endl;
    
    vector<int>().swap(dynamicVector); // Swap with empty vector to deallocate
    cout << "After swap with empty vector: Size " << dynamicVector.size() << ", Capacity " << dynamicVector.capacity() << endl;
    cout << endl;
}

// =========================================================================
// 7. Memory Debugging Techniques
// =========================================================================

void memoryDebuggingExample() {
    cout << "=== Memory Debugging Techniques ===\n";
    
    // 7.1 Overflow detection
    cout << "\n1. Buffer Overflow Detection:\n";
    char buffer[5];
    sprintf(buffer, "1234567890"); // This will overflow the buffer!
    cout << "Buffer content: " << buffer << endl;
    cout << "(Note: This buffer overflow is intentional for demonstration)\n";
    
    // 7.2 Memory alignment
    cout << "\n2. Memory Alignment:\n";
    cout << "Size of int: " << sizeof(int) << endl;
    cout << "Size of long: " << sizeof(long) << endl;
    cout << "Size of double: " << sizeof(double) << endl;
    
    struct Misaligned {
        char c;
        double d;
        int i;
    };
    
    struct Aligned {
        double d;
        int i;
        char c;
    };
    
    cout << "Misaligned struct size: " << sizeof(Misaligned) << endl;
    cout << "Aligned struct size: " << sizeof(Aligned) << endl;
    
    // 7.3 Memory fragmentation
    cout << "\n3. Memory Fragmentation Example:\n";
    vector<void*> allocatedBlocks;
    
    for (int i = 0; i < 10; ++i) {
        void* block = malloc(1000); // Allocate 1KB blocks
        allocatedBlocks.push_back(block);
        cout << "Allocated block " << i << ": " << block << endl;
    }
    
    // Free every other block
    for (int i = 1; i < 10; i += 2) {
        free(allocatedBlocks[i]);
        cout << "Freed block " << i << endl;
    }
    
    // Allocate a larger block
    void* largeBlock = malloc(5000); // 5KB block
    if (largeBlock != nullptr) {
        cout << "Successfully allocated 5KB block: " << largeBlock << endl;
        free(largeBlock);
    } else {
        cout << "Failed to allocate 5KB block - memory fragmented" << endl;
    }
    
    // Clean up
    for (int i = 0; i < 10; i += 2) {
        free(allocatedBlocks[i]);
    }
    
    cout << endl;
}

// =========================================================================
// 8. Performance and Optimization
// =========================================================================

void performanceOptimization() {
    cout << "=== Memory Performance Optimization ===\n";
    
    // 8.1 Allocation patterns
    const int NUM_ALLOCATIONS = 1000000;
    
    // Stack allocation is faster
    cout << "\nStack allocation is fastest for known sizes\n";
    
    // Vector preallocation
    cout << "\n2. Vector Preallocation vs Reallocation:\n";
    vector<int> vec1;
    auto start = clock();
    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        vec1.push_back(i); // Will reallocate multiple times
    }
    auto end = clock();
    cout << "Without reserve: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
    
    vector<int> vec2;
    vec2.reserve(NUM_ALLOCATIONS);
    start = clock();
    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        vec2.push_back(i); // No reallocations
    }
    end = clock();
    cout << "With reserve: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
    
    // 8.2 Memory pool
    cout << "\n3. Memory Pool Concept:\n";
    vector<int*> pool;
    pool.reserve(NUM_ALLOCATIONS);
    
    start = clock();
    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        pool.push_back(new int(i));
    }
    for (int* ptr : pool) {
        delete ptr;
    }
    end = clock();
    cout << "Individual allocations: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
    
    start = clock();
    int* largeBlock = new int[NUM_ALLOCATIONS];
    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        largeBlock[i] = i;
    }
    delete[] largeBlock;
    end = clock();
    cout << "Single allocation: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
    
    // 8.3 Smart pointer performance
    cout << "\n4. Smart Pointer Performance:\n";
    start = clock();
    vector<unique_ptr<int>> uniquePtrVec;
    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        uniquePtrVec.push_back(make_unique<int>(i));
    }
    end = clock();
    cout << "Unique ptr: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
    
    start = clock();
    vector<shared_ptr<int>> sharedPtrVec;
    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        sharedPtrVec.push_back(make_shared<int>(i));
    }
    end = clock();
    cout << "Shared ptr: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
    
    cout << endl;
}

// =========================================================================
// 9. Memory Leak Detection with Valgrind
// =========================================================================

void valgrindExample() {
    cout << "=== Memory Leak Detection with Valgrind ===\n";
    cout << "Valgrind is a powerful memory debugging tool. To use:\n";
    cout << "1. Compile with -g flag: g++ -g memory_management.cpp -o memory_management\n";
    cout << "2. Run valgrind: valgrind --leak-check=yes ./memory_management\n";
    cout << "3. Look for 'HEAP SUMMARY' and 'LEAK SUMMARY' sections\n";
    cout << endl;
}

// =========================================================================
// Main Function for Testing
// =========================================================================
int main() {
    cout << "=== C++ Memory Management Comprehensive Example ===\n";
    
    try {
        // 1. Stack vs Heap basics
        stackMemoryExample();
        
        // 2. Dynamic memory allocation
        dynamicMemoryExample();
        
        // 3. Smart pointers
        smartPointersExample();
        
        // 4. RAII
        raiiExample();
        
        // 5. Containers memory management
        containersMemoryExample();
        
        // 6. Memory debugging and optimization
        memoryDebuggingExample();
        performanceOptimization();
        
        // 7. Valgrind usage
        valgrindExample();
        
        // 8. Memory leak example (comment out to avoid actual leaks)
        // memoryLeakExample();
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    cout << "=== All Tests Completed ===\n";
    return 0;
}

/*
Key Takeaways:

1. Memory Types:
   - Stack: Fast, automatic allocation/deallocation, fixed size, local variables
   - Heap: Manual allocation/deallocation, dynamic size, slower access
   - Static/Global: Persistent throughout program lifetime

2. Dynamic Memory Management:
   - new/delete: Allocate/deallocate single variables
   - new[]/delete[]: Allocate/deallocate arrays
   - Must always match new with delete, new[] with delete[]

3. Smart Pointers:
   - unique_ptr: Sole ownership, no copy, move semantics
   - shared_ptr: Shared ownership, reference counting
   - weak_ptr: Non-owning reference, doesn't affect lifetime
   - Prevents memory leaks by automatic cleanup

4. RAII (Resource Acquisition Is Initialization):
   - Encapsulates resource management within a class
   - Constructor acquires resource
   - Destructor releases resource
   - Handles exceptions automatically

5. Memory Debugging:
   - Valgrind: Detects leaks, buffer overflows, access violations
   - AddressSanitizer: Compile-time tool for memory error detection
   - LeakSanitizer: Focuses on leak detection

6. Performance Optimization:
   - Stack allocation for known sizes
   - Preallocate containers with reserve()
   - Use single allocation instead of multiple small allocations
   - Pool allocation for repeated similar allocations
   - unique_ptr is much faster than shared_ptr

7. Common Issues:
   - Memory leaks: Forgetting to delete dynamically allocated memory
   - Buffer overflows: Writing beyond buffer boundaries
   - Wild pointers: Accessing freed memory
   - Dangling pointers: Pointer pointing to deallocated memory
   - Double deletion: Deleting the same memory twice

8. Best Practices:
   - Prefer stack allocation over heap
   - Use smart pointers instead of raw pointers
   - Follow RAII pattern
   - Minimize dynamic allocation
   - Preallocate when possible
   - Use containers (vector, string) instead of raw arrays
   - Always check for nullptr before dereferencing
   - Use initializer lists for array initialization

9. Modern C++ Features:
   - make_unique, make_shared: Exception-safe allocation
   - vector: Automatically manages dynamic arrays
   - string: Dynamic string management
   - Optional: Safe nullable types

10. Memory Leak Detection Tools:
    - Valgrind (Linux)
    - AddressSanitizer (GCC/Clang)
    - LeakSanitizer (LLVM)
    - Dr. Memory (Windows)

Memory management in C++ is complex but powerful. Understanding these concepts
and using the right tools will help you write efficient and bug-free code.
*/
