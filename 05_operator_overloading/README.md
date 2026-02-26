# Module 05: Operator Overloading

## What C++ Adds: Custom Operators

**C has**: Fixed operator behavior (only for built-in types)
**C++ adds**: Custom operator behavior for user-defined types

## Key Concept

Make your classes behave like built-in types:

```cpp
class Complex {
    double real, imag;
public:
    Complex(double r, double i) : real(r), imag(i) {}
    
    // Operator overloading
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
};

Complex a(1, 2), b(3, 4);
Complex c = a + b;  // Uses operator+! Natural syntax!
```

## Why It Matters

Without operator overloading (like in C):
```c
struct complex add_complex(struct complex a, struct complex b);
struct complex c = add_complex(a, b);  // Verbose
```

With operator overloading (C++):
```cpp
Complex c = a + b;  // Natural, intuitive
```

## Overloadable Operators

**Can overload**: `+ - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= <=> && || ++ -- , ->* -> () []`

**Cannot overload**: `. .* :: ?: sizeof typeid`

## Operator Overloading Forms

### Member Function
```cpp
class Point {
    int x, y;
public:
    // Member function: *this is left operand
    Point operator+(const Point& other) const {
        return Point{x + other.x, y + other.y};
    }
};

Point p1{1, 2}, p2{3, 4};
Point p3 = p1 + p2;  // p1.operator+(p2)
```

### Non-Member Function (Friend)
```cpp
class Complex {
    double real, imag;
    friend Complex operator+(const Complex& a, const Complex& b);
public:
    Complex(double r, double i) : real(r), imag(i) {}
};

Complex operator+(const Complex& a, const Complex& b) {
    return Complex{a.real + b.real, a.imag + b.imag};
}
```

## Common Operators

### Arithmetic Operators
```cpp
class Vector {
    double x, y;
public:
    Vector operator+(const Vector& v) const {
        return Vector{x + v.x, y + v.y};
    }
    
    Vector operator-(const Vector& v) const {
        return Vector{x - v.x, y - v.y};
    }
    
    Vector operator*(double scalar) const {
        return Vector{x * scalar, y * scalar};
    }
};
```

### Comparison Operators
```cpp
class Fraction {
    int num, den;
public:
    bool operator==(const Fraction& other) const {
        return num * other.den == other.num * den;
    }
    
    bool operator<(const Fraction& other) const {
        return num * other.den < other.num * den;
    }
    
    // C++20: Can auto-generate others with <=>
};
```

### Stream Operators (Must be non-member!)
```cpp
class Point {
    int x, y;
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

std::istream& operator>>(std::istream& is, Point& p) {
    return is >> p.x >> p.y;
}

// Usage:
Point p{3, 4};
std::cout << p << std::endl;  // Prints: (3, 4)
```

### Increment/Decrement
```cpp
class Counter {
    int value;
public:
    // Prefix: ++c
    Counter& operator++() {
        ++value;
        return *this;
    }
    
    // Postfix: c++ (dummy int parameter distinguishes)
    Counter operator++(int) {
        Counter temp = *this;
        ++value;
        return temp;
    }
};
```

### Subscript Operator
```cpp
class Array {
    int data[10];
public:
    int& operator[](size_t index) {  // For modification
        return data[index];
    }
    
    const int& operator[](size_t index) const {  // For const access
        return data[index];
    }
};

Array arr;
arr[0] = 42;  // Uses non-const version
int x = arr[0];  // Uses non-const version

const Array carr;
int y = carr[0];  // Uses const version
```

### Function Call Operator (Functors)
```cpp
class Multiplier {
    int factor;
public:
    Multiplier(int f) : factor(f) {}
    
    int operator()(int value) const {
        return value * factor;
    }
};

Multiplier times3(3);
int result = times3(10);  // Calls operator()(10), returns 30
```

## Assignment Operator
```cpp
class String {
    char* data;
public:
    // Copy assignment
    String& operator=(const String& other) {
        if (this != &other) {  // Self-assignment check
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        return *this;  // Return *this for chaining
    }
};
```

## Best Practices

1. **Return types**: Match expected behavior
   - `operator+` returns new object
   - `operator+=` returns reference to modified object
   - `operator++` prefix returns reference, postfix returns copy

2. **Const correctness**
   - Operators that don't modify should be `const`
   - Take parameters by `const&` when possible

3. **Symmetry**
   - If `a + b` works, `b + a` should too (use non-member functions)

4. **Related operators**
   - If you define `==`, define `!=`
   - If you define `<`, consider defining `<=`, `>`, `>=`

5. **Stream operators**
   - Must be non-member functions
   - Return reference to stream for chaining

## Common Pitfalls

```cpp
// DON'T: Unexpected behavior
class Counter {
    int value;
public:
    // DON'T make + modify the object!
    Counter& operator+(int n) {  // BAD
        value += n;
        return *this;
    }
};

// DO: Expected behavior
class Counter {
    int value;
public:
    Counter operator+(int n) const {  // GOOD
        return Counter{value + n};
    }
};
```

## Spaceship Operator (C++20)

```cpp
class Point {
    int x, y;
public:
    auto operator<=>(const Point& other) const = default;
    // Auto-generates: <, <=, >, >=, ==, !=
};
```

## Next Module

**06_inheritance**: Operator overloading works with inheritance and polymorphism.
