# Module 12: Lambda Expressions

## What C++ Adds: Anonymous Functions with Closures

**C has**: Function pointers only (no state capture)
**C++ adds**: Lambda expressions (inline functions with captured variables)

## Key Concept

Create inline nameless functions on the spot:

```cpp
// C approach: separate function
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
qsort(array, size, sizeof(int), compare);

// C++ approach: lambda inline
std::sort(vec.begin(), vec.end(), 
    [](int a, int b) { return a < b; }  // Lambda!
);
```

## Basic Syntax

```cpp
[capture](parameters) -> return_type {
    // body
}
```

Example:
```cpp
auto lambda = [](int x, int y) -> int {
    return x + y;
};

int result = lambda(3, 4);  // Calls the lambda, result = 7
```

**Type deduction**: Return type usually inferred
```cpp
auto lambda = [](int x, int y) {  // return type deduced
    return x + y;
};
```

## Capture Clauses

### No Capture `[]`
```cpp
auto lambda = [](int x) {
    return x * 2;
};
```

### Capture by Value `[=]`
```cpp
int multiplier = 3;
auto lambda = [=](int x) {  // Captures multiplier by value
    return x * multiplier;
};

multiplier = 5;
int result = lambda(10);  // result = 30 (not 50!)
```

### Capture by Reference `[&]`
```cpp
int count = 0;
auto lambda = [&]() {  // Captures count by reference
    count++;
};

lambda();
lambda();
std::cout << count << std::endl;  // Output: 2
```

### Capture Specific Variables
```cpp
int x = 10, y = 20;

[x]() {}       // Capture x by value
[&x]() {}      // Capture x by reference
[x, &y]() {}   // x by value, y by reference
[=, &y]() {}   // All by value except y by reference
[&, x]() {}    // All by reference except x by value
```

### Capture `this` (Member Functions)
```cpp
class Counter {
    int count = 0;
public:
    void increment() {
        auto lambda = [this]() {  // Capture this pointer
            count++;  // Access member variable
        };
        lambda();
    }
};
```

### C++14: Init Capture (Generalized Lambda Capture)
```cpp
int x = 5;
auto lambda = [value = x + 1]() {  // Capture expression
    return value;
};

// Move-only captures
auto ptr = std::make_unique<int>(42);
auto lambda2 = [ptr = std::move(ptr)]() {  // Move into lambda
    return *ptr;
};
```

### C ++20: Template Lambdas
```cpp
auto lambda = []<typename T>(T value) {  // Template parameter
    return value * 2;
};

lambda(5);      // T = int
lambda(3.14);   // T = double
```

## Mutable Lambdas

By default, captured-by-value variables are const:

```cpp
int x = 10;
auto lambda = [x]() {
    // x++;  // ERROR: x is const
    return x;
};

// Make it mutable:
auto lambda2 = [x]() mutable {
    x++;  // OK: modifies captured copy
    return x;
};

lambda2();  // Returns 11
lambda2();  // Returns 12
// Original x is still 10!
```

## Lambda Return Types

### Auto-Deduced
```cpp
auto lambda = [](int x) {
    return x * 2;  // Deduced as int
};
```

### Explicit
```cpp
auto lambda = [](int x) -> double {
    return x * 2.0;
};
```

### Multiple Returns (Need Explicit)
```cpp
auto lambda = [](bool flag) -> int {  // Explicit needed
    if (flag) return 1;
    return 2;
};
```

## Lambdas with STL Algorithms

### Sort
```cpp
std::vector<int> vec = {3, 1, 4, 1, 5};
std::sort(vec.begin(), vec.end(), 
    [](int a, int b) { return a > b; }  // Descending order
);
```

### Find_if
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
auto it = std::find_if(vec.begin(), vec.end(),
    [](int x) { return x > 3; }
);
```

### Transform
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
std::vector<int> doubled(vec.size());

std::transform(vec.begin(), vec.end(), doubled.begin(),
    [](int x) { return x * 2; }
);
```

### Count_if
```cpp
int count = std::count_if(vec.begin(), vec.end(),
    [](int x) { return x % 2 == 0; }  // Count even numbers
);
```

### For_each
```cpp
std::for_each(vec.begin(), vec.end(),
    [](int x) { std::cout << x << " "; }
);
```

## Generic Lambdas (C++14)

```cpp
auto lambda = [](auto x, auto y) {  // Template-like
    return x + y;
};

lambda(5, 10);          // int + int
lambda(3.14, 2.71);     // double + double
lambda(std::string("Hello, "), std::string("World!"));  // string + string
```

## Lambda as Function Arguments

### Using std::function
```cpp
#include <functional>

void executeOperation(std::function<int(int, int)> op, int a, int b) {
    std::cout << "Result: " << op(a, b) << std::endl;
}

executeOperation([](int x, int y) { return x + y; }, 5, 3);  // 8
executeOperation([](int x, int y) { return x * y; }, 5, 3);  // 15
```

### Template Parameter (Preferred - No Overhead)
```cpp
template<typename Func>
void executeOperation(Func op, int a, int b) {
    std::cout << "Result: " << op(a, b) << std::endl;
}

executeOperation([](int x, int y) { return x + y; }, 5, 3);
```

## Immediately Invoked Lambda Expression (IILE)

```cpp
int result = []() {
    int temp = 0;
    for (int i = 0; i < 10; ++i) {
        temp += i;
    }
    return temp;
}();  // Called immediately

std::cout << result << std::endl;  // 45
```

**Use case**: Complex initialization of const variables:
```cpp
const int value = [&]() {
    if (condition) return 10;
    else return 20;
}();
```

## Recursive Lambdas (C++14)

```cpp
std::function<int(int)> factorial = [&factorial](int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
};

std::cout << factorial(5) << std::endl;  // 120

// C++14: Using auto
auto factorial2 = [](int n) {
    auto impl = [](int n, auto& self) -> int {
        return n <= 1 ? 1 : n * self(n - 1, self);
    };
    return impl(n, impl);
};
```

## Lambda Captures in Detail

```cpp
int a = 1, b = 2, c = 3;

[=]() {  }        // Capture all by value
[&]() {  }        // Capture all by reference
[a, &b]() {  }    // a by value, b by reference
[=, &b]() {  }    // All by value except b by reference
[&, a]() {  }     // All by reference except a by value
[this]() {  }     // Capture this pointer
[*this]() {  }    // C++17: Capture copy of *this
```

## Stateless Lambdas → Function Pointers

Lambdas with no captures convert to function pointers:

```cpp
void takeCallback(int (*func)(int)) {
    std::cout << func(5) << std::endl;
}

// Stateless lambda converts to function pointer
takeCallback([](int x) { return x * 2; });  // OK!

// Stateful lambda CANNOT convert
int multiplier = 3;
// takeCallback([multiplier](int x) { return x * multiplier; });  // ERROR
```

## Comparison with C

| Feature | C | C++ Lambdas |
|---------|---|-------------|
| **Anonymous functions** | No | Yes |
| **State capture** | Manual (structs) | Automatic (closures) |
| **Inline definition** | No (must define separately) | Yes |
| **Type safety** | void* casts | Fully type-safe |
| **Syntax** | Verbose | Concise |

### C Example (Callback with State)
```c
struct Context {
    int multiplier;
};

void callback(int value, void* context) {
    struct Context* ctx = (struct Context*)context;
    printf("%d\n", value * ctx->multiplier);
}

struct Context ctx = {3};
foreach(array, size, callback, &ctx);  // Pass context manually
```

### C++ Example (Lambda with Capture)
```cpp
int multiplier = 3;
std::for_each(vec.begin(), vec.end(),
    [multiplier](int value) {  // Captures multiplier automatically
        std::cout << value * multiplier << std::endl;
    }
);
```

## Performance

- **Stateless lambdas**: Zero overhead (can inline)
- **Captured lambdas**: Small object created (usually stack-allocated)
- **std::function**: Type erasure, virtual dispatch overhead

**Tip**: Use auto or template parameters for lambdas to avoid std::function overhead.

## Common Use Cases

1. **STL Algorithms**: Custom comparators, predicates, transformations
2. **Callbacks**: Event handlers, async operations
3. **Lazy Evaluation**: Defer computation
4. **IILE**: Complex initialization
5. **Thread creation**: `std::thread([]() { /* work */ })`

## Best Practices

1. **Prefer lambdas over function objects** for simple cases
2. **Be careful with `[=]` and `[&]`**: Be explicit when possible
3. **Avoid `[=]` with `this`**: Leads to confusion (use `[this]` explicitly)
4. **Use `mutable` sparingly**: Usually indicates design issue
5. **Prefer `auto` over `std::function`**: Better performance
6. **Document complex captures**

## Common Pitfalls

### 1. Dangling References
```cpp
auto makeLambda() {
    int local = 42;
    return [&local]() { return local; };  // DANGER: captures local by ref!
}

auto lambda = makeLambda();
// lambda uses dangling reference!
```

### 2. Capturing `this` in Member Functions
```cpp
class Widget {
    int value = 42;
public:
    auto getLambda() {
        return [=]() { return value; };  // Captures 'this', not 'value'!
    }
};
```

**Fix**: Use `[*this]` (C++17) to capture copy of object.

### 3. Default Capture with Specific
```cpp
int x = 1, y = 2;
// [=, x]() {};  // ERROR: x already captured by =
[=, &y]() {};    // OK: All by value except y
```

## Next Module

**13_move_semantics**: Efficient resource transfer (move constructors  often used with lambdas).
