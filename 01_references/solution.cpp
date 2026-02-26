#include <iostream>
#include <string>
#include <vector>

/*
 * SOLUTION 1: Implement a swap function using references
 */
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

/*
 * SOLUTION 2: Pass by const reference to avoid copying
 */
struct LargeDataSet {
    int data[1000];
    std::string description;
};

void printDataSetInfo(const LargeDataSet& dataset) {
    std::cout << "Description: " << dataset.description << std::endl;
    std::cout << "First element: " << dataset.data[0] << std::endl;
    std::cout << "Last element: " << dataset.data[999] << std::endl;
}

/*
 * SOLUTION 3: Modify array elements using reference in range-based for
 */
void doubleAllValues(std::vector<int>& vec) {
    for (auto& elem : vec) {
        elem *= 2;
    }
}

/*
 * SOLUTION 4: Return reference for chaining
 */
class Calculator {
private:
    int value;
    
public:
    Calculator() : value(0) {}
    
    Calculator& add(int num) {
        value += num;
        return *this;  // Return reference to current object
    }
    
    Calculator& subtract(int num) {
        value -= num;
        return *this;
    }
    
    Calculator& multiply(int num) {
        value *= num;
        return *this;
    }
    
    int getResult() const {
        return value;
    }
};

/*
 * SOLUTION 5: Understanding reference behavior vs pointers
 */
void testReferenceBehavior() {
    int x = 5;
    int y = 10;
    
    int& ref = x;
    ref = y;  // This assigns the VALUE of y to x (doesn't rebind reference!)
    
    std::cout << "x = " << x << std::endl;  // Expected: 10 (value copied from y)
    std::cout << "y = " << y << std::endl;  // Expected: 10 (unchanged)
    std::cout << "ref = " << ref << std::endl;  // Expected: 10 (still refers to x)
    
    // ref still refers to x's address, not y's
    std::cout << "Address of x: " << &x << std::endl;
    std::cout << "Address of y: " << &y << std::endl;
    std::cout << "Address ref refers to: " << &ref << std::endl;  // Same as &x
}

/*
 * SOLUTION 6: Fix the dangling reference bug
 * 
 * The original function returns a reference to a local variable,
 * which is destroyed when the function returns. This is undefined behavior!
 * 
 * Fix option 1: Return by value instead
 */
int createNumber() {
    int num = 42;
    return num;  // Return by value (copy)
}

/*
 * Fix option 2: Use static variable (but be careful with this approach)
 */
int& createNumberStatic() {
    static int num = 42;  // Static lifetime - exists for program duration
    return num;
}

/*
 * Fix option 3: Take a reference parameter to modify
 */
void createNumberParam(int& num) {
    num = 42;
}

/*
 * SOLUTION 7: Find maximum and return reference
 */
int& findMax(int& a, int& b, int& c) {
    if (a >= b && a >= c) {
        return a;
    } else if (b >= a && b >= c) {
        return b;
    } else {
        return c;
    }
}

/*
 * SOLUTION 8: Const correctness
 */
class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

void printPoint(const Point& p) {
    std::cout << "Point(" << p.x << ", " << p.y << ")" << std::endl;
}

void movePoint(Point& p, int dx, int dy) {
    p.x += dx;
    p.y += dy;
}

/*
 * MAIN FUNCTION - Test implementations
 */
int main() {
    std::cout << "=== Solution 1: Swap ===" << std::endl;
    int a = 5, b = 10;
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    swap(a, b);
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 2: Const Reference ===" << std::endl;
    LargeDataSet dataset;
    dataset.data[0] = 100;
    dataset.data[999] = 999;
    dataset.description = "Sample Dataset";
    printDataSetInfo(dataset);
    std::cout << std::endl;
    
    std::cout << "=== Solution 3: Range-based For ===" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Before: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    doubleAllValues(numbers);
    std::cout << "After doubling: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 4: Chaining ===" << std::endl;
    Calculator calc;
    int result = calc.add(10).add(5).subtract(3).multiply(2).getResult();
    std::cout << "Result of calc.add(10).add(5).subtract(3).multiply(2): " << result << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 5: Reference Behavior ===" << std::endl;
    testReferenceBehavior();
    std::cout << std::endl;
    
    std::cout << "=== Solution 6: Fixed Dangling Reference ===" << std::endl;
    int num = createNumber();  // By value now
    std::cout << "Created number: " << num << std::endl;
    
    int& staticNum = createNumberStatic();
    std::cout << "Static number: " << staticNum << std::endl;
    
    int paramNum;
    createNumberParam(paramNum);
    std::cout << "Param number: " << paramNum << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 7: Find Max ===" << std::endl;
    int x = 10, y = 25, z = 15;
    int& max = findMax(x, y, z);
    std::cout << "Max of " << x << ", " << y << ", " << z << " is: " << max << std::endl;
    
    max = 100;  // Modifies y
    std::cout << "After setting max to 100, y = " << y << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 8: Point Operations ===" << std::endl;
    Point p(10, 20);
    printPoint(p);
    movePoint(p, 5, -3);
    printPoint(p);
    std::cout << std::endl;
    
    std::cout << "All solutions demonstrated!" << std::endl;
    
    // BONUS: Demonstrating const correctness
    std::cout << "\n=== Bonus: Const Correctness ===" << std::endl;
    const Point constPoint(5, 5);
    printPoint(constPoint);  // OK: takes const reference
    // movePoint(constPoint, 1, 1);  // ERROR: cannot pass const to non-const ref
    
    return 0;
}

/*
 * ANSWERS TO CHALLENGE QUESTIONS
 * 
 * 1. Why can't you create an array of references?
 *    - Arrays require elements to be assignable
 *    - References cannot be reassigned after initialization
 *    - This makes arrays of references impossible
 * 
 * 2. const int& ref vs int const& ref vs int& const ref
 *    - const int& ref = x;     // OK: reference to const int
 *    - int const& ref = x;     // OK: same as above (const applies to int)
 *    - int& const ref = x;     // Meaningless: references are always const (cannot rebind)
 *                              // Some compilers accept but ignore it
 * 
 * 3. Can you have a reference to a pointer?
 *    - YES! int* ptr; int*& ref = ptr;
 *    - This is a reference to a pointer
 *    - Useful for functions that modify pointer variables
 * 
 * 4. Reference without initialization
 *    - int& ref;  // ERROR: references must be initialized
 *    - Compiler error: "declaration of reference variable 'ref' requires an initializer"
 * 
 * 5. Memory usage comparison
 *    - sizeof(int) = 4 bytes (the actual int)
 *    - sizeof(int&) = 4 bytes (implementation detail, but references have no overhead in behavior)
 *    - sizeof(int*) = 8 bytes on 64-bit systems (pointer stores memory address)
 *    - Passing by reference typically has same performance as pointer
 *    - Both avoid copying large objects
 */
