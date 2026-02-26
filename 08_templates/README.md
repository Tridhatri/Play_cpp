# Module 08: Templates

## What C++ Adds: Compile-Time Generic Programming

**C has**: Macros (text substitution) or void* (type-unsafe)
**C++ adds**: Templates (type-safe, compile-time generics)

## Key Concept

Write code once, use with any type:

```cpp
// Function template
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int i = max(5, 10);           // Instantiates max<int>
double d = max(3.14, 2.71);   // Instantiates max<double>
std::string s = max(std::string("apple"), std::string("banana"));
```

## Why Not Macros?

```c
// C approach with macro
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int x = 5;
int y = MAX(x++, 10);  // BUG: x incremented twice!
// Expands to: ((x++) > (10) ? (x++) : (10))
```

```cpp
// C++ template - type safe, no double evaluation
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int x = 5;
int y = max(x++, 10);  // Safe: x++ evaluated once
```

## Function Templates

### Basic Syntax
```cpp
template<typename T>  // or template<class T>
T add(T a, T b) {
    return a + b;
}

// Explicit instantiation
int result = add<int>(5, 10);

// Type deduction
int result = add(5, 10);  // Compiler deduces T = int
```

### Multiple Template Parameters
```cpp
template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {  // C++11 trailing return type
    return a * b;
}

// C++14: simpler
template<typename T, typename U>
auto multiply(T a, U b) {
    return a * b;
}

auto result = multiply(5, 3.14);  // T=int, U=double, returns double
```

### Template Specialization
```cpp
// Primary template
template<typename T>
void print(T value) {
    std::cout << value << std::endl;
}

// Specialization for const char*
template<>
void print<const char*>(const char* value) {
    std::cout << "String: " << value << std::endl;
}

print(42);          // Uses primary template
print("hello");     // Uses specialization
```

## Class Templates

```cpp
template<typename T>
class Stack {
private:
    std::vector<T> elements;
    
public:
    void push(const T& elem) {
        elements.push_back(elem);
    }
    
    T pop() {
        T elem = elements.back();
        elements.pop_back();
        return elem;
    }
    
    bool empty() const {
        return elements.empty();
    }
};

// Usage:
Stack<int> intStack;
intStack.push(5);
intStack.push(10);

Stack<std::string> stringStack;
stringStack.push("hello");
```

### Class Template Specialization
```cpp
// Primary template
template<typename T>
class Container {
public:
    void info() { std::cout << "Generic container\n"; }
};

// Full specialization
template<>
class Container<bool> {
public:
    void info() { std::cout << "Specialized for bool\n"; }
};

Container<int> c1;   // Uses primary template
Container<bool> c2;  // Uses specialization
```

### Partial Specialization (Classes Only)
```cpp
// Primary template
template<typename T, typename U>
class Pair {
public:
    void info() { std::cout << "Two different types\n"; }
};

// Partial specialization: both types the same
template<typename T>
class Pair<T, T> {
public:
    void info() { std::cout << "Two same types\n"; }
};

// Partial specialization: second type is pointer
template<typename T, typename U>
class Pair<T, U*> {
public:
    void info() { std::cout << "Second is pointer\n"; }
};

Pair<int, double> p1;  // Primary
Pair<int, int> p2;     // Same-type specialization
Pair<int, double*> p3; // Pointer specialization
```

## Non-Type Template Parameters

```cpp
template<typename T, int SIZE>
class Array {
private:
    T data[SIZE];
    
public:
    int size() const { return SIZE; }
    
    T& operator[](int index) { return data[index]; }
};

Array<int, 10> arr1;   // Array of 10 ints
Array<double, 20> arr2;  // Different type - totally different class!
```

## Template Type Deduction

```cpp
template<typename T>
void func(T param);

int x = 42;
const int cx = x;
const int& rx = x;

func(x);   // T = int
func(cx);  // T = int (const dropped)
func(rx);  // T = int (const& dropped)

// To preserve const:
template<typename T>
void func(const T& param);

func(x);   // T = int, param is const int&
func(cx);  // T = int, param is const int&
```

## Variadic Templates (C++11)

```cpp
// Base case
void print() {
    std::cout << std::endl;
}

// Recursive case
template<typename T, typename... Args>
void print(T first, Args... rest) {
    std::cout << first << " ";
    print(rest...);  // Recursive call
}

print(1, 2.5, "hello", 'c');
// Output: 1 2.5 hello c
```

## SFINAE (Substitution Failure Is Not An Error)

```cpp
template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
processNumber(T value) {
    std::cout << "Integer: " << value << std::endl;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
processNumber(T value) {
    std::cout << "Float: " << value << std::endl;
}

processNumber(42);      // Calls integral version
processNumber(3.14);    // Calls floating-point version
```

## Concepts (C++20)

Cleaner syntax for template constraints:

```cpp
// Old way (C++11/14)
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
add(T a, T b) {
    return a + b;
}

// New way (C++20)
template<std::integral T>
T add(T a, T b) {
    return a + b;
}

// Or define custom concepts
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
T multiply(T a, T b) {
    return a * b;
}
```

## Template Instantiation

**Key difference from C macros**: Templates are compiled!

```cpp
template<typename T>
void func(T x) {
    x.nonexistent();  // Will only error if func is instantiated
}

// No error yet - template not instantiated

// func(42);  // NOW we get error: int has no member 'nonexistent'
```

**Implicit instantiation**: When you use the template
**Explicit instantiation**: Force instantiation

```cpp
template void func<int>(int);  // Explicit instantiation
```

## Comparison with C

| Feature | C | C++ Templates |
|---------|---|---------------|
| **Generics** | Macros or void* | Type-safe templates |
| **Type checking** | Runtime (void*) | Compile-time |
| **Code bloat** | Manual duplication | Automatic (but controlled) |
| **Performance** | Macros: fast; void*: slow | Zero-cost abstraction |
| **Errors** | Runtime crashes | Compile-time errors |

### C Example (void* Generic)
```c
void* max(void* a, void* b, int (*compare)(void*, void*)) {
    return compare(a, b) > 0 ? a : b;
}
// Type-unsafe, verbose, error-prone
```

## Common Use Cases

1. **Containers**: `vector<T>`, `map<K, V>`
2. **Algorithms**: `sort`, `find`, `transform`
3. **Smart pointers**: `unique_ptr<T>`, `shared_ptr<T>`
4. **Type traits**: `is_integral<T>`, `is_pointer<T>`
5. **Meta-programming**: Compile-time computations

## Best Practices

1. **Prefer templates over macros** for type-generic code
2. **Use concepts (C++20)** for clearer constraints
3. **Keep templates in headers** (definition must be visible)
4. **Use explicit** for single-arg template constructors
5. **Consider compilation time** (templates can slow builds)

## Next Module

**09_stl_containers**: Standard Template Library - production-ready template containers.
