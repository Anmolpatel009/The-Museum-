/*
C++ STL Vector Example - Comprehensive Guide
===========================================
This file demonstrates the usage of std::vector in C++ STL,
including all major operations and best practices.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cassert>

using namespace std;

// Function to print a vector with a label
void printVector(const vector<int>& vec, const string& label) {
    cout << label << ": ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== C++ STL Vector Comprehensive Example ===\n\n";
    
    // 1. Vector Initialization
    cout << "1. Vector Initialization Methods:\n";
    
    // Empty vector
    vector<int> vec1;
    cout << "   Empty vector: size = " << vec1.size() 
         << ", capacity = " << vec1.capacity() << endl;
    
    // Vector with 5 elements initialized to 0
    vector<int> vec2(5);
    cout << "   Vector with 5 zeros: size = " << vec2.size() 
         << ", capacity = " << vec2.capacity() << endl;
    
    // Vector with 3 elements initialized to 7
    vector<int> vec3(3, 7);
    printVector(vec3, "   Vector with 3 sevens");
    
    // Vector from initializer list
    vector<int> vec4 = {1, 2, 3, 4, 5};
    printVector(vec4, "   Vector from initializer list");
    
    // Vector from another vector
    vector<int> vec5(vec4);
    printVector(vec5, "   Vector from another vector");
    
    // Vector from array
    int arr[] = {10, 20, 30, 40};
    vector<int> vec6(arr, arr + sizeof(arr)/sizeof(arr[0]));
    printVector(vec6, "   Vector from array");
    
    cout << endl;
    
    // 2. Element Access
    cout << "2. Element Access Methods:\n";
    
    vector<int> vec = {10, 20, 30, 40, 50};
    
    // Direct access using [] operator (no bounds checking)
    cout << "   vec[0] = " << vec[0] << endl;
    cout << "   vec[4] = " << vec[4] << endl;
    
    // Access using at() method (with bounds checking)
    cout << "   vec.at(2) = " << vec.at(2) << endl;
    try {
        vec.at(10);  // This will throw an exception
    } catch (const out_of_range& e) {
        cout << "   vec.at(10) = Out of range exception caught" << endl;
    }
    
    // Front and back access
    cout << "   Front element: " << vec.front() << endl;
    cout << "   Back element: " << vec.back() << endl;
    
    // Data pointer access
    cout << "   Data pointer access: " << vec.data() << endl;
    cout << "   First element via data(): " << *vec.data() << endl;
    
    cout << endl;
    
    // 3. Capacity Operations
    cout << "3. Capacity Operations:\n";
    
    cout << "   Current size: " << vec.size() << endl;
    cout << "   Current capacity: " << vec.capacity() << endl;
    cout << "   Is empty? " << (vec.empty() ? "Yes" : "No") << endl;
    cout << "   Maximum size: " << vec.max_size() << endl;
    
    // Reserve capacity
    vec.reserve(10);
    cout << "   After reserve(10): size = " << vec.size() 
         << ", capacity = " << vec.capacity() << endl;
    
    // Shrink to fit
    vec.shrink_to_fit();
    cout << "   After shrink_to_fit(): size = " << vec.size() 
         << ", capacity = " << vec.capacity() << endl;
    
    cout << endl;
    
    // 4. Modification Operations
    cout << "4. Modification Operations:\n";
    
    printVector(vec, "   Original vector");
    
    // Push back elements
    vec.push_back(60);
    vec.push_back(70);
    printVector(vec, "   After push_back(60, 70)");
    
    // Pop back
    vec.pop_back();
    printVector(vec, "   After pop_back()");
    
    // Insert elements
    vec.insert(vec.begin() + 2, 25);  // Insert at index 2
    printVector(vec, "   After insert at index 2: 25");
    
    vec.insert(vec.end(), 3, 80);  // Insert 3 elements of 80 at end
    printVector(vec, "   After inserting 3 eights at end");
    
    vector<int> temp = {90, 100};
    vec.insert(vec.end(), temp.begin(), temp.end());
    printVector(vec, "   After inserting another vector");
    
    // Erase elements
    vec.erase(vec.begin() + 3);  // Erase index 3
    printVector(vec, "   After erase index 3");
    
    vec.erase(vec.begin() + 1, vec.begin() + 3);  // Erase range
    printVector(vec, "   After erase range [1, 3)");
    
    // Clear the vector
    vec.clear();
    cout << "   After clear(): size = " << vec.size() 
         << ", capacity = " << vec.capacity() << endl;
    cout << "   Is empty? " << (vec.empty() ? "Yes" : "No") << endl;
    
    cout << endl;
    
    // 5. Vector Operations and Algorithms
    cout << "5. Vector Operations and Algorithms:\n";
    
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    printVector(nums, "   Original numbers");
    
    // Sorting
    sort(nums.begin(), nums.end());
    printVector(nums, "   Sorted numbers");
    
    // Reverse
    reverse(nums.begin(), nums.end());
    printVector(nums, "   Reversed numbers");
    
    // Find element
    int target = 5;
    auto it = find(nums.begin(), nums.end(), target);
    if (it != nums.end()) {
        cout << "   Found " << target << " at position: " 
             << distance(nums.begin(), it) << endl;
    } else {
        cout << "   " << target << " not found" << endl;
    }
    
    // Count occurrences
    int count4 = count(nums.begin(), nums.end(), 4);
    cout << "   Number of 4's: " << count4 << endl;
    
    // Sum of elements
    int sum = accumulate(nums.begin(), nums.end(), 0);
    cout << "   Sum of elements: " << sum << endl;
    
    // Minimum and maximum
    auto minIt = min_element(nums.begin(), nums.end());
    auto maxIt = max_element(nums.begin(), nums.end());
    cout << "   Minimum element: " << *minIt << endl;
    cout << "   Maximum element: " << *maxIt << endl;
    
    // Remove duplicates
    sort(nums.begin(), nums.end());
    auto last = unique(nums.begin(), nums.end());
    nums.erase(last, nums.end());
    printVector(nums, "   After removing duplicates");
    
    cout << endl;
    
    // 6. Vector of Vectors (2D Vector)
    cout << "6. Vector of Vectors (2D Vector):\n";
    
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    cout << "   3x3 Matrix:\n";
    for (const vector<int>& row : matrix) {
        cout << "   ";
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    
    // Accessing elements
    cout << "   Element at (1, 1): " << matrix[1][1] << endl;
    
    // Adding a row
    matrix.push_back({10, 11, 12});
    cout << "   After adding a row:\n";
    for (const vector<int>& row : matrix) {
        cout << "   ";
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    
    cout << endl;
    
    // 7. Performance Considerations
    cout << "7. Performance Considerations:\n";
    
    vector<int> performanceVec;
    const int numElements = 100000;
    
    // Reserve capacity to avoid reallocations
    performanceVec.reserve(numElements);
    
    cout << "   Vector capacity before push_back: " 
         << performanceVec.capacity() << endl;
    
    // Add elements
    for (int i = 0; i < numElements; ++i) {
        performanceVec.push_back(i);
    }
    
    cout << "   After adding " << numElements << " elements:\n";
    cout << "   Size: " << performanceVec.size() << endl;
    cout << "   Capacity: " << performanceVec.capacity() << endl;
    
    cout << endl;
    
    cout << "=== Vector Example Completed ===\n";
    return 0;
}

/*
Key Takeaways:
1. Vectors are dynamic arrays with automatic resizing
2. Always reserve capacity if you know the required size beforehand
3. Prefer push_back() over insert() for efficiency
4. Use vector::at() for bounds-checked access
5. Vectors guarantee contiguous memory storage
6. When capacity is exhausted, vectors resize to 2x their current capacity
*/
