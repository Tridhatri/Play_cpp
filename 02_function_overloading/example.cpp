#include <iostream>
#include <string>
#include <vector>

// Example 1: Basic overloading - same operation on different types
void print(int value) {
    std::cout << "Integer: " << value << std::endl;
}

void print(double value) {
    std::cout << "Double: " << value << std::endl;
}

void print(const std::string& value) {
    std::cout << "String: " << value << std::endl;
}

void print(const char* value) {
    std::cout << "C-string: " << value << std::endl;
}

// Example 2: Different number of parameters
int add(int a, int b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

double add(double a, double b) {
    return a + b;
}

// Example 3: Const overloading with references
void processString(std::string& str) {
    std::cout << "Non-const version: Modifying string" << std::endl;
    str += " (modified)";
}

void processString(const std::string& str) {
    std::cout << "Const version: Read-only access to: " << str << std::endl;
}

// Example 4: Overload resolution demonstration
void demonstrate(int x) {
    std::cout << "demonstrate(int): " << x << std::endl;
}

void demonstrate(double x) {
    std::cout << "demonstrate(double): " << x << std::endl;
}

void demonstrate(int x, int y) {
    std::cout << "demonstrate(int, int): " << x << ", " << y << std::endl;
}

// Example 5: Pointer vs const pointer overloading
void modify(int* ptr) {
    std::cout << "Non-const pointer: can modify value" << std::endl;
    *ptr = 100;
}

void modify(const int* ptr) {
    std::cout << "Const pointer: read-only access to " << *ptr << std::endl;
    // *ptr = 100;  // ERROR: cannot modify
}

// Example 6: Reference vs value (less common, but possible with const)
class BigObject {
public:
    int data[1000];
    BigObject() { std::cout << "BigObject constructed" << std::endl; }
    BigObject(const BigObject&) { std::cout << "BigObject copied (expensive!)" << std::endl; }
};

void process(BigObject obj) {
    std::cout << "Passed by value (copy made)" << std::endl;
}

void process(const BigObject& obj) {
    std::cout << "Passed by const reference (no copy)" << std::endl;
}

int main() {
    std::cout << "=== Example 1: Type-based Overloading ===" << std::endl;
    print(42);                  // Calls print(int)
    print(3.14159);             // Calls print(double)
    print(std::string("C++"));  // Calls print(const std::string&)
    print("Hello");             // Calls print(const char*)
    std::cout << std::endl;
    
    std::cout << "=== Example 2: Different Number of Parameters ===" << std::endl;
    std::cout << "add(5, 10) = " << add(5, 10) << std::endl;
    std::cout << "add(5, 10, 15) = " << add(5, 10, 15) << std::endl;
    std::cout << "add(2.5, 3.7) = " << add(2.5, 3.7) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Example 3: Const Overloading ===" << std::endl;
    std::string mutableStr = "Hello";
    const std::string constStr = "World";
    
    processString(mutableStr);   // Calls non-const version
    std::cout << "Result: " << mutableStr << std::endl;
    
    processString(constStr);     // Calls const version
    std::cout << std::endl;
    
    std::cout << "=== Example 4: Overload Resolution ===" << std::endl;
    demonstrate(5);              // Exact match: demonstrate(int)
    demonstrate(5.5);            // Exact match: demonstrate(double)
    demonstrate(5, 10);          // Exact match: demonstrate(int, int)
    
    short s = 3;
    demonstrate(s);              // Promotion: short -> int
    
    float f = 2.5f;
    demonstrate(f);              // Promotion: float -> double
    std::cout << std::endl;
    
    std::cout << "=== Example 5: Pointer Constness ===" << std::endl;
    int value = 42;
    const int constValue = 99;
    
    modify(&value);              // Calls non-const version
    std::cout << "value after modify: " << value << std::endl;
    
    modify(&constValue);         // Calls const version
    std::cout << std::endl;
    
    std::cout << "=== Example 6: Type Promotions ===" << std::endl;
    // Demonstrating what types call what functions
    char ch = 'A';
    print(ch);                   // char promotes to int
    
    bool b = true;
    print(b);                    // bool converts to int (1)
    
    float fl = 1.5f;
    print(fl);                   // float promotes to double
    std::cout << std::endl;
    
    std::cout << "=== Example 7: Ambiguity Example ===" << std::endl;
    // This would be ambiguous if we had:
    // void ambiguous(int x, double y);
    // void ambiguous(double x, int y);
    // ambiguous(5, 10);  // ERROR: which one? Both need 1 conversion
    std::cout << "See comments in code for ambiguity examples" << std::endl;
    std::cout << std::endl;
    
    std::cout << "All examples completed!" << std::endl;
    return 0;
}

/*
 * Additional Notes:
 * 
 * 1. Name Mangling: The compiler converts function names into unique symbols
 *    print(int) might become: _Z5printi
 *    print(double) might become: _Z5printd
 *    This allows linking to work properly
 * 
 * 2. extern "C": Disables name mangling for C compatibility
 *    extern "C" void func(int x);  // Won't be mangled
 * 
 * 3. Can't overload on return type alone:
 *    int getValue();
 *    double getValue();  // ERROR
 * 
 * 4. Arrays decay to pointers:
 *    void func(int arr[]);
 *    void func(int* arr);     // Same signature!
 *    void func(int arr[10]);  // Still same! Size ignored
 */
