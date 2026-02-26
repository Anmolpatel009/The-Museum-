/*
C++ STL Map and Set Example - Comprehensive Guide
=================================================
This file demonstrates the usage of std::map, std::unordered_map,
std::set, and std::unordered_set in C++ STL, including all
major operations and best practices.
*/

#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

// Helper function to print a map
template <typename K, typename V>
void printMap(const map<K, V>& m, const string& label) {
    cout << label << ": ";
    for (const auto& pair : m) {
        cout << "{" << pair.first << ": " << pair.second << "} ";
    }
    cout << endl;
}

// Helper function to print an unordered_map
template <typename K, typename V>
void printUnorderedMap(const unordered_map<K, V>& um, const string& label) {
    cout << label << ": ";
    for (const auto& pair : um) {
        cout << "{" << pair.first << ": " << pair.second << "} ";
    }
    cout << endl;
}

// Helper function to print a set
template <typename T>
void printSet(const set<T>& s, const string& label) {
    cout << label << ": ";
    for (const T& item : s) {
        cout << item << " ";
    }
    cout << endl;
}

// Helper function to print an unordered_set
template <typename T>
void printUnorderedSet(const unordered_set<T>& us, const string& label) {
    cout << label << ": ";
    for (const T& item : us) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== C++ STL Map and Set Comprehensive Example ===\n\n";
    
    // =========================================================================
    // 1. Map Example (Ordered, Red-Black Tree)
    // =========================================================================
    cout << "1. Map Operations (Ordered by Key):\n";
    
    map<string, int> employeeSalaries;
    
    // Insert key-value pairs
    employeeSalaries["John"] = 50000;
    employeeSalaries["Jane"] = 60000;
    employeeSalaries["Mike"] = 55000;
    employeeSalaries.insert(make_pair("Sarah", 70000));
    employeeSalaries.insert({"Tom", 48000});
    printMap(employeeSalaries, "   Initial map");
    
    // Access elements
    cout << "   Jane's salary: " << employeeSalaries["Jane"] << endl;
    cout << "   John's salary: " << employeeSalaries.at("John") << endl;
    
    // Check if key exists
    string key = "Sarah";
    if (employeeSalaries.find(key) != employeeSalaries.end()) {
        cout << "   " << key << " exists with salary: " << employeeSalaries[key] << endl;
    }
    
    // Update values
    employeeSalaries["John"] += 5000;
    printMap(employeeSalaries, "   After updating John's salary");
    
    // Size and capacity
    cout << "   Map size: " << employeeSalaries.size() << endl;
    cout << "   Is empty? " << (employeeSalaries.empty() ? "Yes" : "No") << endl;
    cout << "   Maximum size: " << employeeSalaries.max_size() << endl;
    
    // Iteration
    cout << "   Iterating through map:\n   ";
    for (auto it = employeeSalaries.begin(); it != employeeSalaries.end(); ++it) {
        cout << "[" << it->first << ": " << it->second << "] ";
    }
    cout << endl;
    
    // Erase elements
    employeeSalaries.erase("Mike");  // Erase by key
    printMap(employeeSalaries, "   After erasing Mike");
    
    auto eraseIt = employeeSalaries.find("Tom");
    if (eraseIt != employeeSalaries.end()) {
        employeeSalaries.erase(eraseIt);  // Erase by iterator
    }
    printMap(employeeSalaries, "   After erasing Tom");
    
    // Clear the map
    employeeSalaries.clear();
    cout << "   After clear(): size = " << employeeSalaries.size() << endl;
    
    cout << endl;
    
    // =========================================================================
    // 2. Unordered Map Example (Hash Table)
    // =========================================================================
    cout << "2. Unordered Map Operations (Hash Table):\n";
    
    unordered_map<string, string> countryCapitals;
    
    countryCapitals["USA"] = "Washington D.C.";
    countryCapitals["France"] = "Paris";
    countryCapitals["Japan"] = "Tokyo";
    countryCapitals["India"] = "New Delhi";
    countryCapitals["Brazil"] = "Brasilia";
    printUnorderedMap(countryCapitals, "   Initial unordered_map");
    
    // Hash table properties
    cout << "   Bucket count: " << countryCapitals.bucket_count() << endl;
    cout << "   Load factor: " << countryCapitals.load_factor() << endl;
    
    // Bucket operations
    cout << "   USA is in bucket " << countryCapitals.bucket("USA") << endl;
    cout << "   Bucket 3 contains " << countryCapitals.bucket_size(3) << " elements" << endl;
    
    cout << endl;
    
    // =========================================================================
    // 3. Set Example (Ordered, Red-Black Tree)
    // =========================================================================
    cout << "3. Set Operations (Ordered):\n";
    
    set<int> uniqueNumbers;
    
    // Insert elements
    uniqueNumbers.insert(5);
    uniqueNumbers.insert(3);
    uniqueNumbers.insert(7);
    uniqueNumbers.insert(3);  // Duplicate, will be ignored
    uniqueNumbers.insert(9);
    uniqueNumbers.insert(1);
    printSet(uniqueNumbers, "   Initial set");
    
    // Size and capacity
    cout << "   Set size: " << uniqueNumbers.size() << endl;
    cout << "   Is empty? " << (uniqueNumbers.empty() ? "Yes" : "No") << endl;
    
    // Check if element exists
    int target = 7;
    if (uniqueNumbers.find(target) != uniqueNumbers.end()) {
        cout << "   " << target << " exists in the set" << endl;
    } else {
        cout << "   " << target << " not found" << endl;
    }
    
    // Range find
    cout << "   Elements less than 6: ";
    for (auto it = uniqueNumbers.begin(); it != uniqueNumbers.upper_bound(6); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Erase elements
    uniqueNumbers.erase(5);  // Erase by value
    printSet(uniqueNumbers, "   After erasing 5");
    
    auto eraseItSet = uniqueNumbers.find(3);
    if (eraseItSet != uniqueNumbers.end()) {
        uniqueNumbers.erase(eraseItSet);  // Erase by iterator
    }
    printSet(uniqueNumbers, "   After erasing 3");
    
    // Clear the set
    uniqueNumbers.clear();
    cout << "   After clear(): size = " << uniqueNumbers.size() << endl;
    
    cout << endl;
    
    // =========================================================================
    // 4. Unordered Set Example (Hash Table)
    // =========================================================================
    cout << "4. Unordered Set Operations (Hash Table):\n";
    
    unordered_set<string> uniqueWords;
    
    uniqueWords.insert("apple");
    uniqueWords.insert("banana");
    uniqueWords.insert("cherry");
    uniqueWords.insert("apple");  // Duplicate
    uniqueWords.insert("date");
    printUnorderedSet(uniqueWords, "   Initial unordered_set");
    
    // Hash table properties
    cout << "   Bucket count: " << uniqueWords.bucket_count() << endl;
    cout << "   Load factor: " << uniqueWords.load_factor() << endl;
    
    cout << endl;
    
    // =========================================================================
    // 5. Multimap and Multiset (Allow Duplicates)
    // =========================================================================
    cout << "5. Multimap and Multiset (Allow Duplicates):\n";
    
    // Multimap - allows duplicate keys
    multimap<int, string> ageNames;
    ageNames.insert({25, "Alice"});
    ageNames.insert({30, "Bob"});
    ageNames.insert({25, "Charlie"});
    ageNames.insert({30, "David"});
    ageNames.insert({28, "Eve"});
    
    cout << "   Multimap (age -> name):\n   ";
    for (const auto& pair : ageNames) {
        cout << "{" << pair.first << ": " << pair.second << "} ";
    }
    cout << endl;
    
    // Find all elements with key 25
    cout << "   Names with age 25: ";
    auto range = ageNames.equal_range(25);
    for (auto it = range.first; it != range.second; ++it) {
        cout << it->second << " ";
    }
    cout << endl;
    
    // Multiset - allows duplicate values
    multiset<int> numbersWithDuplicates;
    numbersWithDuplicates.insert(10);
    numbersWithDuplicates.insert(20);
    numbersWithDuplicates.insert(10);
    numbersWithDuplicates.insert(30);
    numbersWithDuplicates.insert(20);
    
    cout << "   Multiset: ";
    for (int num : numbersWithDuplicates) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "   Count of 10's: " << numbersWithDuplicates.count(10) << endl;
    
    cout << endl;
    
    // =========================================================================
    // 6. Practical Examples
    // =========================================================================
    cout << "6. Practical Examples:\n";
    
    // Example 1: Count word frequency in a text
    cout << "   Example 1: Word frequency counter\n";
    
    string text = "the quick brown fox jumps over the lazy dog the quick brown fox";
    unordered_map<string, int> wordCount;
    
    // Split text into words and count
    string word;
    for (char c : text) {
        if (isalpha(c)) {
            word += tolower(c);
        } else if (!word.empty()) {
            wordCount[word]++;
            word.clear();
        }
    }
    if (!word.empty()) {
        wordCount[word]++;
    }
    
    cout << "   Word frequencies:\n";
    for (const auto& pair : wordCount) {
        cout << "   " << pair.first << ": " << pair.second << endl;
    }
    
    cout << endl;
    
    // Example 2: Remove duplicates from a vector
    cout << "   Example 2: Remove duplicates from vector using set\n";
    
    vector<int> numbers = {1, 2, 3, 2, 4, 1, 5, 3};
    cout << "   Original vector: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    set<int> uniqueNumbersSet(numbers.begin(), numbers.end());
    vector<int> uniqueVector(uniqueNumbersSet.begin(), uniqueNumbersSet.end());
    
    cout << "   Without duplicates (sorted): ";
    for (int num : uniqueVector) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << endl;
    
    // =========================================================================
    // 7. Performance Comparison
    // =========================================================================
    cout << "7. Performance Comparison:\n";
    
    const int numElements = 100000;
    
    // Measure map performance
    clock_t start = clock();
    map<int, int> performanceMap;
    for (int i = 0; i < numElements; ++i) {
        performanceMap[i] = i * 2;
    }
    for (int i = 0; i < numElements; ++i) {
        int value = performanceMap[i];
    }
    double mapTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "   Map operations (" << numElements << " insert/find): " 
         << mapTime << " seconds\n";
    
    // Measure unordered_map performance
    start = clock();
    unordered_map<int, int> performanceUnorderedMap;
    for (int i = 0; i < numElements; ++i) {
        performanceUnorderedMap[i] = i * 2;
    }
    for (int i = 0; i < numElements; ++i) {
        int value = performanceUnorderedMap[i];
    }
    double unorderedMapTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "   Unordered_map operations (" << numElements << " insert/find): " 
         << unorderedMapTime << " seconds\n";
    
    // Measure set performance
    start = clock();
    set<int> performanceSet;
    for (int i = 0; i < numElements; ++i) {
        performanceSet.insert(i);
    }
    for (int i = 0; i < numElements; ++i) {
        bool exists = (performanceSet.find(i) != performanceSet.end());
    }
    double setTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "   Set operations (" << numElements << " insert/find): " 
         << setTime << " seconds\n";
    
    // Measure unordered_set performance
    start = clock();
    unordered_set<int> performanceUnorderedSet;
    for (int i = 0; i < numElements; ++i) {
        performanceUnorderedSet.insert(i);
    }
    for (int i = 0; i < numElements; ++i) {
        bool exists = (performanceUnorderedSet.find(i) != performanceUnorderedSet.end());
    }
    double unorderedSetTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    cout << "   Unordered_set operations (" << numElements << " insert/find): " 
         << unorderedSetTime << " seconds\n";
    
    cout << endl;
    
    // =========================================================================
    // 8. Custom Key Types
    // =========================================================================
    cout << "8. Custom Key Types:\n";
    
    // Define a custom struct for complex numbers
    struct Complex {
        double real;
        double imag;
        
        Complex(double r = 0, double i = 0) : real(r), imag(i) {}
        
        bool operator<(const Complex& other) const {
            if (real != other.real) {
                return real < other.real;
            }
            return imag < other.imag;
        }
    };
    
    // Create a map with Complex as key
    map<Complex, string> complexMap;
    complexMap[Complex(1, 2)] = "First";
    complexMap[Complex(0, 3)] = "Second";
    complexMap[Complex(2, 1)] = "Third";
    
    cout << "   Map with custom Complex keys:\n";
    for (const auto& pair : complexMap) {
        cout << "   (" << pair.first.real << ", " << pair.first.imag << "): " 
             << pair.second << endl;
    }
    
    cout << endl;
    
    cout << "=== Example Completed ===\n";
    return 0;
}

/*
Key Takeaways:
1. Map: Ordered key-value pairs, O(log n) operations, Red-Black tree
2. Unordered Map: Unordered key-value pairs, O(1) average time, hash table
3. Set: Ordered unique elements, O(log n) operations
4. Unordered Set: Unordered unique elements, O(1) average time
5. Multimap/Multiset: Allow duplicate keys/values
6. Use map/set for ordered data, unordered versions for faster access
7. Always define proper comparison operators for custom types
8. Hash tables have worst-case O(n) time if many collisions
*/
