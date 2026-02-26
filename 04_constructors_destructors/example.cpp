#include <iostream>
#include <cstring>

// Example 1: Basic constructors and destructor
class Demo {
private:
    int value;
    std::string name;
    
public:
    // Default constructor
    Demo() : value(0), name("default") {
        std::cout << "Default constructor called" << std::endl;
    }
    
    // Parameterized constructor
    Demo(int v, const std::string& n) : value(v), name(n) {
        std::cout << "Parameterized constructor: " << name << std::endl;
    }
    
    // Copy constructor
    Demo(const Demo& other) : value(other.value), name(other.name) {
        std::cout << "Copy constructor: copying " << name << std::endl;
    }
    
    // Destructor
    ~Demo() {
        std::cout << "Destructor called for " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Value: " << value << ", Name: " << name << std::endl;
    }
};

// Example 2: RAII Pattern
class DynamicArray {
private:
    int* data;
    size_t size;
    
public:
    // Constructor acquires resource
    DynamicArray(size_t n) : size(n), data(new int[n]) {
        std::cout << "Allocated array of size " << size << std::endl;
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }
    
    // Destructor releases resource
    ~DynamicArray() {
        std::cout << "Freeing array of size " << size << std::endl;
        delete[] data;
    }
    
    // Copy constructor (deep copy)
    DynamicArray(const DynamicArray& other) : size(other.size), data(new int[other.size]) {
        std::cout << "Deep copying array" << std::endl;
        std::copy(other.data, other.data + size, data);
    }
    
    int& operator[](size_t index) { return data[index]; }
    const int& operator[](size_t index) const { return data[index]; }
    size_t getSize() const { return size; }
};

// Example 3: Constructor delegation
class Point {
private:
    int x, y;
    
public:
    Point() : Point(0, 0) {  // Delegate to 2-param constructor
        std::cout << "Default constructor (delegated)" << std::endl;
    }
    
    Point(int val) : Point(val, val) {  // Delegate
        std::cout << "1-param constructor (delegated)" << std::endl;
    }
    
    Point(int xVal, int yVal) : x(xVal), y(yVal) {
        std::cout << "2-param constructor: (" << x << ", " << y << ")" << std::endl;
    }
};

// Example 4: Explicit constructor
class Integer {
private:
    int value;
    
public:
    explicit Integer(int v) : value(v) {
        std::cout << "Explicit constructor: " << value << std::endl;
    }
    
    int get() const { return value; }
};

void takeInteger(Integer i) {
    std::cout << "Function received: " << i.get() << std::endl;
}

int main() {
    std::cout << "=== Example 1: Constructor/Destructor Calls ===" << std::endl;
    {
        Demo d1;                        // Default constructor
        Demo d2(42, "test");           // Parameterized
        Demo d3 = d2;                  // Copy constructor
    }  // All destructors called here
    std::cout << std::endl;
    
    std::cout << "=== Example 2: RAII Pattern ===" << std::endl;
    {
        DynamicArray arr(5);
        arr[0] = 10;
        arr[1] = 20;
        std::cout << "arr[0] = " << arr[0] << std::endl;
        
        DynamicArray arr2 = arr;  // Copy constructor (deep copy)
        arr2[0] = 99;
        std::cout << "After modifying copy:" << std::endl;
        std::cout << "arr[0] = " << arr[0] << ", arr2[0] = " << arr2[0] << std::endl;
    }  // Resources automatically freed
    std::cout << std::endl;
    
    std::cout << "=== Example 3: Constructor Delegation ===" << std::endl;
    Point p1;
    Point p2(5);
    Point p3(3, 4);
    std::cout << std::endl;
    
    std::cout << "=== Example 4: Explicit Constructor ===" << std::endl;
    Integer i1(42);         // OK
    // Integer i2 = 42;     // ERROR: implicit conversion prevented
    // takeInteger(42);     // ERROR: can't implicitly convert
    takeInteger(Integer(42));  // OK: explicit conversion
    std::cout << std::endl;
    
    return 0;
}
