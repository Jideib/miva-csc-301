/*
 CSC 301 - Data Structures
 Tutor-Marked Assessment
 Question 2: Solving Problems Using Recursion
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ============================================================================
// FACTORIAL CALCULATION USING RECURSION
// ============================================================================

/*
 F *unction: calculateFactorial
 Purpose: To calculate the factorial of a number using recursion
 Base Case: When n is 0 or 1, return 1 (since 0! = 1 and 1! = 1)
 Recursive Case: n * factorial(n-1) - the function calls itself with n-1
 Explanation:
 - Factorial of n (n!) is the product of all positive integers from 1 to n
 - Example: 5! = 5 × 4 × 3 × 2 × 1 = 120
 - The recursive approach breaks down the problem into smaller subproblems
 */
long long calculateFactorial(int n) {
    // BASE CASE: If n is 0 or 1, factorial is 1
    // This stops the recursion from going forever
    if (n == 0 || n == 1) {
        cout << "Base case reached: factorial(" << n << ") = 1" << endl;
        return 1;
    }

    // RECURSIVE CASE: n * factorial(n-1)
    // The function calls itself with a smaller value (n-1)
    cout << "Calculating " << n << " * factorial(" << n-1 << ")" << endl;
    long long result = n * calculateFactorial(n - 1);
    cout << "Returning " << n << "! = " << result << endl;
    return result;
}

void testFactorial() {
    cout << "=== FACTORIAL CALCULATION TESTS ===" << endl;

    // Test case 1: Edge case - factorial of 0
    cout << "\nTest 1 - Factorial of 0 (Edge Case):" << endl;
    cout << "Result: " << calculateFactorial(0) << endl;

    // Test case 2: Small number
    cout << "\nTest 2 - Factorial of 1:" << endl;
    cout << "Result: " << calculateFactorial(1) << endl;

    // Test case 3: Normal case
    cout << "\nTest 3 - Factorial of 5:" << endl;
    cout << "Result: " << calculateFactorial(5) << endl;

    // Test case 4: Larger number
    cout << "\nTest 4 - Factorial of 7:" << endl;
    cout << "Result: " << calculateFactorial(7) << endl;
}

// ============================================================================
// FIBONACCI SEQUENCE USING RECURSION
// ============================================================================

/*
 F *unction: fibonacci
 Purpose: To find the nth Fibonacci number using recursion
 Base Cases:
 - fibonacci(0) = 0
 - fibonacci(1) = 1
 Recursive Case: fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)
 Explanation:
 - Fibonacci sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...
 - Each number is the sum of the two preceding ones
 - This shows the "tree-like" structure of recursion
 */
int fibonacci(int n) {
    // BASE CASE 1: fibonacci(0) = 0
    if (n == 0) {
        return 0;
    }
    // BASE CASE 2: fibonacci(1) = 1
    if (n == 1) {
        return 1;
    }

    // RECURSIVE CASE: fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)
    // The function calls itself twice with different parameters
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void printFibonacciSequence(int n) {
    cout << "First " << n << " Fibonacci numbers: ";
    for (int i = 0; i < n; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;
}

void testFibonacci() {
    cout << "\n=== FIBONACCI SEQUENCE TESTS ===" << endl;

    // Test case 1: Edge case - first 0 numbers
    cout << "\nTest 1 - First 0 Fibonacci numbers (Edge Case):" << endl;
    printFibonacciSequence(0);

    // Test case 2: Small sequence
    cout << "\nTest 2 - First 5 Fibonacci numbers:" << endl;
    printFibonacciSequence(5);

    // Test case 3: Medium sequence
    cout << "\nTest 3 - First 8 Fibonacci numbers:" << endl;
    printFibonacciSequence(8);

    // Test case 4: Individual number
    cout << "\nTest 4 - 6th Fibonacci number:" << endl;
    cout << "fibonacci(6) = " << fibonacci(6) << endl;
}

// ============================================================================
// STRING REVERSAL USING RECURSION
// ============================================================================

/*
 F *unction: reverseString
 Purpose: To reverse a string using recursion
 Base Case: When string is empty or has only one character, return the string as is
 Recursive Case: reverse(substring) + first_character
 Explanation:
 - We take the first character and put it at the end
 - Then recursively reverse the remaining substring
 - This builds the reversed string from the end to the beginning
 */
string reverseString(const string& str) {
    // BASE CASE: If string is empty or has only one character, it's already reversed
    if (str.length() <= 1) {
        return str;
    }

    // RECURSIVE CASE:
    // Take the substring from position 1 to end and reverse it recursively
    // Then append the first character at the end
    string reversed = reverseString(str.substr(1)) + str[0];
    return reversed;
}

void testStringReversal() {
    cout << "\n=== STRING REVERSAL TESTS ===" << endl;

    // Test case 1: Edge case - empty string
    cout << "\nTest 1 - Reverse empty string (Edge Case):" << endl;
    string test1 = "";
    cout << "Original: \"" << test1 << "\" -> Reversed: \"" << reverseString(test1) << "\"" << endl;

    // Test case 2: Single character
    cout << "\nTest 2 - Reverse single character:" << endl;
    string test2 = "A";
    cout << "Original: \"" << test2 << "\" -> Reversed: \"" << reverseString(test2) << "\"" << endl;

    // Test case 3: Normal string
    cout << "\nTest 3 - Reverse 'hello':" << endl;
    string test3 = "hello";
    cout << "Original: \"" << test3 << "\" -> Reversed: \"" << reverseString(test3) << "\"" << endl;

    // Test case 4: Longer string
    cout << "\nTest 4 - Reverse 'recursion':" << endl;
    string test4 = "recursion";
    cout << "Original: \"" << test4 << "\" -> Reversed: \"" << reverseString(test4) << "\"" << endl;
}

// ============================================================================
// BINARY SEARCH USING RECURSION
// ============================================================================

/*
 F *unction: recursiveBinarySearch
 Purpose: To find a target element in sorted array using recursive binary search
 Base Cases:
 - If left > right: element not found, return -1
 - If arr[mid] == target: element found, return mid index
 Recursive Cases:
 - If target < arr[mid]: search in left half
 - If target > arr[mid]: search in right half
 Explanation:
 - Binary search works by repeatedly dividing the search interval in half
 - The array must be sorted for this to work
 - Each recursive call works on a smaller portion of the array
 */
int recursiveBinarySearch(const vector<int>& arr, int target, int left, int right) {
    // BASE CASE 1: Element not found - search space is empty
    if (left > right) {
        return -1;
    }

    // Calculate middle index to avoid overflow
    int mid = left + (right - left) / 2;

    // BASE CASE 2: Element found at middle index
    if (arr[mid] == target) {
        return mid;
    }

    // RECURSIVE CASE 1: Search in left half if target is smaller
    if (target < arr[mid]) {
        return recursiveBinarySearch(arr, target, left, mid - 1);
    }
    // RECURSIVE CASE 2: Search in right half if target is larger
    else {
        return recursiveBinarySearch(arr, target, mid + 1, right);
    }
}

void testBinarySearch() {
    cout << "\n=== BINARY SEARCH TESTS ===" << endl;

    // Test array for binary search (must be sorted)
    vector<int> sortedArray = {2, 5, 8, 12, 16, 23, 38, 45, 67, 89};

    // Test case 1: Edge case - empty array
    cout << "\nTest 1 - Search in empty array (Edge Case):" << endl;
    vector<int> emptyArray = {};
    int result1 = recursiveBinarySearch(emptyArray, 5, 0, emptyArray.size() - 1);
    cout << "Search for 5 in empty array: " << (result1 == -1 ? "Not found" : "Found") << endl;

    // Test case 2: Element found in middle
    cout << "\nTest 2 - Search for element in middle:" << endl;
    int result2 = recursiveBinarySearch(sortedArray, 23, 0, sortedArray.size() - 1);
    cout << "Search for 23: " << (result2 != -1 ? "Found at index " + to_string(result2) : "Not found") << endl;

    // Test case 3: Element found at beginning
    cout << "\nTest 3 - Search for element at beginning:" << endl;
    int result3 = recursiveBinarySearch(sortedArray, 2, 0, sortedArray.size() - 1);
    cout << "Search for 2: " << (result3 != -1 ? "Found at index " + to_string(result3) : "Not found") << endl;

    // Test case 4: Element not found
    cout << "\nTest 4 - Search for non-existent element:" << endl;
    int result4 = recursiveBinarySearch(sortedArray, 100, 0, sortedArray.size() - 1);
    cout << "Search for 100: " << (result4 != -1 ? "Found at index " + to_string(result4) : "Not found") << endl;
}

// ============================================================================
// MAIN FUNCTION - TEST ALL RECURSIVE FUNCTIONS
// ============================================================================

int main() {
    cout << "CSC 301 - Data Structures - Recursion Assignment" << endl;
    cout << "================================================" << endl;

    // Test all recursive functions
    testFactorial();
    testFibonacci();
    testStringReversal();
    testBinarySearch();

    cout << "\n=== ALL TESTS COMPLETED ===" << endl;

    return 0;
}
