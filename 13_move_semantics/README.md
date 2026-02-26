# Module 13: Move Semantics

## What C++ Adds: Efficient Resource Transfer

**C has**: Only copying (memcpy, assignment)
**C++ adds**: Move semantics (transfer ownership without copying)

## Key Concept

**Copying** is expensive for resource-owning objects:
```cpp
std::vector<int> v1(1000000);  // 1 million elements
std::vector<int> v2 = v1;      // COPY: allocates new memory, copies all elements
```

**Moving** transfers ownership:
```cpp
std::vector<int> v1(1000000);  // 1 million elements
std::vector<int> v2 = std::move(v1);  // MOVE: just steals v1's pointer!
// v1 is now empty, v2 owns the data
```

## L-values vs R-values

### L-value
Has a name, persistent, has an address:
```cpp
int x = 10;      // x is an l-value
int* ptr = &x;   // Can take address
x = 20;          // Can appear on left of =
```

### R-value
Temporary, no name, can't take address:
```cpp
int x = 10 + 5;  // (10 + 5) is an r-value (temporary)
// int* ptr = &(10 + 5);  // ERROR: can't take address
```

**Simple rule**: If you can take its address (`&`), it's an l-value. Otherwise, r-value.

```cpp
int x = 10;          // x is l-value
int y = x + 5;       // (x + 5) is r-value
std::string s = "hi";              // s is l-value
std::string t = "hello" + s;       // ("hello" + s) is r-value
std::vector<int> v = createVector();  // createVector() returns r-value
```

## R-value References

**L-value reference**: `Type&` (binds to l-values)
**R-value reference**: `Type&&` (binds to r-values)

```cpp
int x = 10;

int& lref = x;       // OK: l-value reference to l-value
// int& lref2 = 10;  // ERROR: can't bind l-value ref to r-value

int&& rref = 10;     // OK: r-value reference to r-value
// int&& rref2 = x;  // ERROR: can't bind r-value ref to l-value

// Exception: const l-value ref can bind to r-value
const int& cref = 10;  // OK: const ref extends lifetime
```

## Move Constructor

```cpp
class MyVector {
    int* data;
    size_t size;
    
public:
    // Regular constructor
    MyVector(size_t n) : data(new int[n]), size(n) {
        std::cout << "Constructor\n";
    }
    
    // Copy constructor (expensive)
    MyVector(const MyVector& other) : data(new int[other.size]), size(other.size) {
        std::copy(other.data, other.data + size, data);
        std::cout << "Copy constructor (expensive!)\n";
    }
    
    // Move constructor (cheap!)
    MyVector(MyVector&& other) noexcept 
        : data(other.data), size(other.size) {
        
        other.data = nullptr;  // Leave other in valid state
        other.size = 0;
        std::cout << "Move constructor (cheap!)\n";
    }
    
    ~MyVector() {
        delete[] data;
    }
};

MyVector createVector() {
    return MyVector(1000000);  // Returns r-value
}

MyVector v1 = createVector();  // Move constructor called! (not copy)
```

## Move Assignment Operator

```cpp
class MyVector {
    int* data;
    size_t size;
    
public:
    // Move assignment
    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] data;           // Free current resources
            
            data = other.data;       // Steal other's resources
            size = other.size;
            
            other.data = nullptr;    // Leave other in valid state
            other.size = 0;
        }
        return *this;
    }
};

MyVector v1(1000);
MyVector v2(2000);
v1 = std::move(v2);  // Move assignment (v2's resources transferred to v1)
```

## std::move

**std::move** is just a cast to r-value reference:

```cpp
template<typename T>
T&& move(T& arg) {
    return static_cast<T&&>(arg);
}
```

**It doesn't move anything!** It just says "this object can be moved from."

```cpp
std::string s1 = "Hello";
std::string s2 = std::move(s1);  // s1 cast to r-value ref → move constructor

// s1 is now in "valid but unspecified state" (typically empty)
// DON'T use s1 after move! (except to assign new value or destroy)
```

## When Move Happens Automatically

### 1. Returning Local Variables (RVO/NRVO)
```cpp
MyVector createVector() {
    MyVector v(1000);
    return v;  // Move (or elided entirely via RVO)
}
```

### 2. Returning Temporary
```cpp
MyVector createVector() {
    return MyVector(1000);  // Move or RVO
}
```

### 3. Passing to Function (with std::move)
```cpp
void takeVector(MyVector v);  // Takes by value

MyVector v(1000);
takeVector(std::move(v));  // Move v into function
```

### 4. STL Containers
```cpp
std::vector<MyVector> vec;
MyVector v(1000);

vec.push_back(v);              // Copy
vec.push_back(std::move(v));   // Move (v is empty after)

vec.emplace_back(1000);        // Construct in-place (best!)
```

## Rule of Five (C++11)

If you define ANY of these, consider defining ALL:
1. Destructor
2. Copy constructor
3. Copy assignment operator
4. Move constructor
5. Move assignment operator

```cpp
class Resource {
    int* data;
    
public:
    // 1. Destructor
    ~Resource() {
        delete[] data;
    }
    
    // 2. Copy constructor
    Resource(const Resource& other) {
        data = new int[other.size];
        std::copy(other.data, other.data + size, data);
    }
    
    // 3. Copy assignment
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data;
            data = new int[other.size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }
    
    // 4. Move constructor
    Resource(Resource&& other) noexcept 
        : data(other.data) {
        other.data = nullptr;
    }
    
    // 5. Move assignment
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};
```

## Rule of Zero (Preferred)

Don't define any if you can use RAII types:

```cpp
class Resource {
    std::vector<int> data;  // Handles everything automatically!
    std::unique_ptr<int> ptr;  // No manual memory management
    
    // No destructor, copy/move constructors needed!
    // Compiler-generated ones work perfectly
};
```

## noexcept on Move Operations

**Critical**: Move constructors/assignments should be `noexcept`

```cpp
MyClass(MyClass&& other) noexcept {  // Always noexcept!
    // ...
}

MyClass& operator=(MyClass&& other) noexcept {  // Always noexcept!
    // ...
}
```

**Why?** STL containers use move only if it's `noexcept`:

```cpp
std::vector<MyClass> vec;

// If move constructor is noexcept:
vec.resize(1000);  // Uses move constructor (fast!)

// If move constructor can throw:
vec.resize(1000);  // Uses copy constructor (slow!) for strong exception guarantee
```

## Perfect Forwarding

Preserve l-value/r-value nature when forwarding:

```cpp
template<typename T>
void wrapper(T&& arg) {  // Universal reference (forwarding reference)
    actualFunction(std::forward<T>(arg));  // Perfect forwarding
}

void actualFunction(int& x) { std::cout << "L-value\n"; }
void actualFunction(int&& x) { std::cout << "R-value\n"; }

int a = 10;
wrapper(a);    // Calls actualFunction(int&)
wrapper(10);   // Calls actualFunction(int&&)
```

**std::forward**: Conditional cast (casts to r-value only if arg was r-value)

## Universal References (Forwarding References)

`T&&` in template context can bind to both l-value and r-value:

```cpp
template<typename T>
void func(T&& arg);  // Universal reference, NOT r-value reference!

int x = 10;
func(x);    // T deduced as int&, arg is int&
func(10);   // T deduced as int, arg is int&&
```

**Rules**:
- `T&&` where T is template parameter: Universal reference
- `Type&&` where Type is concrete: R-value reference

```cpp
void f1(std::vector<int>&& v);  // R-value reference (Type is concrete)

template<typename T>
void f2(std::vector<T>&& v);    // R-value reference! (T is template, but vector<T> isn't)

template<typename T>
void f3(T&& v);                 // Universal reference
```

## Move-Only Types

Some types can only be moved, not copied:

```cpp
std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
// std::unique_ptr<int> ptr2 = ptr1;  // ERROR: can't copy

std::unique_ptr<int> ptr2 = std::move(ptr1);  // OK: move
// ptr1 is now nullptr

std::thread t1([]() { /* work */ });
// std::thread t2 = t1;  // ERROR: can't copy
std::thread t2 = std::move(t1);  // OK: move
```

## When to Use std::move

**DO use std::move when**:
```cpp
// 1. Transferring ownership
std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
std::unique_ptr<int> ptr2 = std::move(ptr1);

// 2. Last use of local variable
std::string name = "Alice";
Person p(std::move(name));  // name not used after this

// 3. Passing to function that takes ownership
void takeOwnership(std::unique_ptr<int> ptr);
takeOwnership(std::move(myPtr));

// 4. Implementing move operations
MyClass& operator=(MyClass&& other) {
    member = std::move(other.member);
    return *this;
}
```

**DON'T use std::move**:
```cpp
// 1. On const objects (does nothing!)
const std::string s = "hello";
std::string t = std::move(s);  // Copies! Can't move from const

// 2. On return values (RVO does it automatically)
MyClass func() {
    MyClass obj;
    return std::move(obj);  // WRONG! Prevents RVO
}

MyClass func() {
    MyClass obj;
    return obj;  // Correct: RVO or automatic move
}

// 3. When you'll use the object again
std::string s = "hello";
func(std::move(s));
std::cout << s << std::endl;  // BAD: s is in unspecified state!
```

## Comparison with C

| Feature | C | C++ Move Semantics |
|---------|---|--------------------|
| **Transfer ownership** | Manual pointer assignment | Move constructor/assignment |
| **Efficiency** | memcpy or manual | Cheap pointer swap |
| **Safety** | Easy to double-free | Moved-from object left in safe state |
| **Return values** | Always copy or pointer | RVO or move (cheap) |
| **Temporaries** | Wasted copies | Automatically moved |

### C Example
```c
struct Buffer {
    char* data;
    size_t size;
};

// Transfer ownership manually
struct Buffer transfer(struct Buffer* from) {
    struct Buffer result = *from;
    from->data = NULL;  // Manual "move"
    from->size = 0;
    return result;      // Still copies struct
}
```

### C++ Example
```cpp
class Buffer {
    char* data;
    size_t size;
public:
    Buffer(Buffer&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
};

Buffer transfer(Buffer&& from) {
    return std::move(from);  // Efficient move
}
```

## Performance Impact

### Before Move Semantics (C++03)
```cpp
std::vector<std::string> createVector() {
    std::vector<std::string> result;
    result.push_back("data");
    return result;  // Copies entire vector!
}
```

### With Move Semantics (C++11+)
```cpp
std::vector<std::string> createVector() {
    std::vector<std::string> result;
    result.push_back("data");
    return result;  // Moves vector (cheap!)
}
```

**Benchmark**: Returning million-element vector
- Copy: ~100ms
- Move: ~0.001ms (100,000x faster!)

## Best Practices

1. **Make move operations noexcept** whenever possible
2. **Use Rule of Zero** (prefer RAII types)
3. **Use std::move only when transferring ownership**
4. **Don't std::move on return** (prevents RVO)
5. **Pass by value + move** for sink functions
6. **Never use moved-from objects** (except destroy/assign)

## Common Pitfalls

### 1. Using Object After Move
```cpp
std::string s = "hello";
std::string t = std::move(s);
std::cout << s << std::endl;  // BAD: s is in unspecified state!

// OK: Reassign before use
s = "world";
std::cout << s << std::endl;  // OK
```

### 2. Moving from const
```cpp
const std::string s = "hello";
std::string t = std::move(s);  // Does nothing! Calls copy constructor
```

### 3. Returning std::move
```cpp
// BAD:
MyClass func() {
    MyClass obj;
    return std::move(obj);  // Prevents RVO!
}

// GOOD:
MyClass func() {
    MyClass obj;
    return obj;  // Compiler handles it
}
```

### 4. Forgetting noxcept
```cpp
// BAD: std::vector won't use this move constructor!
MyClass(MyClass&& other) {  // Missing noexcept
    // ...
}

// GOOD:
MyClass(MyClass&& other) noexcept {
    // ...
}
```

## Summary

Move semantics enables:
- **Efficient resource transfer** (no copying)
- **Move-only types** (unique_ptr, thread)
- **RVO optimization**
- **Perfect forwarding**
- **Faster STL containers** (vector, map, etc.)

This is why C++11 move semantics is one of the biggest improvements to C++!

---

**Congratulations!** You've completed all 13 modules. You now know the key C++ features that differentiate it from C. Practice these concepts extensively to master modern C++!
