/*
C++ Dynamic Programming Examples - Comprehensive Guide
======================================================
This file demonstrates various dynamic programming problems with implementations,
including classic problems, optimal solutions, and performance comparisons.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

// =========================================================================
// Helper Functions
// =========================================================================

// Print a 2D vector
template <typename T>
void print2DVector(const vector<vector<T>>& dp, const string& label) {
    cout << label << ":\n";
    for (const vector<T>& row : dp) {
        for (const T& value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Print a 1D vector
template <typename T>
void printVector(const vector<T>& vec, const string& label) {
    cout << label << ": ";
    for (const T& value : vec) {
        cout << value << " ";
    }
    cout << endl;
}

// =========================================================================
// 1. Fibonacci Numbers
// =========================================================================

// Recursive approach (exponential time)
int fibRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// Memoization (top-down dynamic programming)
int fibMemoization(int n, vector<int>& memo) {
    if (n <= 1) {
        return n;
    }
    if (memo[n] != -1) {
        return memo[n];
    }
    memo[n] = fibMemoization(n - 1, memo) + fibMemoization(n - 2, memo);
    return memo[n];
}

// Tabulation (bottom-up dynamic programming)
int fibTabulation(int n) {
    if (n <= 1) {
        return n;
    }
    
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

// Optimized tabulation (constant space)
int fibOptimized(int n) {
    if (n <= 1) {
        return n;
    }
    
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    
    return b;
}

// =========================================================================
// 2. Climbing Stairs
// =========================================================================

// Recursive approach
int climbStairsRecursive(int n) {
    if (n <= 2) {
        return n;
    }
    return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
}

// Dynamic programming approach
int climbStairsDP(int n) {
    if (n <= 2) {
        return n;
    }
    
    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

// Optimized dynamic programming (constant space)
int climbStairsOptimized(int n) {
    if (n <= 2) {
        return n;
    }
    
    int a = 1, b = 2, c;
    for (int i = 3; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    
    return b;
}

// =========================================================================
// 3. Longest Common Subsequence (LCS)
// =========================================================================

int lcsRecursive(const string& s1, const string& s2, int i, int j) {
    if (i == 0 || j == 0) {
        return 0;
    }
    
    if (s1[i - 1] == s2[j - 1]) {
        return 1 + lcsRecursive(s1, s2, i - 1, j - 1);
    } else {
        return max(lcsRecursive(s1, s2, i - 1, j), lcsRecursive(s1, s2, i, j - 1));
    }
}

int lcsDP(const string& s1, const string& s2) {
    int m = s1.size();
    int n = s2.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    return dp[m][n];
}

string lcsPrint(const string& s1, const string& s2) {
    int m = s1.size();
    int n = s2.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs += s1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    reverse(lcs.begin(), lcs.end());
    return lcs;
}

// =========================================================================
// 4. Longest Increasing Subsequence (LIS)
// =========================================================================

int lisRecursive(const vector<int>& arr, int index, int prev) {
    if (index == arr.size()) {
        return 0;
    }
    
    int notTake = lisRecursive(arr, index + 1, prev);
    int take = 0;
    
    if (arr[index] > prev) {
        take = 1 + lisRecursive(arr, index + 1, arr[index]);
    }
    
    return max(take, notTake);
}

int lisDP(const vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *max_element(dp.begin(), dp.end());
}

int lisOptimized(const vector<int>& arr) {
    vector<int> tails;
    
    for (int num : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if (it == tails.end()) {
            tails.push_back(num);
        } else {
            *it = num;
        }
    }
    
    return tails.size();
}

// =========================================================================
// 5. 0/1 Knapsack Problem
// =========================================================================

int knapsackRecursive(const vector<int>& weights, const vector<int>& values, int capacity, int n) {
    if (n == 0 || capacity == 0) {
        return 0;
    }
    
    if (weights[n - 1] > capacity) {
        return knapsackRecursive(weights, values, capacity, n - 1);
    } else {
        int include = values[n - 1] + knapsackRecursive(weights, values, capacity - weights[n - 1], n - 1);
        int exclude = knapsackRecursive(weights, values, capacity, n - 1);
        return max(include, exclude);
    }
}

int knapsackDP(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (weights[i - 1] > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                int include = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                int exclude = dp[i - 1][w];
                dp[i][w] = max(include, exclude);
            }
        }
    }
    
    return dp[n][capacity];
}

int knapsackOptimized(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<int> dp(capacity + 1, 0);
    
    for (int i = 0; i < n; ++i) {
        for (int w = capacity; w >= weights[i]; --w) {
            dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
        }
    }
    
    return dp[capacity];
}

// =========================================================================
// 6. Coin Change Problem
// =========================================================================

int coinChangeRecursive(const vector<int>& coins, int amount, int index) {
    if (amount == 0) {
        return 0;
    }
    if (index < 0 || amount < 0) {
        return INT_MAX;
    }
    
    int take = INT_MAX;
    if (coins[index] <= amount) {
        int result = coinChangeRecursive(coins, amount - coins[index], index);
        if (result != INT_MAX) {
            take = 1 + result;
        }
    }
    
    int notTake = coinChangeRecursive(coins, amount, index - 1);
    
    return min(take, notTake);
}

int coinChangeDP(const vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    
    for (int coin : coins) {
        for (int i = coin; i <= amount; ++i) {
            if (dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// =========================================================================
// 7. Maximum Subarray Sum (Kadane's Algorithm)
// =========================================================================

int maxSubarrayRecursive(const vector<int>& arr, int n) {
    if (n == 1) {
        return arr[0];
    }
    
    int mid = n / 2;
    int leftMax = maxSubarrayRecursive(vector<int>(arr.begin(), arr.begin() + mid), mid);
    int rightMax = maxSubarrayRecursive(vector<int>(arr.begin() + mid, arr.end()), n - mid);
    
    int crossLeft = INT_MIN, crossRight = INT_MIN, temp = 0;
    
    for (int i = mid - 1; i >= 0; --i) {
        temp += arr[i];
        crossLeft = max(crossLeft, temp);
    }
    
    temp = 0;
    for (int i = mid; i < n; ++i) {
        temp += arr[i];
        crossRight = max(crossRight, temp);
    }
    
    return max({leftMax, rightMax, crossLeft + crossRight});
}

int maxSubarrayDP(const vector<int>& arr) {
    int maxSum = arr[0];
    int currentSum = arr[0];
    
    for (size_t i = 1; i < arr.size(); ++i) {
        currentSum = max(arr[i], currentSum + arr[i]);
        maxSum = max(maxSum, currentSum);
    }
    
    return maxSum;
}

// =========================================================================
// 8. Longest Palindromic Substring
// =========================================================================

string longestPalindromeDP(const string& s) {
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int start = 0;
    int maxLength = 1;
    
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }
    
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }
    
    for (int length = 3; length <= n; ++length) {
        for (int i = 0; i <= n - length; ++i) {
            int j = i + length - 1;
            
            if (dp[i + 1][j - 1] && s[i] == s[j]) {
                dp[i][j] = true;
                start = i;
                maxLength = length;
            }
        }
    }
    
    return s.substr(start, maxLength);
}

// =========================================================================
// 9. Edit Distance (Levenshtein Distance)
// =========================================================================

int editDistanceRecursive(const string& s1, const string& s2, int i, int j) {
    if (i == 0) {
        return j;
    }
    if (j == 0) {
        return i;
    }
    
    if (s1[i - 1] == s2[j - 1]) {
        return editDistanceRecursive(s1, s2, i - 1, j - 1);
    }
    
    int insert = editDistanceRecursive(s1, s2, i, j - 1);
    int remove = editDistanceRecursive(s1, s2, i - 1, j);
    int replace = editDistanceRecursive(s1, s2, i - 1, j - 1);
    
    return 1 + min({insert, remove, replace});
}

int editDistanceDP(const string& s1, const string& s2) {
    int m = s1.size();
    int n = s2.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i;
    }
    
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                int insert = dp[i][j - 1];
                int remove = dp[i - 1][j];
                int replace = dp[i - 1][j - 1];
                dp[i][j] = 1 + min({insert, remove, replace});
            }
        }
    }
    
    return dp[m][n];
}

// =========================================================================
// 10. Matrix Chain Multiplication
// =========================================================================

int matrixChainRecursive(const vector<int>& dimensions, int i, int j) {
    if (i == j) {
        return 0;
    }
    
    int minCost = INT_MAX;
    
    for (int k = i; k < j; ++k) {
        int cost = matrixChainRecursive(dimensions, i, k) +
                   matrixChainRecursive(dimensions, k + 1, j) +
                   dimensions[i - 1] * dimensions[k] * dimensions[j];
        
        if (cost < minCost) {
            minCost = cost;
        }
    }
    
    return minCost;
}

int matrixChainDP(const vector<int>& dimensions) {
    int n = dimensions.size() - 1;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    
    for (int length = 2; length <= n; ++length) {
        for (int i = 1; i <= n - length + 1; ++i) {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;
            
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }
    
    return dp[1][n];
}

// =========================================================================
// Main Function for Testing
// =========================================================================
int main() {
    cout << "=== C++ Dynamic Programming Comprehensive Example ===\n\n";
    
    // Fibonacci Numbers
    cout << "1. Fibonacci Numbers:\n";
    int n = 10;
    cout << "Fibonacci(" << n << ") - Recursive: " << fibRecursive(n) << endl;
    
    vector<int> memo(n + 1, -1);
    cout << "Fibonacci(" << n << ") - Memoization: " << fibMemoization(n, memo) << endl;
    
    cout << "Fibonacci(" << n << ") - Tabulation: " << fibTabulation(n) << endl;
    
    cout << "Fibonacci(" << n << ") - Optimized: " << fibOptimized(n) << endl;
    cout << endl;
    
    // Climbing Stairs
    cout << "2. Climbing Stairs:\n";
    int stairs = 5;
    cout << "Ways to climb " << stairs << " stairs - Recursive: " << climbStairsRecursive(stairs) << endl;
    cout << "Ways to climb " << stairs << " stairs - DP: " << climbStairsDP(stairs) << endl;
    cout << "Ways to climb " << stairs << " stairs - Optimized: " << climbStairsOptimized(stairs) << endl;
    cout << endl;
    
    // Longest Common Subsequence
    cout << "3. Longest Common Subsequence:\n";
    string s1 = "abcde";
    string s2 = "ace";
    cout << "S1: " << s1 << ", S2: " << s2 << endl;
    cout << "LCS length (Recursive): " << lcsRecursive(s1, s2, s1.size(), s2.size()) << endl;
    cout << "LCS length (DP): " << lcsDP(s1, s2) << endl;
    cout << "LCS string: " << lcsPrint(s1, s2) << endl;
    cout << endl;
    
    // Longest Increasing Subsequence
    cout << "4. Longest Increasing Subsequence:\n";
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    printVector(arr, "Array");
    cout << "LIS length (Recursive): " << lisRecursive(arr, 0, INT_MIN) << endl;
    cout << "LIS length (DP): " << lisDP(arr) << endl;
    cout << "LIS length (Optimized): " << lisOptimized(arr) << endl;
    cout << endl;
    
    // 0/1 Knapsack Problem
    cout << "5. 0/1 Knapsack Problem:\n";
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    int capacity = 8;
    printVector(weights, "Weights");
    printVector(values, "Values");
    cout << "Capacity: " << capacity << endl;
    cout << "Maximum value (Recursive): " << knapsackRecursive(weights, values, capacity, weights.size()) << endl;
    cout << "Maximum value (DP): " << knapsackDP(weights, values, capacity) << endl;
    cout << "Maximum value (Optimized): " << knapsackOptimized(weights, values, capacity) << endl;
    cout << endl;
    
    // Coin Change Problem
    cout << "6. Coin Change Problem:\n";
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    printVector(coins, "Coins");
    cout << "Amount: " << amount << endl;
    int result = coinChangeRecursive(coins, amount, coins.size() - 1);
    cout << "Minimum coins (Recursive): " << (result == INT_MAX ? -1 : result) << endl;
    cout << "Minimum coins (DP): " << coinChangeDP(coins, amount) << endl;
    cout << endl;
    
    // Maximum Subarray Sum
    cout << "7. Maximum Subarray Sum:\n";
    vector<int> subarr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    printVector(subarr, "Array");
    cout << "Maximum subarray sum (Recursive): " << maxSubarrayRecursive(subarr, subarr.size()) << endl;
    cout << "Maximum subarray sum (DP): " << maxSubarrayDP(subarr) << endl;
    cout << endl;
    
    // Longest Palindromic Substring
    cout << "8. Longest Palindromic Substring:\n";
    string palindromeStr = "babad";
    cout << "Input string: " << palindromeStr << endl;
    cout << "Longest palindromic substring: " << longestPalindromeDP(palindromeStr) << endl;
    cout << endl;
    
    // Edit Distance
    cout << "9. Edit Distance:\n";
    string editStr1 = "kitten";
    string editStr2 = "sitting";
    cout << "S1: " << editStr1 << ", S2: " << editStr2 << endl;
    cout << "Edit distance (Recursive): " << editDistanceRecursive(editStr1, editStr2, editStr1.size(), editStr2.size()) << endl;
    cout << "Edit distance (DP): " << editDistanceDP(editStr1, editStr2) << endl;
    cout << endl;
    
    // Matrix Chain Multiplication
    cout << "10. Matrix Chain Multiplication:\n";
    vector<int> matrixDims = {10, 30, 5, 60};
    printVector(matrixDims, "Matrix dimensions");
    cout << "Minimum multiplications (Recursive): " << matrixChainRecursive(matrixDims, 1, matrixDims.size() - 1) << endl;
    cout << "Minimum multiplications (DP): " << matrixChainDP(matrixDims) << endl;
    cout << endl;
    
    cout << "=== All Tests Completed ===\n";
    return 0;
}

/*
Key Takeaways:

1. Dynamic Programming Principles:
   - Optimal Substructure: Optimal solution can be constructed from optimal solutions of subproblems
   - Overlapping Subproblems: Subproblems are solved multiple times

2. Approaches:
   - Recursive: Simple but inefficient for large inputs
   - Memoization (Top-Down): Store solutions to subproblems to avoid redundant calculations
   - Tabulation (Bottom-Up): Build solutions from smallest to largest subproblems
   - Optimized: Reduce space complexity by reusing variables

3. Time Complexity:
   - Fibonacci: O(n) with DP, O(2^n) recursive
   - LCS: O(mn)
   - LIS: O(n^2) or O(n log n) optimized
   - Knapsack: O(nW)
   - Coin Change: O(amount * coins)
   - Kadane's: O(n)
   - Matrix Chain: O(n^3)

4. Space Complexity:
   - O(n): Fibonacci, Climbing Stairs, Coin Change (optimized)
   - O(n^2): LCS, LIS, Knapsack, Matrix Chain
   - O(1): Some optimized solutions (Fibonacci)

5. When to Use Dynamic Programming:
   - Problems with optimal substructure
   - Problems with overlapping subproblems
   - Problems involving optimization (max/min)
   - Problems with decisions that affect future choices

6. Classic Problems:
   - Fibonacci, Climbing Stairs
   - LCS, LIS
   - Knapsack
   - Coin Change
   - Kadane's Algorithm
   - Longest Palindromic Substring
   - Edit Distance
   - Matrix Chain Multiplication

7. Implementation Tips:
   - Start with recursive approach to understand the problem
   - Add memoization to optimize
   - Convert to bottom-up DP for better efficiency
   - Optimize space if possible

8. Common Patterns:
   - 1D DP arrays: Single state variable
   - 2D DP tables: Two state variables
   - Optimized DP: Use previous values instead of full tables

Dynamic programming is a powerful technique for solving complex optimization problems by breaking them into simpler subproblems and reusing solutions to overlapping subproblems.
*/
