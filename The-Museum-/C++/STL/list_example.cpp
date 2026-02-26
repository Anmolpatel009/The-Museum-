/*
C++ STL List Example - Comprehensive Guide
==========================================
This file demonstrates the usage of std::list in C++ STL,
including all major operations and best practices.
*/

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

// Function to print a list with a label
template <typename T>
void printList(const list<T>& lst, const string& label) {
    cout << label << ": ";
    for (const T& item : lst) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== C++ STL List Comprehensive Example ===\n\n";
    
    // 1. List Initialization
    cout << "1. List Initialization Methods:\n";
    
    // Empty list
    list<int> lst1;
    cout << "   Empty list: size = " << lst1.size() << endl;
    
    // List with 5 elements initialized to 0
    list<int> lst2(5);
    cout << "   List with 5 zeros: size = " << lst2.size() << endl;
    
    // List with 3 elements initialized to 7
    list<int> lst3(3, 7);
    printList(lst3, "   List with 3 sevens");
    
    // List from initializer list
    list<int> lst4 = {1, 2, 3, 4, 5};
    printList(lst4, "   List from initializer list");
    
    // List from another list
    list<int> lst5(lst4);
    printList(lst5, "   List from another list");
    
    // List from array
    int arr[] = {10, 20, 30, 40};
    list<int> lst6(arr, arr + sizeof(arr)/sizeof(arr[0]));
    printList(lst6, "   List from array");
    
    cout << endl;
    
    // 2. Element Access
    cout << "2. Element Access Methods:\n";
    
    list<int> lst = {10, 20, 30, 40, 50};
    
    // Front and back access
    cout << "   Front element: " << lst.front() << endl;
    cout << "   Back element: " << lst.back() << endl;
    
    // No random access - must use iterators
    cout << "   Iterating through list:\n   ";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << endl;
    
    // 3. Capacity Operations
    cout << "3. Capacity Operations:\n";
    
    cout << "   Current size: " << lst.size() << endl;
    cout << "   Is empty? " << (lst.empty() ? "Yes" : "No") << endl;
    cout << "   Maximum size: " << lst.max_size() << endl;
    
    cout << endl;
    
    // 4. Modification Operations
    cout << "4. Modification Operations:\n";
    
    printList(lst, "   Original list");
    
    // Push front and back
    lst.push_front(5);
    lst.push_back(60);
    printList(lst, "   After push_front(5) and push_back(60)");
    
    // Pop front and back
    lst.pop_front();
    lst.pop_back();
    printList(lst, "   After pop_front() and pop_back()");
    
    // Insert elements
    auto it = lst.begin();
    advance(it, 2);  // Move iterator to index 2
    lst.insert(it, 25);  // Insert at position 2
    printList(lst, "   After insert at position 2: 25");
    
    lst.insert(lst.end(), 3, 80);  // Insert 3 elements of 80 at end
    printList(lst, "   After inserting 3 eights at end");
    
    list<int> temp = {90, 100};
    lst.insert(lst.end(), temp.begin(), temp.end());
    printList(lst, "   After inserting another list");
    
    // Erase elements
    auto eraseIt = lst.begin();
    advance(eraseIt, 3);  // Move to index 3
    lst.erase(eraseIt);  // Erase index 3
    printList(lst, "   After erase index 3");
    
    auto startIt = lst.begin();
    advance(startIt, 1);
    auto endIt = lst.begin();
    advance(endIt, 3);
    lst.erase(startIt, endIt);  // Erase range [1, 3)
    printList(lst, "   After erase range [1, 3)");
    
    // Clear the list
    lst.clear();
    cout << "   After clear(): size = " << lst.size() << endl;
    cout << "   Is empty? " << (lst.empty() ? "Yes" : "No") << endl;
    
    cout << endl;
    
    // 5. List Operations
    cout << "5. List Operations:\n";
    
    list<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    printList(nums, "   Original numbers");
    
    // Sorting
    nums.sort();
    printList(nums, "   Sorted numbers");
    
    // Reverse
    nums.reverse();
    printList(nums, "   Reversed numbers");
    
    // Remove elements with specific value
    nums.remove(1);  // Removes all elements with value 1
    printList(nums, "   After removing 1's");
    
    // Remove elements based on condition
    nums.remove_if([](int x) { return x % 2 == 0; });  // Remove even numbers
    printList(nums, "   After removing even numbers");
    
    // Unique elements (must be sorted)
    nums.sort();
    nums.unique();
    printList(nums, "   Unique elements (sorted)");
    
    cout << endl;
    
    // 6. Splice Operations (Merging lists)
    cout << "6. Splice Operations:\n";
    
    list<int> list1 = {1, 3, 5, 7};
    list<int> list2 = {2, 4, 6, 8};
    
    printList(list1, "   List1");
    printList(list2, "   List2");
    
    // Splice entire list2 into list1 at beginning
    list1.splice(list1.begin(), list2);
    printList(list1, "   List1 after splice list2 at beginning");
    cout << "   List2 size after splice: " << list2.size() << endl;
    
    cout << endl;
    
    // 7. Merge and Unique
    cout << "7. Merge and Unique Operations:\n";
    
    list<int> listA = {3, 1, 4, 1, 5};
    list<int> listB = {2, 7, 1, 8, 2};
    
    printList(listA, "   ListA");
    printList(listB, "   ListB");
    
    // Merge (requires both lists to be sorted)
    listA.sort();
    listB.sort();
    listA.merge(listB);
    printList(listA, "   After merge (sorted)");
    cout << "   ListB size after merge: " << listB.size() << endl;
    
    listA.unique();
    printList(listA, "   After unique");
    
    cout << endl;
    
    // 8. List Iteration
    cout << "8. List Iteration Methods:\n";
    
    list<string> fruits = {"Apple", "Banana", "Cherry", "Date"};
    
    // Forward iteration
    cout << "   Forward iteration:\n   ";
    for (auto it = fruits.begin(); it != fruits.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Reverse iteration
    cout << "   Reverse iteration:\n   ";
    for (auto it = fruits.rbegin(); it != fruits.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << endl;
    
    // 9. Performance Considerations
    cout << "9. Performance Considerations:\n";
    
    list<int> performanceList;
    const int numElements = 100000;
    
    // Adding elements to front and back
    cout << "   Adding " << numElements << " elements to front and back...\n";
    for (int i = 0; i < numElements; ++i) {
        if (i % 2 == 0) {
            performanceList.push_back(i);
        } else {
            performanceList.push_front(i);
        }
    }
    
    cout << "   List size: " << performanceList.size() << endl;
    
    // Removing elements from front and back
    cout << "   Removing " << numElements / 2 << " elements from front and back...\n";
    for (int i = 0; i < numElements / 2; ++i) {
        if (i % 2 == 0) {
            performanceList.pop_back();
        } else {
            performanceList.pop_front();
        }
    }
    
    cout << "   List size after removal: " << performanceList.size() << endl;
    
    cout << endl;
    
    cout << "=== List Example Completed ===\n";
    return 0;
}

/*
Key Takeaways:
1. Lists are doubly linked lists with O(1) insertion and deletion at any position
2. No random access - must use iterators to traverse
3. Prefer list over vector if you need frequent insertions/deletions in the middle
4. List has its own sort() method (not the STL algorithm)
5. Splice operations transfer elements between lists in O(1) time
6. Merging and unique operations require the list to be sorted
*/
