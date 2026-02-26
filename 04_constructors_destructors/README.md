# Module 04: Constructors & Destructors

## What C++ Adds: Automatic Initialization and Cleanup

**C has**: Manual initialization via functions
**C++ adds**: Constructors (automatic init) and Destructors (automatic cleanup)

## Key Concept: RAII

**RAII** = Resource Acquisition Is Initialization
- Constructor acquires resources (memory, files, locks)
- Destructor releases resources
- Automatic, exception-safe resource management

## Constructors

Special member functions that initialize objects:

```cpp
class Point {
private:
    int x, y;
    
public:
    // Default constructor
    Point() : x(0), y(0) {
        std::cout << "Default constructor" << std::endl;
    }
    
    // Parameterized constructor
    Point(int xVal, int yVal) : x(xVal), y(yVal) {
        std::cout << "Parameterized constructor" << std::endl;
    }
    
    // Copy constructor
    Point(const Point& other) : x(other.x), y(other.y) {
        std::cout << "Copy constructor" << std::endl;
    }
};

// Usage:
Point p1;          // Calls default constructor
Point p2(3, 4);    // Calls parameterized constructor
Point p3 = p2;     // Calls copy constructor
Point p4{5, 6};    // Uniform initialization (C++11)
```

## Member Initializer Lists

**Preferred way** to initialize members (more efficient than assignment):

```cpp
class Example {
private:
    const int constValue;
    int& refValue;
    std::string name;
    
public:
    // CORRECT: Use member initializer list
    Example(int val, int& ref, const std::string& n)
        : constValue(val), refValue(ref), name(n) {
        // Body can contain additional logic
    }
    
    // WON'T COMPILE: const and references must be initialized in list
    /*
    Example(int val, int& ref, const std::string& n) {
        constValue = val;  // ERROR: can't assign to const
        refValue = ref;    // ERROR: reference already bound
        name = n;          // Works but less efficient (constructs then assigns)
    }
    */
};
```

 ## Destructors

Called automatically when object is destroyed:

```cpp
class File {
private:
    FILE* handle;
    std::string filename;
    
public:
    File(const char* name) : filename(name) {
        handle = fopen(name, "r");
        std::cout << "Opened " << filename << std::endl;
    }
    
    ~File() {  // Destructor
        if (handle) {
            fclose(handle);
            std::cout << "Closed " << filename << std::endl;
        }
    }
};

{
    File f("data.txt");  // Constructor called
    // Use file...
}  // Destructor called automatically here!
```

## When Destructors Are Called

- Local objects: When scope ends
- Dynamically allocated: When `delete` is called
- Global/static: At program end
- Members: When containing object is destroyed

## Rule of Three

If you define ANY of these, you should probably define ALL:
1. Destructor
2. Copy constructor
3. Copy assignment operator

```cpp
class Array {
private:
    int* data;
    size_t size;
    
public:
    // Constructor
    Array(size_t n) : size(n), data(new int[n]) {}
    
    // Destructor (1)
    ~Array() {
        delete[] data;
    }
    
    // Copy constructor (2)
    Array(const Array& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + size, data);
    }
    
    // Copy assignment (3)
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
        }        return *this;
    }
};
```

## Rule of Five (C++11)

Adds move operations for efficiency:
4. Move constructor
5. Move assignment operator

(Covered in Module 13: Move Semantics)

## Constructor Delegation (C++11)

```cpp
class Point {
private:
    int x, y;
    
public:
    Point() : Point(0, 0) {  // Delegate to other constructor
    }
    
    Point(int xVal) : Point(xVal, 0) {
    }
    
    Point(int xVal, int yVal) : x(xVal), y(yVal) {
        // Main initialization logic here
    }
};
```

## Explicit Constructors

Prevent implicit conversions:

```cpp
class Integer {
private:
    int value;
    
public:
    explicit Integer(int v) : value(v) {}
};

Integer i1(42);      // OK
Integer i2 = 42;     // ERROR: implicit conversion disabled by explicit
Integer i3{42};      // OK: direct initialization
void func(Integer i);
func(42);            // ERROR: can't implicitly convert
func(Integer(42));   // OK: explicit conversion
```

## Default and Deleted Functions (C++11)

```cpp
class NonCopyable {
public:
    NonCopyable() = default;  // Use compiler-generated default
    NonCopyable(const NonCopyable&) = delete;  // Disable copying
    NonCopyable& operator=(const NonCopyable&) = delete;
};
```

## Comparison with C

| Feature | C | C++ |
|---------|---|-----|
| Initialization | Manual function calls | Automatic constructors |
| Cleanup | Manual function calls | Automatic destructors |
| Resource safety | Easy to forget | RAII guarantees cleanup |
| Copy behavior | Manual implementation | Copy constructor |
| Const members | N/A | Must init in constructor list |

## Common Patterns

### RAII for Resource Management
```cpp
class Lock {
    mutex& m;
public:
    Lock(mutex& mtx) : m(mtx) { m.lock(); }
    ~Lock() { m.unlock(); }
};
// Guaranteed unlock even with exceptions!
```

### Factory Functions
```cpp
class Complex {
public:
    static Complex fromPolar(double r, double theta);
    static Complex fromCartesian(double real, double imag);
};
```

## Next Module

**05_operator_overloading**: Constructors enable conversion operators and implicit conversions.
