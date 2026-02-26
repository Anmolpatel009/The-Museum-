/*
C++ Searching Algorithms - Comprehensive Guide
===============================================
This file demonstrates various searching algorithms with implementations,
time complexity analysis, and practical examples.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>
#include <climits>
#include <map>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

// =========================================================================
// Helper Functions
// =========================================================================

// Print an array
template <typename T>
void printArray(const vector<T>& arr, const string& label) {
    cout << label << ": ";
    for (const T& element : arr) {
        cout << element << " ";
    }
    cout << endl;
}

// Generate random array
vector<int> generateRandomArray(int size, int minVal = 0, int maxVal = 1000, bool sorted = false) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minVal, maxVal);
    
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    
    if (sorted) {
        sort(arr.begin(), arr.end());
    }
    
    return arr;
}

// Measure time taken by searching algorithm
template <typename Func, typename T>
double measureTime(Func searchFunc, const vector<T>& arr, const T& target) {
    auto start = high_resolution_clock::now();
    searchFunc(arr, target);
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count() / 1e9;
}

// =========================================================================
// 1. Linear Search
// =========================================================================
template <typename T>
int linearSearch(const vector<T>& arr, const T& target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// =========================================================================
// 2. Binary Search (Iterative)
// =========================================================================
template <typename T>
int binarySearchIterative(const vector<T>& arr, const T& target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// =========================================================================
// 3. Binary Search (Recursive)
// =========================================================================
template <typename T>
int binarySearchRecursiveHelper(const vector<T>& arr, const T& target, int left, int right) {
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursiveHelper(arr, target, mid + 1, right);
    } else {
        return binarySearchRecursiveHelper(arr, target, left, mid - 1);
    }
}

template <typename T>
int binarySearchRecursive(const vector<T>& arr, const T& target) {
    return binarySearchRecursiveHelper(arr, target, 0, arr.size() - 1);
}

// =========================================================================
// 4. Jump Search
// =========================================================================
template <typename T>
int jumpSearch(const vector<T>& arr, const T& target) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;
    
    while (arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        
        if (prev >= n) {
            return -1;
        }
    }
    
    for (int i = prev; i < min(step, n); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    
    return -1;
}

// =========================================================================
// 5. Interpolation Search
// =========================================================================
template <typename T>
int interpolationSearch(const vector<T>& arr, const T& target) {
    int low = 0;
    int high = arr.size() - 1;
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) {
                return low;
            }
            return -1;
        }
        
        int pos = low + ((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]);
        
        if (arr[pos] == target) {
            return pos;
        }
        
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    return -1;
}

// =========================================================================
// 6. Exponential Search
// =========================================================================
template <typename T>
int exponentialSearch(const vector<T>& arr, const T& target) {
    int n = arr.size();
    
    if (arr[0] == target) {
        return 0;
    }
    
    int i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;
    }
    
    int left = i / 2;
    int right = min(i, n - 1);
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// =========================================================================
// 7. Fibonacci Search
// =========================================================================
template <typename T>
int fibonacciSearch(const vector<T>& arr, const T& target) {
    int n = arr.size();
    int fibM2 = 0; // (m-2)th Fibonacci number
    int fibM1 = 1; // (m-1)th Fibonacci number
    int fibM = fibM2 + fibM1; // mth Fibonacci number
    
    while (fibM < n) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }
    
    int offset = -1;
    
    while (fibM > 1) {
        int i = min(offset + fibM2, n - 1);
        
        if (arr[i] < target) {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        } else if (arr[i] > target) {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        } else {
            return i;
        }
    }
    
    if (fibM1 && offset + 1 < n && arr[offset + 1] == target) {
        return offset + 1;
    }
    
    return -1;
}

// =========================================================================
// 8. Ternary Search
// =========================================================================
template <typename T>
int ternarySearch(const vector<T>& arr, const T& target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        if (arr[mid1] == target) {
            return mid1;
        }
        
        if (arr[mid2] == target) {
            return mid2;
        }
        
        if (target < arr[mid1]) {
            right = mid1 - 1;
        } else if (target > arr[mid2]) {
            left = mid2 + 1;
        } else {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    
    return -1;
}

// =========================================================================
// 9. Hash Table Search
// =========================================================================
template <typename T>
int hashTableSearch(const vector<T>& arr, const T& target) {
    unordered_map<T, int> hashTable;
    
    for (int i = 0; i < arr.size(); ++i) {
        hashTable[arr[i]] = i;
    }
    
    auto it = hashTable.find(target);
    return (it != hashTable.end()) ? it->second : -1;
}

// =========================================================================
// 10. Binary Search Tree (BST) Search
// =========================================================================
template <typename T>
struct BSTNode {
    T data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
BSTNode<T>* createBST(const vector<T>& arr) {
    if (arr.empty()) {
        return nullptr;
    }
    
    BSTNode<T>* root = new BSTNode<T>(arr[0]);
    
    for (size_t i = 1; i < arr.size(); ++i) {
        BSTNode<T>* current = root;
        BSTNode<T>* parent = nullptr;
        
        while (current != nullptr) {
            parent = current;
            if (arr[i] < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        if (arr[i] < parent->data) {
            parent->left = new BSTNode<T>(arr[i]);
        } else {
            parent->right = new BSTNode<T>(arr[i]);
        }
    }
    
    return root;
}

template <typename T>
int bstSearchHelper(BSTNode<T>* root, const T& target, int index) {
    if (root == nullptr) {
        return -1;
    }
    
    if (root->data == target) {
        return index;
    } else if (target < root->data) {
        return bstSearchHelper(root->left, target, 2 * index + 1);
    } else {
        return bstSearchHelper(root->right, target, 2 * index + 2);
    }
}

template <typename T>
int bstSearch(const vector<T>& arr, const T& target) {
    if (arr.empty()) {
        return -1;
    }
    
    BSTNode<T>* root = createBST(arr);
    int result = bstSearchHelper(root, target, 0);
    
    return result;
}

// =========================================================================
// Performance Comparison
// =========================================================================
void compareSearchingAlgorithms() {
    const int sizes[] = {100, 1000, 5000, 10000, 50000, 100000};
    const string algorithms[] = {
        "Linear",
        "Binary Iterative",
        "Binary Recursive",
        "Jump",
        "Interpolation",
        "Exponential",
        "Fibonacci",
        "Ternary",
        "Hash Table",
        "BST"
    };
    
    cout << "=== Performance Comparison of Searching Algorithms ===\n";
    cout << "Size\tLinear\tBinaryIt\tBinaryRec\tJump\tInterp\tExponent\tFibonacci\tTernary\tHash\tBST\n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    
    for (int size : sizes) {
        cout << size << "\t";
        
        vector<int> arr = generateRandomArray(size, 0, size * 10, true);
        int target = arr[rand() % size];
        
        // Linear Search
        double time = measureTime(linearSearch<int>, arr, target);
        cout << time << "\t";
        
        // Binary Search (Iterative)
        time = measureTime(binarySearchIterative<int>, arr, target);
        cout << time << "\t\t";
        
        // Binary Search (Recursive)
        time = measureTime(binarySearchRecursive<int>, arr, target);
        cout << time << "\t\t";
        
        // Jump Search
        time = measureTime(jumpSearch<int>, arr, target);
        cout << time << "\t";
        
        // Interpolation Search
        time = measureTime(interpolationSearch<int>, arr, target);
        cout << time << "\t";
        
        // Exponential Search
        time = measureTime(exponentialSearch<int>, arr, target);
        cout << time << "\t\t";
        
        // Fibonacci Search
        time = measureTime(fibonacciSearch<int>, arr, target);
        cout << time << "\t\t";
        
        // Ternary Search
        time = measureTime(ternarySearch<int>, arr, target);
        cout << time << "\t";
        
        // Hash Table Search
        time = measureTime(hashTableSearch<int>, arr, target);
        cout << time << "\t";
        
        // BST Search
        time = measureTime(bstSearch<int>, arr, target);
        cout << time << "\n";
    }
    
    cout << endl;
}

// =========================================================================
// Main Function for Testing
// =========================================================================
int main() {
    cout << "=== C++ Searching Algorithms Comprehensive Example ===\n\n";
    
    // Test array
    vector<int> testArray = {64, 34, 25, 12, 22, 11, 90};
    vector<int> sortedArray = testArray;
    sort(sortedArray.begin(), sortedArray.end());
    int target = 22;
    
    printArray(testArray, "Original array");
    printArray(sortedArray, "Sorted array");
    cout << "Target to search: " << target << endl;
    cout << endl;
    
    // Test individual searching algorithms
    cout << "1. Testing Searching Algorithms:\n";
    
    // Linear Search
    int index = linearSearch(testArray, target);
    cout << "Linear Search: Index = " << index << endl;
    
    // Binary Search (Iterative)
    index = binarySearchIterative(sortedArray, target);
    cout << "Binary Search (Iterative): Index = " << index << endl;
    
    // Binary Search (Recursive)
    index = binarySearchRecursive(sortedArray, target);
    cout << "Binary Search (Recursive): Index = " << index << endl;
    
    // Jump Search
    index = jumpSearch(sortedArray, target);
    cout << "Jump Search: Index = " << index << endl;
    
    // Interpolation Search
    index = interpolationSearch(sortedArray, target);
    cout << "Interpolation Search: Index = " << index << endl;
    
    // Exponential Search
    index = exponentialSearch(sortedArray, target);
    cout << "Exponential Search: Index = " << index << endl;
    
    // Fibonacci Search
    index = fibonacciSearch(sortedArray, target);
    cout << "Fibonacci Search: Index = " << index << endl;
    
    // Ternary Search
    index = ternarySearch(sortedArray, target);
    cout << "Ternary Search: Index = " << index << endl;
    
    // Hash Table Search
    index = hashTableSearch(testArray, target);
    cout << "Hash Table Search: Index = " << index << endl;
    
    // BST Search
    index = bstSearch(testArray, target);
    cout << "BST Search: Index = " << index << endl;
    
    cout << endl;
    
    // Performance comparison
    cout << "2. Performance Comparison (time in seconds):\n";
    compareSearchingAlgorithms();
    
    cout << "3. Searching Random Arrays:\n";
    
    // Test with random array
    const int randomSize = 100000;
    vector<int> randomArray = generateRandomArray(randomSize, 0, randomSize * 10, true);
    cout << "Generated sorted random array with " << randomSize << " elements\n";
    
    int randomTarget = randomArray[rand() % randomSize];
    cout << "Searching for target: " << randomTarget << endl;
    
    double binaryTime = measureTime(binarySearchIterative<int>, randomArray, randomTarget);
    cout << "Binary Search time: " << binaryTime << " seconds\n";
    
    double linearTime = measureTime(linearSearch<int>, randomArray, randomTarget);
    cout << "Linear Search time: " << linearTime << " seconds\n";
    
    double ratio = linearTime / binaryTime;
    cout << "Binary Search is " << ratio << "x faster for " << randomSize << " elements\n";
    
    cout << endl;
    
    // Test with large array
    const int largeSize = 1000000;
    vector<int> largeArray = generateRandomArray(largeSize, 0, largeSize * 10, true);
    int largeTarget = largeArray[rand() % largeSize];
    
    double largeBinaryTime = measureTime(binarySearchIterative<int>, largeArray, largeTarget);
    cout << "Searching in " << largeSize << " elements:\n";
    cout << "Binary Search time: " << largeBinaryTime << " seconds\n";
    
    cout << endl;
    
    // Test not found
    int notFoundTarget = -1;
    int notFoundIndex = binarySearchIterative(sortedArray, notFoundTarget);
    cout << "Searching for non-existent element (" << notFoundTarget << "): Index = " << notFoundIndex << endl;
    
    cout << endl;
    
    cout << "=== All Tests Completed ===\n";
    return 0;
}

/*
Key Takeaways:

1. Time Complexity:
   - O(n): Linear (simple, works on any array)
   - O(log n): Binary (iterative/recursive), Jump, Exponential, Fibonacci, Ternary
   - O(log(log n)): Interpolation (best for uniformly distributed data)
   - O(1): Hash Table (average case)
   - O(h): BST (h is tree height, O(log n) for balanced BST)

2. Space Complexity:
   - O(1): Linear, Binary Iterative, Jump, Interpolation, Exponential, Fibonacci, Ternary
   - O(log n): Binary Recursive (call stack)
   - O(n): Hash Table, BST (storage)

3. Best Use Cases:
   - Linear: Small datasets, unsorted arrays, simple implementation
   - Binary: Large datasets, sorted arrays, known range
   - Interpolation: Uniformly distributed sorted data
   - Hash Table: Multiple searches, average O(1) time
   - BST: Dynamic datasets, insertion/deletion/search in O(log n) time

4. Algorithm Selection Tips:
   - For small n (<= 100): Use Linear Search (simple, fast enough)
   - For large n (1000+): Use Binary Search (O(log n) guaranteed)
   - For uniformly distributed data: Use Interpolation Search
   - For dynamic data: Use Hash Table or BST
   - For linked lists: Use Linear Search (only option)

5. Binary Search Variations:
   - Binary Search: Find exact match
   - Lower Bound: First occurrence >= target
   - Upper Bound: First occurrence > target
   - Equal Range: Range of elements == target

6. STL Searching Functions:
   - find(): Linear search for a value
   - binary_search(): Check if value exists in sorted range
   - lower_bound(): First element >= value
   - upper_bound(): First element > value
   - equal_range(): Pair of lower/upper bounds

7. Performance Comparison:
   - Binary Search is significantly faster than Linear for large datasets
   - Hash Table provides O(1) average time but has higher memory overhead
   - Interpolation Search can be faster than Binary if data is uniformly distributed

8. Edge Cases:
   - Empty array: Return -1
   - Single element: Check and return
   - Duplicate elements: Various algorithms handle differently
   - Target not found: Return -1

9. Implementation Tips:
   - Use binary search on sorted data only
   - Calculate mid as left + (right - left)/2 to avoid overflow
   - Handle edge cases (empty array, single element)
   - For binary search, ensure the array is properly sorted
*/
