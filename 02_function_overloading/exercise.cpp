#include <iostream>
#include <string>
#include <vector>
#include <cmath>

/*
 * EXERCISE 1: Create overloaded max functions
 * Create overloads for int, double, and string (lexicographic comparison)
 */
// TODO: Implement max for int
int max(int a, int b) {
    // Your code here
}

// TODO: Implement max for double
double max(double a, double b) {
    // Your code here
}

// TODO: Implement max for strings
std::string max(const std::string& a, const std::string& b) {
    // Your code here
}

/*
 * EXERCISE 2: Overload for different number of parameters
 * Create multiply functions for 2, 3, and 4 parameters
 */
// TODO: Multiply two integers
int multiply(int a, int b) {
    // Your code here
}

// TODO: Multiply three integers
int multiply(int a, int b, int c) {
    // Your code here
}

// TODO: Multiply four integers
int multiply(int a, int b, int c, int d) {
    // Your code here
}

/*
 * EXERCISE 3: Const correctness with overloading
 * Create two versions: one for modifiable, one for const
 */
class Data {
public:
    int value;
    Data(int v) : value(v) {}
};

// TODO: Implement display for non-const Data (should also increment value)
void display(Data& data) {
    // Your code here
    // Print value and increment it
}

// TODO: Implement display for const Data (read-only)
void display(const Data& data) {
    // Your code here
    // Just print value
}

/*
 * EXERCISE 4: Distance function overloading
 * Calculate distance in different coordinate systems
 */
// TODO: Implement distance for 1D (absolute difference)
double distance(double x1, double x2) {
    // Your code here
}

// TODO: Implement distance for 2D (Euclidean)
double distance(double x1, double y1, double x2, double y2) {
    // Your code here
    // Use sqrt((x2-x1)^2 + (y2-y1)^2)
}

// TODO: Implement distance for 3D
double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    // Your code here
}

/*
 * EXERCISE 5: Format output differently based on type
 */
// TODO: Implement format for integers (add commas)
std::string format(int value) {
    // Your code here
    // For simplicity, just prefix with "INT: "
}

// TODO: Implement format for doubles (2 decimal places)
std::string format(double value) {
    // Your code here
    // For simplicity, just prefix with "DOUBLE: "
}

// TODO: Implement format for booleans (true/false as strings)
std::string format(bool value) {
    // Your code here
}

/*
 * EXERCISE 6: Pointer constness overloading
 */
// TODO: Implement getValue for non-const pointer (can modify)
void getValue(int* ptr, int newValue) {
    // Your code here
    // Set *ptr to newValue
}

// TODO: Implement getValue for const pointer (read-only)
int getValue(const int* ptr) {
    // Your code here
    // Return *ptr
}

/*
 * EXERCISE 7: Predict the output
 * For each call, determine which overload is called
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
    // TODO: Before running, write down which function you think will be called
    
    test(5);           // Which overload?
    test(5.0);         // Which overload?
    test(5, 10);       // Which overload?
    
    char c = 'A';
    test(c);           // Which overload? (char promotes to ?)
    
    float f = 2.5f;
    test(f);           // Which overload? (float promotes to ?)
    
    short s = 100;
    test(s);           // Which overload? (short promotes to ?)
}

/*
 * EXERCISE 8: Error detection
 * Some of these function declarations will cause errors. Find and fix them!
 */

// TODO: Identify which of these are valid overloads and fix the invalid ones

// Set 1: Return type differences
int compute(int x) { return x * 2; }
// double compute(int x) { return x * 2.0; }  // Is this valid?

// Set 2: Parameter name differences
void process(int value) { std::cout << "A: " << value << std::endl; }
// void process(int number) { std::cout << "B: " << number << std::endl; }  // Is this valid?

// Set 3: Const parameters (by value)
void handle(int x) { std::cout << "C: " << x << std::endl; }
// void handle(const int x) { std::cout << "D: " << x << std::endl; }  // Is this valid?

// Set 4: Const with references (different!)
void modify(int& ref) { ref++; }
void modify(const int& ref) { std::cout << ref << std::endl; }  // Is this valid?

/*
 * MAIN FUNCTION
 */
int main() {
    std::cout << "=== Exercise 1: Max Functions ===" << std::endl;
    std::cout << "max(5, 10) = " << max(5, 10) << std::endl;
    std::cout << "max(3.14, 2.71) = " << max(3.14, 2.71) << std::endl;
    std::cout << "max(\"apple\", \"banana\") = " << max(std::string("apple"), std::string("banana")) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Exercise 2: Multiply Overloads ===" << std::endl;
    std::cout << "multiply(2, 3) = " << multiply(2, 3) << std::endl;
    std::cout << "multiply(2, 3, 4) = " << multiply(2, 3, 4) << std::endl;
    std::cout << "multiply(2, 3, 4, 5) = " << multiply(2, 3, 4, 5) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Exercise 3: Const Overloading ===" << std::endl;
    Data d1(10);
    const Data d2(20);
    
    std::cout << "Non-const Data:" << std::endl;
    display(d1);
    display(d1);  // Value should increment each time
    
    std::cout << "Const Data:" << std::endl;
    display(d2);
    display(d2);  // Value should NOT change
    std::cout << std::endl;
    
    std::cout << "=== Exercise 4: Distance Calculations ===" << std::endl;
    std::cout << "1D distance(5, 10) = " << distance(5.0, 10.0) << std::endl;
    std::cout << "2D distance(0, 0, 3, 4) = " << distance(0.0, 0.0, 3.0, 4.0) << std::endl;
    std::cout << "3D distance(0, 0, 0, 1, 1, 1) = " << distance(0.0, 0.0, 0.0, 1.0, 1.0, 1.0) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Exercise 5: Format Functions ===" << std::endl;
    std::cout << format(12345) << std::endl;
    std::cout << format(3.14159) << std::endl;
    std::cout << format(true) << std::endl;
    std::cout << format(false) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Exercise 6: Pointer Constness ===" << std::endl;
    int val = 50;
    const int constVal = 100;
    
    getValue(&val, 75);
    std::cout << "After getValue(&val, 75), val = " << val << std::endl;
    
    std::cout << "getValue(&constVal) = " << getValue(&constVal) << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Exercise 7: Predict Output ===" << std::endl;
    predictOutput();
    std::cout << std::endl;
    
    std::cout << "All exercises completed!" << std::endl;
    return 0;
}

/*
 * CHALLENGE QUESTIONS:
 * 
 * 1. Can you overload based on return type alone? Why or why not?
 * 
 * 2. What happens with this call?
 *    void func(int x, double y);
 *    void func(double x, int y);
 *    func(5, 10);  // What error occurs?
 * 
 * 3. Are these valid overloads?
 *    void f(int* p);
 *    void f(int p[]);
 *    void f(int p[10]);
 * 
 * 4. What's the difference between:
 *    void g(const int x);    // Const by value
 *    void g(const int& x);   // Const by reference
 *    Which can be overloaded with void g(int x)?
 * 
 * 5. How does the compiler resolve overloads?
 *    What are the steps in overload resolution?
 */
