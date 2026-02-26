#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

/*
 * SOLUTION 1: Overloaded max functions
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

std::string max(const std::string& a, const std::string& b) {
    return (a > b) ? a : b;
}

/*
 * SOLUTION 2: Multiply overloads
 */
int multiply(int a, int b) {
    return a * b;
}

int multiply(int a, int b int c) {
    return a * b * c;
}

int multiply(int a, int b, int c, int d) {
    return a * b * c * d;
}

/*
 * SOLUTION 3: Const correctness
 */
class Data {
public:
    int value;
    Data(int v) : value(v) {}
};

void display(Data& data) {
    std::cout << "Non-const display: value = " << data.value;
    data.value++;
    std::cout << " (incremented to " << data.value << ")" << std::endl;
}

void display(const Data& data) {
    std::cout << "Const display: value = " << data.value << " (read-only)" << std::endl;
}

/*
 * SOLUTION 4: Distance calculations
 */
double distance(double x1, double x2) {
    return std::abs(x2 - x1);
}

double distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return std::sqrt(dx*dx + dy*dy);
}

double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dz = z2 - z1;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

/*
 * SOLUTION 5: Format functions
 */
std::string format(int value) {
    return "INT: " + std::to_string(value);
}

std::string format(double value) {
    std::ostringstream oss;
    oss << "DOUBLE: " << std::fixed << std::setprecision(2) << value;
    return oss.str();
}

std::string format(bool value) {
    return value ? "BOOL: true" : "BOOL: false";
}

/*
 * SOLUTION 6: Pointer constness
 */
void getValue(int* ptr, int newValue) {
    std::cout << "Non-const pointer: setting value to " << newValue << std::endl;
    *ptr = newValue;
}

int getValue(const int* ptr) {
    std::cout << "Const pointer: reading value" << std::endl;
    return *ptr;
}

/*
 * SOLUTION 7: Predict output
 */
void test(int x) {
    std::cout << "test(int)" << std::endl;
}

void test(double x) {
    std::cout << "test(double)" << std::endl;
}

void test(int x, int y) {
    std::cout << "test(int, int)" << std::endl;
}

void predictOutput() {
    test(5);           // test(int) - exact match
    test(5.0);         // test(double) - exact match
    test(5, 10);       // test(int, int) - exact match
    
    char c = 'A';
    test(c);           // test(int) - char promotes to int
    
    float f = 2.5f;
    test(f);           // test(double) - float promotes to double
    
    short s = 100;
    test(s);           // test(int) - short promotes to int
}

/*
 * SOLUTION 8: Error detection
 */

// Set 1: Return type differences
int compute(int x) { return x * 2; }
// INVALID: Cannot overload on return type alone
// Fix: Remove one or change parameter types

// Set 2: Parameter name differences
void process(int value) { std::cout << "A: " << value << std::endl; }
// INVALID: Parameter names don't affect signature
// Fix: This is a redefinition error - remove one

// Set 3: Const parameters (by value)
void handle(int x) { std::cout << "C: " << x << std::endl; }
// INVALID: Top-level const on pass-by-value doesn't create different signature
// Fix: Remove one or use reference/pointer

// Set 4: Const with references
void modify(int& ref) { ref++; }
void modify(const int& ref) { std::cout << ref << std::endl; }
// VALID: Const matters for references and pointers!

/*
 * MAIN FUNCTION
 */
int main() {
    std::cout << "=== Solution 1: Max Functions ===" << std::endl;
    std::cout << "max(5, 10) = " << max(5, 10) << std::endl;
    std::cout << "max(3.14, 2.71) = " << max(3.14, 2.71) << std::endl;
    std::cout << "max(\"apple\", \"banana\") = " << max(std::string("apple"), std::string("banana")) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 2: Multiply Overloads ===" << std::endl;
    std::cout << "multiply(2, 3) = " << multiply(2, 3) << std::endl;
    std::cout << "multiply(2, 3, 4) = " << multiply(2, 3, 4) << std::endl;
    std::cout << "multiply(2, 3, 4, 5) = " << multiply(2, 3, 4, 5) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 3: Const Overloading ===" << std::endl;
    Data d1(10);
    const Data d2(20);
    
    std::cout << "Non-const Data:" << std::endl;
    display(d1);
    display(d1);
    
    std::cout << "Const Data:" << std::endl;
    display(d2);
    display(d2);
    std::cout << std::endl;
    
    std::cout << "=== Solution 4: Distance Calculations ===" << std::endl;
    std::cout << "1D distance(5, 10) = " << distance(5.0, 10.0) << std::endl;
    std::cout << "2D distance(0, 0, 3, 4) = " << distance(0.0, 0.0, 3.0, 4.0) << std::endl;
    std::cout << "3D distance(0, 0, 0, 1, 1, 1) = " << distance(0.0, 0.0, 0.0, 1.0, 1.0, 1.0) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 5: Format Functions ===" << std::endl;
    std::cout << format(12345) << std::endl;
    std::cout << format(3.14159) << std::endl;
    std::cout << format(true) << std::endl;
    std::cout << format(false) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 6: Pointer Constness ===" << std::endl;
    int val = 50;
    const int constVal = 100;
    
    getValue(&val, 75);
    std::cout << "After getValue(&val, 75), val = " << val << std::endl;
    
    std::cout << "getValue(&constVal) = " << getValue(&constVal) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 7: Predict Output ===" << std::endl;
    predictOutput();
    std::cout << std::endl;
    
    std::cout << "All solutions demonstrated!" << std::endl;
    return 0;
}

/*
 * ANSWERS TO CHALLENGE QUESTIONS:
 * 
 * 1. Cannot overload on return type alone
 *    - Reason: At call site, compiler might not know expected return type
 *    - Example: int x = func(); Could be any return type!
 *    - The function call itself determines which overload, not the assignment
 * 
 * 2. Ambiguity error
 *    func(5, 10) is ambiguous because:
 *    - func(int, double) requires converting second arg: int->double
 *    - func(double, int) requires converting first arg: int->double
 *    - Both require exactly 1 conversion, so neither is better
 * 
 * 3. NOT valid overloads
 *    void f(int* p);
 *    void f(int p[]);    // Same as int* p
 *    void f(int p[10]);  // Still same as int* p (array size ignored!)
 *    Arrays decay to pointers in function parameters
 * 
 * 4. Top-level const doesn't create overload
 *    void g(int x);
 *    void g(const int x);      // INVALID: same as above (top-level const ignored)
 *    void g(const int& x);     // VALID: different signature (reference)
 *    
 *    Only void g(const int& x) can be overloaded with void g(int x)
 * 
 * 5. Overload resolution steps:
 *    a) Find candidate functions (same name, visible in scope)
 *    b) Filter to viable functions (can be called with given arguments)
 *    c) Find best match:
 *       1. Exact match (no conversions)
 *       2. Promotion (char->int, float->double)
 *       3. Standard conversion (int->double, derived->base)
 *       4. User-defined conversion
 *    d) If multiple functions tie for best, it's ambiguous (compile error)
 */
