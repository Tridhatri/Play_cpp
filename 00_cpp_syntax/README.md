# Module 00: C++ Syntax — What's New Beyond C

## What C++ Adds: Core Syntax Differences

**C has**: A procedural language with manual everything
**C++ adds**: A multi-paradigm language with richer syntax, type safety, and built-in abstractions

This module covers the **syntactic and language-level** features C++ introduces over C — things you'll encounter immediately when reading or writing C++ code. Later modules dive deeper into OOP, templates, and modern C++.

---

## 1. Namespaces

C has a single global namespace. Name collisions are managed with prefixes (e.g., `SDL_CreateWindow`). C++ introduces **namespaces** to scope identifiers.

```cpp
namespace Math {
    double pi = 3.14159;
    double square(double x) { return x * x; }
}

namespace Physics {
    double pi = 3.14159265;  // No conflict with Math::pi
}

// Usage
double area = Math::pi * Math::square(5.0);
```

### `using` Declarations

```cpp
using std::cout;       // Import a single name
using namespace std;   // Import everything (avoid in headers!)
```

> **C equivalent**: There is none. You'd use naming conventions like `math_square()`.

---

## 2. `iostream` — Type-Safe I/O

C uses `printf`/`scanf` with format specifiers (`%d`, `%s`). Type mismatches are silent bugs. C++ provides **stream-based I/O** that is type-safe.

```cpp
#include <iostream>

int x = 42;
double pi = 3.14;
std::string name = "Alice";

// Output — no format specifiers needed
std::cout << "x = " << x << ", pi = " << pi << ", name = " << name << std::endl;

// Input
std::cin >> x;
std::getline(std::cin, name);  // Read a full line
```

| Feature | C (`printf`/`scanf`) | C++ (`iostream`) |
|---------|---------------------|------------------|
| Type safety | No (format mismatch = UB) | Yes (compile-time) |
| Extensibility | No | Yes (overload `operator<<`) |
| Localization | Limited | Stream locales |

> You can still use `printf` in C++, and many projects do for performance. But `iostream` is idiomatic.

---

## 3. `std::string` — A Real String Type

C has null-terminated `char` arrays. C++ provides `std::string` with automatic memory management.

```cpp
#include <string>

std::string greeting = "Hello";
greeting += ", World!";              // Concatenation
std::cout << greeting.length();      // 13
std::string sub = greeting.substr(0, 5);  // "Hello"

if (greeting == "Hello, World!") {   // Direct comparison (no strcmp!)
    // ...
}
```

| Operation | C | C++ |
|-----------|---|-----|
| Create | `char s[50] = "hi";` | `std::string s = "hi";` |
| Concatenate | `strcat(s, " there");` | `s += " there";` |
| Compare | `strcmp(a, b) == 0` | `a == b` |
| Length | `strlen(s)` | `s.length()` |
| Copy | `strcpy(dst, src);` | `dst = src;` |
| Find | `strstr(hay, needle)` | `hay.find(needle)` |

---

## 4. `bool` Type

C (before C99) had no boolean type. Even with C99's `_Bool`/`stdbool.h`, it's an afterthought. In C++, `bool` is a **first-class type**.

```cpp
bool isReady = true;
bool isValid = (x > 0) && (x < 100);

// Functions that return bool
bool isPrime(int n);
```

---

## 5. `new` / `delete` vs `malloc` / `free`

C uses `malloc`/`free` which return `void*` and know nothing about types. C++ uses `new`/`delete` which are **type-aware** and call constructors/destructors.

```cpp
// C style (still works in C++, but not idiomatic)
int* p = (int*)malloc(sizeof(int));
*p = 42;
free(p);

// C++ style
int* p = new int(42);       // Allocates and initializes
delete p;

// Arrays
int* arr = new int[100];
delete[] arr;                // Must use delete[] for arrays
```

| Feature | `malloc`/`free` | `new`/`delete` |
|---------|-----------------|----------------|
| Returns | `void*` (needs cast) | Correct type |
| Constructors | Not called | Called |
| Destructors | Not called | Called |
| On failure | Returns `NULL` | Throws `std::bad_alloc` |
| Size | Manual `sizeof` | Automatic |

> In modern C++, prefer **smart pointers** (`unique_ptr`, `shared_ptr`) over raw `new`/`delete`. We cover these in Module 10.

---

## 6. Type Casting — Explicit and Safe

C uses a single cast syntax: `(type)expression`. C++ provides **four explicit cast operators** with clear intent.

```cpp
double pi = 3.14;

// C-style cast (works but discouraged in C++)
int x = (int)pi;

// C++ style casts
int a = static_cast<int>(pi);                     // Compile-time checked numeric/related conversion
const int* cp = &a;
int* mp = const_cast<int*>(cp);                    // Remove const (use with care)
// dynamic_cast<Derived*>(basePtr)                 // Runtime-checked downcast (needs virtual)
// reinterpret_cast<char*>(&x)                     // Raw bit reinterpretation (dangerous)
```

| Cast | Purpose | Checked? |
|------|---------|----------|
| `static_cast` | Numeric conversions, upcasts | Compile-time |
| `dynamic_cast` | Downcast in class hierarchy | Runtime |
| `const_cast` | Add/remove `const` | Compile-time |
| `reinterpret_cast` | Raw bit reinterpretation | None |

---

## 7. `auto` and Type Inference (C++11)

C requires you to spell out every type. C++ can **deduce types** for you.

```cpp
auto x = 42;              // int
auto pi = 3.14;           // double
auto name = std::string("Alice");  // std::string
auto it = myMap.begin();  // std::map<std::string, int>::iterator  (much shorter!)

// With const
const auto& ref = someExpensiveObject;  // const reference, type deduced
```

> `auto` doesn't mean dynamically typed. The type is fixed at compile time — it's just the compiler writing it for you.

---

## 8. Range-Based `for` Loop (C++11)

C loops over arrays with indices. C++ adds a **range-based for** that works with any iterable.

```cpp
int arr[] = {1, 2, 3, 4, 5};

// C style
for (int i = 0; i < 5; i++) {
    printf("%d ", arr[i]);
}

// C++ range-based for
for (int val : arr) {
    std::cout << val << " ";
}

// With reference (to modify in-place)
for (int& val : arr) {
    val *= 2;
}

// With auto
for (const auto& val : arr) {
    std::cout << val << " ";
}
```

---

## 9. Default and Keyword Arguments

### Default Parameters
C has no default arguments. C++ lets you provide defaults.

```cpp
void connect(const std::string& host, int port = 8080, bool useTls = false);

connect("localhost");               // port=8080, useTls=false
connect("localhost", 443);          // useTls=false
connect("localhost", 443, true);    // All specified
```

### `nullptr` (C++11)
C uses `NULL` (which is `0` or `(void*)0`). C++ introduces `nullptr`, a proper null pointer constant with its own type.

```cpp
int* p = nullptr;       // Preferred in C++
// int* p = NULL;       // Works but ambiguous (is it int 0 or pointer?)
// int* p = 0;          // Legal but confusing
```

---

## 10. Structured Bindings (C++17)

C++ can unpack structs, pairs, and tuples directly into named variables.

```cpp
#include <tuple>
#include <map>

std::pair<int, std::string> getUser() {
    return {1, "Alice"};
}

auto [id, name] = getUser();  // Destructure the pair

// With maps
std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << std::endl;
}
```

---

## 11. `constexpr` — Compile-Time Computation (C++11)

C uses `#define` or `const` for constants. C++ adds `constexpr` for **guaranteed compile-time evaluation**.

```cpp
constexpr int square(int x) { return x * x; }
constexpr int val = square(5);  // Computed at compile time — no runtime cost

// Can be used where C would require a macro
constexpr int SIZE = 256;
int buffer[SIZE];  // OK — SIZE is a compile-time constant
```

---

## 12. Enum Classes (C++11)

C enums leak their values into the enclosing scope and implicitly convert to `int`. C++ adds **scoped enums**.

```cpp
// C-style enum (still valid in C++)
enum Color { RED, GREEN, BLUE };   // RED, GREEN, BLUE are in global scope
int x = RED;                       // Implicit conversion to int

// C++ scoped enum
enum class Direction { NORTH, SOUTH, EAST, WEST };
Direction d = Direction::NORTH;
// int x = d;                      // ERROR: no implicit conversion
int x = static_cast<int>(d);      // Must be explicit
```

---

## 13. Initializer Lists and Uniform Initialization (C++11)

C++ provides **brace initialization** `{}` that works consistently everywhere.

```cpp
int x{42};                                 // Direct initialization
int arr[]{1, 2, 3, 4, 5};                  // Array
std::vector<int> v{1, 2, 3, 4, 5};        // Container (via std::initializer_list)
std::map<std::string, int> m{{"a", 1}, {"b", 2}};

// Prevents narrowing conversions
// int x{3.14};  // ERROR: narrowing double → int
int y = 3.14;    // OK in C, silently truncates
```

---

## 14. Inline Variables and `constexpr` Variables (C++17)

C++ allows variables to be declared `inline` in headers (just like inline functions), avoiding ODR violations:

```cpp
// In a header file
inline constexpr int MAX_RETRIES = 3;   // One definition, usable everywhere
```

---

## Summary: C++ Syntax Quick Reference

| Feature | C Way | C++ Way |
|---------|-------|---------|
| Names scope | Prefixes (`SDL_Init`) | Namespaces (`SDL::Init`) |
| I/O | `printf` / `scanf` | `std::cout` / `std::cin` |
| Strings | `char[]`, `strlen`, `strcmp` | `std::string` |
| Booleans | `int` or `_Bool` | `bool` |
| Heap alloc | `malloc` / `free` | `new` / `delete` (or smart ptrs) |
| Type cast | `(int)x` | `static_cast<int>(x)` |
| Type inference | — | `auto` |
| Iteration | `for (i=0; ...)` | `for (auto& x : collection)` |
| Null pointer | `NULL` | `nullptr` |
| Constants | `#define` / `const` | `constexpr` |
| Enumerations | `enum { ... }` | `enum class { ... }` |
| Default args | — | `void f(int x = 0)` |

---

## Next Module
[01_references](../01_references/README.md) — Aliases that replace many pointer use-cases.
