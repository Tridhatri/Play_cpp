# Module 11: Exception Handling

## What C++ Adds: Structured Exception Handling

**C has**: Error codes (return values, errno, setjmp/longjmp)
**C++ adds**: try-catch-throw mechanism with RAII integration

## Key Concept

Handle errors without cluttering code with error checks:

```cpp
// C approach
int processFile(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return ERROR_OPEN;
    
    char* buffer = malloc(1024);
    if (!buffer) {
        fclose(f);
        return ERROR_MEMORY;
    }
    
    if (fread(buffer, 1, 1024, f) < 0) {
        free(buffer);
        fclose(f);
        return ERROR_READ;
    }
    
    // ... more error checking ...
    
    free(buffer);
    fclose(f);
    return SUCCESS;
}

// C++ approach
void processFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }
    
    std::vector<char> buffer(1024);  // RAII
    file.read(buffer.data(), buffer.size());
    
    if (file.fail()) {
        throw std::runtime_error("Read error");
    }
    
    // Resources automatically cleaned up!
}
```

## Basic Syntax

```cpp
try {
    // Code that might throw
    throw std::runtime_error("Something went wrong");
}
catch (const std::runtime_error& e) {
    // Handle runtime_error
    std::cout << "Error: " << e.what() << std::endl;
}
catch (const std::exception& e) {
    // Handle any std::exception
    std::cout << "Exception: " << e.what() << std::endl;
}
catch (...) {
    // Catch everything else
    std::cout << "Unknown exception\n";
}
```

## Throwing Exceptions

### Throw by Value
```cpp
throw std::runtime_error("Error message");
throw std::invalid_argument("Invalid input");
throw 42;  // Can throw any type (but don't!)
```

### Standard Exception Hierarchy
```cpp
std::exception                    // Base class
├── std::logic_error
│   ├── std::invalid_argument
│   ├── std::domain_error
│   ├── std::length_error
│   └── std::out_of_range
├── std::runtime_error
│   ├── std::range_error
│   ├── std::overflow_error
│   └── std::underflow_error
├── std::bad_alloc               // new failed
├── std::bad_cast                // dynamic_cast failed
└── std::bad_exception
```

### Custom Exceptions
```cpp
class FileError : public std::runtime_error {
public:
    FileError(const std::string& msg) 
        : std::runtime_error(msg) {}
};

class FileNotFoundError : public FileError {
public:
    FileNotFoundError(const std::string& filename)
        : FileError("File not found: " + filename) {}
};

throw FileNotFoundError("config.txt");
```

## Catching Exceptions

### Catch by const Reference (Preferred)
```cpp
try {
    // ...
}
catch (const std::exception& e) {  // Catches by reference
    std::cout << e.what() << std::endl;
}
```

**Why const reference?**
- Avoids slicing (polymorphism works)
- No copying
- Can catch derived types

### Catch Order Matters
```cpp
try {
    throw std::out_of_range("index error");
}
catch (const std::exception& e) {
    // Catches all std::exception (including out_of_range)
    std::cout << "General exception\n";
}
catch (const std::out_of_range& e) {
    // Never reached! (more specific handler should come first)
    std::cout << "Out of range\n";
}

// CORRECT order:
try {
    throw std::out_of_range("index error");
}
catch (const std::out_of_range& e) {  // More specific first
    std::cout << "Out of range\n";
}
catch (const std::exception& e) {     // More general later
    std::cout << "General exception\n";
}
```

## Stack Unwinding

When exception is thrown, stack is unwound:
- Local objects are destroyed (destructors called)
- Continues until matching catch block found
- **RAII makes this powerful**: Resources automatically cleaned up!

```cpp
void func() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);  // RAII
    std::vector<int> vec = {1, 2, 3};                      // RAII
    
    someOperationThatMightThrow();
    
    // If exception thrown above:
    // - vec destructor called (memory freed)
    // - ptr destructor called (int* deleted)
    // No memory leaks!
}
```

## Exception Safety Guarantees

### 1. No-throw Guarantee (Strongest)
```cpp
void func() noexcept {  // Promises never to throw
    // ...
}
```

### 2. Strong Guarantee
Operation succeeds or has no effect (transactional):
```cpp
void Vector::push_back(const T& value) {
    // If adding fails, vector unchanged
}
```

### 3. Basic Guarantee
If exception thrown, object in valid (but unspecified) state:
```cpp
void modify(std::vector<int>& vec) {
    vec.clear();
    // If exception here, vec is valid but empty
}
```

### 4. No Guarantee
Might leak resources or corrupt state (BAD)

## noexcept Specifier (C++11)

```cpp
void func() noexcept {  // Guaranteed not to throw
    // If exception escapes, std::terminate() called
}

void func2() noexcept(true) {  // Same as noexcept
}

void func3() noexcept(false) {  // May throw (default)
}

// Conditional noexcept
template<typename T>
void swap(T& a, T& b) noexcept(std::is_nothrow_move_constructible_v<T>) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}
```

**Benefits**:
- Compiler can optimize better
- Move constructors should be noexcept (enables optimizations)
- Indicates intent

**Important**: Destructors are implicitly noexcept!

## RAII and Exceptions

Perfect combination:

```cpp
class FileHandle {
    FILE* file;
public:
    FileHandle(const char* name) {
        file = fopen(name, "r");
        if (!file) throw std::runtime_error("Open failed");
    }
    
    ~FileHandle() {
        if (file) fclose(file);  // Always called, even with exceptions
    }
    
    void read() {
        // ... might throw ...
    }
};

void processFile() {
    FileHandle file("data.txt");  // RAII
    file.read();  // If this throws, FileHandle destructor still called!
}  // File automatically closed
```

## Rethrowing Exceptions

```cpp
try {
    // ...
}
catch (const std::exception& e) {
    std::cerr << "Caught: " << e.what() << std::endl;
    throw;  // Rethrow same exception (preserves type!)
}

// DON'T do this:
catch (const std::exception& e) {
    throw e;  // Throws copy (slicing if e is derived type!)
}
```

## Function Try Blocks

Catch exceptions from constructor initializer list:

```cpp
class MyClass {
    Resource resource;
public:
    MyClass(const std::string& name)
    try : resource(name) {  // Function try block
        // Constructor body
    }
    catch (const std::exception& e) {
        // Handle exception from resource construction
        std::cerr << "Failed to create resource: " << e.what() << std::endl;
        throw;  // Must rethrow or throw new exception
    }
};
```

## When to Use Exceptions

**Good use cases**:
- Constructor failures (can't return error code)
- Deep call stacks (avoid error propagation through every function)
- Exceptional conditions (not normal control flow)
- Library code (let user decide how to handle)

**Bad use cases**:
- Normal control flow (e.g., loop termination)
- Performance-critical code (exceptions have overhead)
- Interfacing with C code (C doesn't understand exceptions)

## Comparison with C

| Feature | C | C++ Exceptions |
|---------|---|----------------|
| **Error reporting** | Return codes, errno | throw/catch |
| **Stack cleanup** | Manual (easy to forget) | Automatic (stack unwinding) |
| **Deep call stacks** | Error codes through every function | Direct to handler |
| **Resource cleanup** | Manual (error-prone) | RAII (automatic) |
| **Type safety** | Type-unsafe (int codes) | Type-safe (exception objects) |
| **Performance** | Fast (no overhead) | Overhead when thrown |

### C Error Handling Example
```c
int func1() {
    int err = func2();
    if (err != 0) {
        cleanup();
        return err;  // Propagate error
    }
    return 0;
}

int func2() {
    int err = func3();
    if (err != 0) {
        cleanup();
        return err;  // Propagate error
    }
    return 0;
}
```

### C++ Exception Handling Example
```cpp
void func1() {
    func2();  // No error checking needed
}  // Automatic cleanup via RAII

void func2() {
    func3();  // Exception automatically propagates
}

void func3() {
    throw std::runtime_error("Error");  // Thrown once, caught once
}
```

## Best Practices

1. **Throw by value, catch by const reference**
2. **Use standard exceptions** when appropriate
3. **Make destructors noexcept** (they already are by default)
4. **Use RAII** for resource management
5. **Don't use exceptions for normal control flow**
6. **Document exceptions** in function comments
7. **Catch specific exceptions** before general ones
8. **Be exception-safe**: Provide at least basic guarantee

## Common Pitfalls

### 1. Exception in Destructor
```cpp
// BAD: might call std::terminate()
~MyClass() {
    someOperationThatMightThrow();  // DANGER!
}

// GOOD: catch and handle
~MyClass() noexcept {
    try {
        someOperationThatMightThrow();
    }
    catch (...) {
        // Log error,but don't rethrow
    }
}
```

### 2. Not Catching by Reference
```cpp
// BAD: Slicing!
catch (std::exception e) {  // Copies, loses derived info
}

// GOOD:
catch (const std::exception& e) {  // No slicing
}
```

### 3. Empty Catch Blocks
```cpp
// BAD: Swallowing exceptions
try {
    // ...
}
catch (...) {
    // Silent failure - hard to debug!
}

// GOOD: At least log it
catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    // Maybe rethrow or handle
}
```

## Next Module

**12_lambda_expressions**: Inline functions for callbacks and algorithms.
