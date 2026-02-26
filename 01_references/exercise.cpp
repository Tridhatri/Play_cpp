#include <iostream>
#include <string>
#include <vector>

/*
 * EXERCISE 1: Implement a swap function using references
 * Unlike C which requires pointers, C++ references make this cleaner
 */
// TODO: Implement swap using references (no pointers!)
void swap(int& a, int& b) {
    // Your code here
}

/*
 * EXERCISE 2: Pass by const reference to avoid copying
 * In C, you'd pass a pointer to avoid copying. In C++, const ref is cleaner.
 */
struct LargeDataSet {
    int data[1000];
    std::string description;
};

// TODO: Implement this function to take a const reference
// Print the first and last elements of data array and the description
void printDataSetInfo(/* Add parameter here */) {
    // Your code here
}

/*
 * EXERCISE 3: Modify array elements using reference in range-based for
 * C doesn't have range-based for loops, this is C++'s syntax
 */
// TODO: Implement function that doubles all values in the vector
void doubleAllValues(std::vector<int>& vec) {
    // Use a range-based for loop with a reference
    // for (auto& elem : vec) { ... }
    // Your code here
}

/*
 * EXERCISE 4: Return reference for chaining
 * Create a simple Calculator class that supports chaining
 */
class Calculator {
private:
    int value;
    
public:
    Calculator() : value(0) {}
    
    // TODO: Implement add() to return a reference for chaining
    // Example: calc.add(5).add(10).subtract(3);
    Calculator& add(int num) {
        // Your code here
    }
    
    // TODO: Implement subtract() to return a reference for chaining
    Calculator& subtract(int num) {
        // Your code here
    }
    
    // TODO: Implement multiply() to return a reference for chaining
    Calculator& multiply(int num) {
        // Your code here
    }
    
    int getResult() const {
        return value;
    }
};

/*
 * EXERCISE 5: Understanding reference behavior vs pointers
 * Fill in the blanks to predict output
 */
void testReferenceBehavior() {
    int x = 5;
    int y = 10;
    
    int& ref = x;
    ref = y;  // What does this do?
    
    // TODO: What are the values of x, y, and ref after the above line?
    // Uncomment and fill in the expected values
    // std::cout << "x = " << x << std::endl;  // Expected: ?
    // std::cout << "y = " << y << std::endl;  // Expected: ?
    // std::cout << "ref = " << ref << std::endl;  // Expected: ?
    
    // TODO: What memory address does ref refer to? x's address or y's address?
    // std::cout << "Address of x: " << &x << std::endl;
    // std::cout << "Address of y: " << &y << std::endl;
    // std::cout << "Address ref refers to: " << &ref << std::endl;
}

/*
 * EXERCISE 6: Fix the dangling reference bug
 * This function has a critical bug - find and fix it!
 */
// TODO: This function returns a dangling reference. Fix it!
// Hint: What happens to local variables when function returns?
int& createNumber() {
    int num = 42;
    return num;  // DANGER: What's wrong with this?
}

/*
 * EXERCISE 7: Implement a function that finds the maximum of three numbers
 * Return a reference to the largest one (so it can be modified)
 */
// TODO: Implement findMax to return reference to the largest of three numbers
int& findMax(int& a, int& b, int& c) {
    // Your code here
}

/*
 * EXERCISE 8: Const correctness
 * Implement a function that takes various forms of references
 */
class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

// TODO: Implement to print point coordinates
// Should take const reference (we don't modify the point)
void printPoint(/* Add parameter */) {
    // Your code here
}

// TODO: Implement to move point by dx and dy
// Should take non-const reference (we modify the point)
void movePoint(/* Add parameter */, int dx, int dy) {
    // Your code here
}

/*
 * MAIN FUNCTION - Test your implementations
 */
int main() {
    std::cout << "=== Exercise 1: Swap ===" << std::endl;
    int a = 5, b = 10;
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    swap(a, b);
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;
    // Expected: a = 10, b = 5
    std::cout << std::endl;
    
    std::cout << "=== Exercise 2: Const Reference ===" << std::endl;
    LargeDataSet dataset;
    dataset.data[0] = 100;
    dataset.data[999] = 999;
    dataset.description = "Sample Dataset";
    // TODO: Uncomment after implementing printDataSetInfo
    // printDataSetInfo(dataset);
    std::cout << std::endl;
    
    std::cout << "=== Exercise 3: Range-based For ===" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Before: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    doubleAllValues(numbers);
    std::cout << "After doubling: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << std::endl;
    // Expected: 2 4 6 8 10
    std::cout << std::endl;
    
    std::cout << "=== Exercise 4: Chaining ===" << std::endl;
    Calculator calc;
    int result = calc.add(10).add(5).subtract(3).multiply(2).getResult();
    std::cout << "Result of calc.add(10).add(5).subtract(3).multiply(2): " << result << std::endl;
    // Expected: (10 + 5 - 3) * 2 = 24
    std::cout << std::endl;
    
    std::cout << "=== Exercise 5: Reference Behavior ===" << std::endl;
    // TODO: Uncomment after completing testReferenceBehavior
    // testReferenceBehavior();
    std::cout << std::endl;
    
    std::cout << "=== Exercise 7: Find Max ===" << std::endl;
    int x = 10, y = 25, z = 15;
    int& max = findMax(x, y, z);
    std::cout << "Max of " << x << ", " << y << ", " << z << " is: " << max << std::endl;
    // Expected: 25
    
    max = 100;  // Should modify y since it's the largest
    std::cout << "After setting max to 100, y = " << y << std::endl;
    // Expected: 100
    std::cout << std::endl;
    
    std::cout << "=== Exercise 8: Point Operations ===" << std::endl;
    Point p(10, 20);
    // TODO: Uncomment after implementing printPoint and movePoint
    // printPoint(p);
    // movePoint(p, 5, -3);
    // printPoint(p);
    // Expected: Point(15, 17)
    
    std::cout << "\nAll exercises completed!" << std::endl;
    return 0;
}

/*
 * CHALLENGE EXERCISES (Optional)
 * 
 * 1. Why can't you create an array of references? int& arr[10];
 * 
 * 2. What's the difference between:
 *    const int& ref = x;
 *    int const& ref = x;
 *    int& const ref = x;  // Does this compile?
 * 
 * 3. Can you have a reference to a pointer? int* ptr; int*& ref = ptr;
 * 
 * 4. What happens if you try to create a reference without initialization?
 *    int& ref;  // Try it and see the error
 * 
 * 5. Compare memory usage: pass by value vs reference vs pointer
 *    Use sizeof() to investigate
 */
