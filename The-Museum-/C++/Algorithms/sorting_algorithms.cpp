/*
C++ Sorting Algorithms - Comprehensive Guide
=============================================
This file demonstrates various sorting algorithms with implementations,
time complexity analysis, and practical examples.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <climits>

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
vector<int> generateRandomArray(int size, int minVal = 0, int maxVal = 1000) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minVal, maxVal);
    
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    
    return arr;
}

// Measure time taken by sorting algorithm
template <typename Func>
double measureTime(Func sortingFunc, vector<int>& arr) {
    auto start = high_resolution_clock::now();
    sortingFunc(arr);
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count() / 1e9;
}

// Check if array is sorted
template <typename T>
bool isSorted(const vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// =========================================================================
// 1. Bubble Sort
// =========================================================================
template <typename T>
void bubbleSort(vector<T>& arr) {
    int n = arr.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) {
            break;
        }
    }
}

// =========================================================================
// 2. Selection Sort
// =========================================================================
template <typename T>
void selectionSort(vector<T>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
    }
}

// =========================================================================
// 3. Insertion Sort
// =========================================================================
template <typename T>
void insertionSort(vector<T>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}

// =========================================================================
// 4. Merge Sort
// =========================================================================
template <typename T>
void merge(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<T> L(n1);
    vector<T> R(n2);
    
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

template <typename T>
void mergeSort(vector<T>& arr) {
    if (arr.size() <= 1) {
        return;
    }
    mergeSort(arr, 0, arr.size() - 1);
}

// =========================================================================
// 5. Quick Sort
// =========================================================================
template <typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void quickSort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template <typename T>
void quickSort(vector<T>& arr) {
    if (arr.size() <= 1) {
        return;
    }
    quickSort(arr, 0, arr.size() - 1);
}

// =========================================================================
// 6. Heap Sort
// =========================================================================
template <typename T>
void heapify(vector<T>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template <typename T>
void heapSort(vector<T>& arr) {
    int n = arr.size();
    
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// =========================================================================
// 7. Shell Sort
// =========================================================================
template <typename T>
void shellSort(vector<T>& arr) {
    int n = arr.size();
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            T temp = arr[i];
            int j;
            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            
            arr[j] = temp;
        }
    }
}

// =========================================================================
// 8. Counting Sort
// =========================================================================
void countingSort(vector<int>& arr) {
    if (arr.empty()) {
        return;
    }
    
    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    
    for (int num : arr) {
        if (num < minVal) {
            minVal = num;
        }
        if (num > maxVal) {
            maxVal = num;
        }
    }
    
    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);
    vector<int> output(arr.size());
    
    for (int num : arr) {
        count[num - minVal]++;
    }
    
    for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }
    
    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }
    
    arr = output;
}

// =========================================================================
// 9. Radix Sort
// =========================================================================
int getMax(const vector<int>& arr) {
    int maxVal = arr[0];
    for (int num : arr) {
        if (num > maxVal) {
            maxVal = num;
        }
    }
    return maxVal;
}

void countSortForRadix(vector<int>& arr, int exp) {
    vector<int> output(arr.size());
    vector<int> count(10, 0);
    
    for (int num : arr) {
        count[(num / exp) % 10]++;
    }
    
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }
    
    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    arr = output;
}

void radixSort(vector<int>& arr) {
    if (arr.empty()) {
        return;
    }
    
    int maxVal = getMax(arr);
    
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countSortForRadix(arr, exp);
    }
}

// =========================================================================
// 10. Bucket Sort
// =========================================================================
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    vector<vector<float>> buckets(n);
    
    for (float num : arr) {
        int bucketIdx = n * num;
        buckets[bucketIdx].push_back(num);
    }
    
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
    }
    
    int index = 0;
    for (const auto& bucket : buckets) {
        for (float num : bucket) {
            arr[index++] = num;
        }
    }
}

// =========================================================================
// 11. Tim Sort (C++ STL sort)
// =========================================================================
template <typename T>
void timSort(vector<T>& arr) {
    sort(arr.begin(), arr.end());
}

// =========================================================================
// Performance Comparison
// =========================================================================
void compareSortingAlgorithms() {
    const int sizes[] = {100, 1000, 5000, 10000};
    const string algorithms[] = {
        "Bubble Sort",
        "Selection Sort",
        "Insertion Sort",
        "Merge Sort",
        "Quick Sort",
        "Heap Sort",
        "Shell Sort",
        "Counting Sort",
        "Radix Sort",
        "Tim Sort (STL)"
    };
    
    cout << "=== Performance Comparison of Sorting Algorithms ===\n";
    cout << "Size\tBubble\tSelect\tInsert\tMerge\tQuick\tHeap\tShell\tCount\tRadix\tTim\n";
    cout << "---------------------------------------------------------------------------\n";
    
    for (int size : sizes) {
        cout << size << "\t";
        
        vector<int> arr = generateRandomArray(size);
        
        // Bubble Sort
        vector<int> temp = arr;
        double time = measureTime(bubbleSort<int>, temp);
        cout << time << "\t";
        
        // Selection Sort
        temp = arr;
        time = measureTime(selectionSort<int>, temp);
        cout << time << "\t";
        
        // Insertion Sort
        temp = arr;
        time = measureTime(insertionSort<int>, temp);
        cout << time << "\t";
        
        // Merge Sort
        temp = arr;
        time = measureTime(mergeSort<int>, temp);
        cout << time << "\t";
        
        // Quick Sort
        temp = arr;
        time = measureTime(quickSort<int>, temp);
        cout << time << "\t";
        
        // Heap Sort
        temp = arr;
        time = measureTime(heapSort<int>, temp);
        cout << time << "\t";
        
        // Shell Sort
        temp = arr;
        time = measureTime(shellSort<int>, temp);
        cout << time << "\t";
        
        // Counting Sort
        temp = arr;
        time = measureTime(countingSort, temp);
        cout << time << "\t";
        
        // Radix Sort
        temp = arr;
        time = measureTime(radixSort, temp);
        cout << time << "\t";
        
        // Tim Sort (STL)
        temp = arr;
        time = measureTime(timSort<int>, temp);
        cout << time << "\n";
    }
    
    cout << endl;
}

// =========================================================================
// Main Function for Testing
// =========================================================================
int main() {
    cout << "=== C++ Sorting Algorithms Comprehensive Example ===\n\n";
    
    // Test array
    vector<int> testArray = {64, 34, 25, 12, 22, 11, 90};
    printArray(testArray, "Original array");
    
    cout << endl;
    
    // Test individual sorting algorithms
    cout << "1. Testing Sorting Algorithms:\n";
    
    vector<int> arr;
    
    // Bubble Sort
    arr = testArray;
    bubbleSort(arr);
    printArray(arr, "Bubble Sort");
    
    // Selection Sort
    arr = testArray;
    selectionSort(arr);
    printArray(arr, "Selection Sort");
    
    // Insertion Sort
    arr = testArray;
    insertionSort(arr);
    printArray(arr, "Insertion Sort");
    
    // Merge Sort
    arr = testArray;
    mergeSort(arr);
    printArray(arr, "Merge Sort");
    
    // Quick Sort
    arr = testArray;
    quickSort(arr);
    printArray(arr, "Quick Sort");
    
    // Heap Sort
    arr = testArray;
    heapSort(arr);
    printArray(arr, "Heap Sort");
    
    // Shell Sort
    arr = testArray;
    shellSort(arr);
    printArray(arr, "Shell Sort");
    
    cout << endl;
    
    // Test counting, radix, and bucket sort
    cout << "2. Specialized Sorting Algorithms:\n";
    
    // Counting Sort
    vector<int> countingTest = {4, 2, 2, 8, 3, 3, 1};
    countingSort(countingTest);
    printArray(countingTest, "Counting Sort");
    
    // Radix Sort
    vector<int> radixTest = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(radixTest);
    printArray(radixTest, "Radix Sort");
    
    // Bucket Sort
    vector<float> bucketTest = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    bucketSort(bucketTest);
    printArray(bucketTest, "Bucket Sort");
    
    cout << endl;
    
    // Performance comparison
    cout << "3. Performance Comparison (time in seconds):\n";
    compareSortingAlgorithms();
    
    cout << "4. Sorting Random Arrays:\n";
    
    // Test with random array
    const int randomSize = 1000;
    vector<int> randomArray = generateRandomArray(randomSize);
    cout << "Generated random array with " << randomSize << " elements\n";
    
    // Check if sorted
    vector<int> sortedArray = randomArray;
    timSort(sortedArray);
    cout << "Is sorted correctly? " << (isSorted(sortedArray) ? "Yes" : "No") << endl;
    
    // Check stability
    vector<pair<int, int>> stableTest = {{4, 1}, {2, 2}, {2, 3}, {8, 4}, {3, 5}, {3, 6}, {1, 7}};
    vector<pair<int, int>> stableTestCopy = stableTest;
    stable_sort(stableTest.begin(), stableTest.end());
    
    cout << "Stable sort preserves order of equal elements: ";
    bool stable = true;
    for (size_t i = 0; i < stableTest.size() && i < stableTestCopy.size(); ++i) {
        if (stableTest[i].first == stableTestCopy[i].first && stableTest[i].second != stableTestCopy[i].second) {
            stable = false;
            break;
        }
    }
    cout << (stable ? "Yes" : "No") << endl;
    
    cout << endl;
    
    cout << "=== All Tests Completed ===\n";
    return 0;
}

/*
Key Takeaways:

1. Time Complexity:
   - O(n²): Bubble, Selection, Insertion (simple algorithms, bad for large data)
   - O(n log n): Merge, Quick, Heap, Shell (efficient for large data)
   - O(n + k): Counting, Radix, Bucket (linear time for specific cases)
   - O(n log n): Tim Sort (STL, hybrid, very efficient)

2. Space Complexity:
   - O(1): Bubble, Selection, Insertion, Heap, Shell (in-place)
   - O(n): Merge (requires additional space)
   - O(log n): Quick (recursive stack)
   - O(n + k): Counting, Radix, Bucket (requires additional space)

3. Stability:
   - Stable: Bubble, Insertion, Merge, Counting, Radix, Bucket (preserve order of equal elements)
   - Unstable: Selection, Quick, Heap (may reorder equal elements)

4. Best Use Cases:
   - Bubble/Selection/Insertion: Small datasets (n < 100)
   - Merge: Large datasets, stability required, linked lists
   - Quick: General purpose, fastest average case
   - Heap: Large datasets, need for in-place sorting
   - Counting: Integer data, small range
   - Radix: Non-comparative, integer data with fixed number of digits
   - Bucket: Floating-point numbers, uniform distribution

5. STL Sorting:
   - sort(): Uses Tim Sort (hybrid of merge and insertion), O(n log n)
   - stable_sort(): Stable version of sort(), O(n log n)
   - nth_element(): Find nth smallest element, O(n) average time

6. Performance Tips:
   - Use STL sort() for most applications
   - For small datasets, insertion sort is often fastest
   - For linked lists, merge sort is more efficient
   - For special data types, implement custom comparison functions

7. Comparison of Randomness:
   - Quick sort has worst case O(n²) if pivot selection is poor
   - Merge sort has guaranteed O(n log n) time
*/
