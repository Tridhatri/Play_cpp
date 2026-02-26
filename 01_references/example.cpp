#include <iostream>
#include <string>

// Example 1: Pass by value vs pass by reference
void incrementByValue(int x) {
    x++;  // Only modifies local copy
    std::cout << "Inside incrementByValue: " << x << std::endl;
}

void incrementByReference(int& x) {
    x++;  // Modifies the original variable
    std::cout << "Inside incrementByReference: " << x << std::endl;
}

void incrementByPointer(int* x) {
    (*x)++;  // C-style: requires dereferencing
    std::cout << "Inside incrementByPointer: " << *x << std::endl;
}

// Example 2: Const references for read-only access (avoids copying)
void printExpensiveData(const std::string& str) {
    // str is not copied, but we can't modify it
    std::cout << "String (by const ref): " << str << std::endl;
    // str += " modified";  // ERROR: cannot modify const reference
}

// Example 3: Returning a reference (useful for chaining)
class Counter {
private:
    int count;
public:
    Counter() : count(0) {}
    
    // Return reference to enable chaining
    Counter& increment() {
        count++;
        return *this;  // return reference to self
    }
    
    int getCount() const { return count; }
};

// Example 4: Reference vs Pointer comparison
void demonstrateReferences() {
    std::cout << "=== Example 1: Pass by Value vs Reference ===" << std::endl;
    int num = 10;
    
    std::cout << "Original value: " << num << std::endl;
    incrementByValue(num);
    std::cout << "After incrementByValue: " << num << std::endl;  // Still 10
    
    incrementByReference(num);
    std::cout << "After incrementByReference: " << num << std::endl;  // Now 11
    
    incrementByPointer(&num);
    std::cout << "After incrementByPointer: " << num << std::endl;  // Now 12
    
    std::cout << std::endl;
}

void demonstrateConstReferences() {
    std::cout << "=== Example 2: Const References ===" << std::endl;
    std::string longString = "This is a very long string that we don't want to copy";
    printExpensiveData(longString);  // Efficient: no copy made
    
    std::cout << std::endl;
}

void demonstrateReferenceBehavior() {
    std::cout << "=== Example 3: Reference is an Alias ===" << std::endl;
    int original = 42;
    int& ref = original;  // ref is just another name for original
    
    std::cout << "original = " << original << ", ref = " << ref << std::endl;
    
    ref = 100;  // Modifying through reference
    std::cout << "After ref = 100:" << std::endl;
    std::cout << "original = " << original << ", ref = " << ref << std::endl;
    
    original = 200;  // Modifying original
    std::cout << "After original = 200:" << std::endl;
    std::cout << "original = " << original << ", ref = " << ref << std::endl;
    
    // They share the same address
    std::cout << "Address of original: " << &original << std::endl;
    std::cout << "Address of ref: " << &ref << std::endl;
    
    std::cout << std::endl;
}

void demonstrateChaining() {
    std::cout << "=== Example 4: Returning References for Chaining ===" << std::endl;
    Counter c;
    
    // Method chaining is possible because increment() returns a reference
    c.increment().increment().increment();
    std::cout << "Count after chaining: " << c.getCount() << std::endl;
    
    std::cout << std::endl;
}

void demonstrateConstReferenceToTemporary() {
    std::cout << "=== Example 5: Const Ref to Temporary ===" << std::endl;
    
    // This works! Const reference extends lifetime of temporary
    const int& ref = 5 + 10;
    std::cout << "Const ref to temporary (5 + 10): " << ref << std::endl;
    
    // int& ref2 = 5 + 10;  // ERROR: non-const reference cannot bind to temporary
    
    std::cout << std::endl;
}

void demonstrateReferenceVsPointer() {
    std::cout << "=== Example 6: Reference vs Pointer Comparison ===" << std::endl;
    
    int x = 10, y = 20;
    
    // Pointer can be reassigned
    int* ptr = &x;
    std::cout << "Pointer points to: " << *ptr << std::endl;
    ptr = &y;  // Reassign to different variable
    std::cout << "Pointer now points to: " << *ptr << std::endl;
    
    // Reference cannot be reassigned
    int& ref = x;
    std::cout << "Reference refers to: " << ref << std::endl;
    ref = y;  // This assigns the VALUE of y to x (doesn't rebind reference!)
    std::cout << "After ref = y, reference still refers to x: " << ref << std::endl;
    std::cout << "But x's value changed to: " << x << std::endl;
    
    std::cout << std::endl;
}

int main() {
    demonstrateReferences();
    demonstrateConstReferences();
    demonstrateReferenceBehavior();
    demonstrateChaining();
    demonstrateConstReferenceToTemporary();
    demonstrateReferenceVsPointer();
    
    std::cout << "All examples completed!" << std::endl;
    return 0;
}
