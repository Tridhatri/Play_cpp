# C++ Exclusive Features - Learning Path

## Overview
This comprehensive guide focuses on **C++ features that don't exist in C**. Since you already know C, this curriculum skips basic syntax and focuses on what makes C++ unique and powerful.

## Prerequisites
- Strong understanding of C (pointers, structs, functions, memory management)
- Familiarity with compilation and linking
- Basic understanding of data structures

## Learning Path Structure

Each module contains:
- **README.md**: Detailed concept explanation with key differences from C
- **example.cpp**: Working code demonstrating the concept
- **exercise.cpp**: Hands-on coding challenges with TODO markers
- **solution.cpp**: Complete solutions to exercises

## Modules

### 00. C++ Syntax Basics
**C++ Exclusive**: Core syntax features C doesn't have
- Namespaces and `using`
- `iostream` (type-safe I/O)
- `std::string` vs C strings
- `bool`, `nullptr`, `new`/`delete`
- C++ casts (`static_cast`, etc.)
- `auto`, range-based `for`, default parameters
- `constexpr`, `enum class`, uniform initialization
- Structured bindings (C++17)
- **Why it matters**: Foundation for all C++ code you read and write

### 01. References
**C++ Exclusive**: References don't exist in C
- What are references vs pointers
- L-value references
- Pass-by-reference
- Reference vs pointer usage patterns
- **Why it matters**: Safer alternative to pointers, enables operator overloading

### 02. Function Overloading
**C++ Exclusive**: C requires unique function names
- Multiple functions with same name, different parameters
- Name mangling
- Overload resolution rules
- **Why it matters**: More intuitive APIs, type-safe generic operations

### 03. Classes - Basics
**C++ Exclusive**: Classes with member functions (C only has structs with data)
- Classes vs structs
- Member functions vs free functions
- `this` pointer
- Access specifiers (public, private, protected)
- **Why it matters**: Encapsulation and data hiding

### 04. Constructors & Destructors
**C++ Exclusive**: Automatic initialization and cleanup
- Constructor types (default, parameterized, copy)
- Destructor for cleanup
- Member initializer lists
- Rule of Three/Five/Zero
- **Why it matters**: RAII pattern, automatic resource management

### 05. Operator Overloading
**C++ Exclusive**: Custom behavior for operators
- Overloading arithmetic, comparison, stream operators
- Member vs non-member operators
- Return value optimization
- **Why it matters**: Natural syntax for custom types

### 06. Inheritance
**C++ Exclusive**: True inheritance with access control
- Base and derived classes
- Protected access
- Constructor/destructor calling order
- Is-a relationship
- **Why it matters**: Code reuse and polymorphism foundation

### 07. Polymorphism
**C++ Exclusive**: Runtime polymorphism with virtual functions
- Virtual functions and vtables
- Pure virtual functions (abstract classes)
- Virtual destructors
- Override and final keywords
- **Why it matters**: Runtime behavior selection, plugin architectures

### 08. Templates
**C++ Exclusive**: Compile-time generic programming
- Function templates
- Class templates
- Template specialization
- Template type deduction
- **Why it matters**: Type-safe generics, zero-cost abstraction

### 09. STL Containers
**C++ Exclusive**: Standard Template Library
- vector, list, map, set, unordered_map
- Iterators
- Container adaptors (stack, queue)
- **Why it matters**: Production-ready data structures

### 10. Smart Pointers
**C++ Exclusive**: Automatic memory management
- unique_ptr (exclusive ownership)
- shared_ptr (reference counting)
- weak_ptr (breaking cycles)
- **Why it matters**: Eliminates manual memory management bugs

### 11. Exception Handling
**C++ Exclusive**: try-catch-throw mechanism
- Throwing and catching exceptions
- Exception safety guarantees
- RAII and exceptions
- noexcept specifier
- **Why it matters**: Robust error handling without error codes

### 12. Lambda Expressions
**C++ Exclusive**: Anonymous functions with captures
- Lambda syntax
- Capture modes (by value, by reference)
- Mutable lambdas
- Generic lambdas
- **Why it matters**: Inline callbacks, STL algorithms

### 13. Move Semantics
**C++ Exclusive**: Efficient resource transfer
- L-values vs R-values
- Move constructors and move assignment
- std::move and std::forward
- Perfect forwarding
- **Why it matters**: Performance optimization, enables unique_ptr

## Compilation Instructions

### Basic Compilation
```bash
g++ -std=c++17 -Wall -Wextra -o program file.cpp
```

### With Debugging
```bash
g++ -std=c++17 -g -Wall -Wextra -o program file.cpp
```

### Optimization
```bash
g++ -std=c++17 -O2 -Wall -Wextra -o program file.cpp
```

## Recommended Learning Order

1. **Start Here**: 00 → 01 → 02 → 03 → 04 (Fundamentals)
2. **Essential OOP**: 05 → 06 → 07 (Object-Oriented)
3. **Generic Programming**: 08 → 09 (Templates & STL)
4. **Modern C++**: 10 → 11 → 12 → 13 (Advanced)

## Key Differences from C - Quick Reference

| Feature | C | C++ |
|---------|---|-----|
| **Encapsulation** | Structs with data only | Classes with private members |
| **Polymorphism** | Function pointers | Virtual functions |
| **Memory Management** | malloc/free | new/delete + smart pointers |
| **Error Handling** | Return codes | Exceptions |
| **Generic Code** | Macros, void* | Templates |
| **Function Names** | Must be unique | Can be overloaded |
| **Initialization** | Manual | Constructors |
| **Cleanup** | Manual | Destructors (RAII) |
| **Parameter Passing** | Value or pointer | Value, pointer, or reference |
| **Type Safety** | Weak (implicit casts) | Strong (explicit casts) |
| **STL** | None (roll your own) | Rich standard library |

## Study Tips

1. **Code Every Example**: Don't just read - type and compile each example
2. **Break Things**: Modify examples to see what fails and why
3. **Use Compiler Warnings**: `-Wall -Wextra` will teach you best practices
4. **Read Compiler Errors**: C++ errors are verbose but informative
5. **Compare to C**: For each feature, think "how would I do this in C?"

## Resources

- **Primary**: learncpp.com (comprehensive online tutorial)
- **Reference**: cppreference.com (detailed technical reference)
- **Books**: "A Tour of C++" by Bjarne Stroustrup
- **Practice**: HackerRank, LeetCode (C++ section)

## Testing Your Knowledge

After completing each module:
1. Complete all exercises without looking at solutions
2. Compile with `-Wall -Wextra` and fix all warnings
3. Use valgrind (Linux) or AddressSanitizer to check for memory leaks
4. Explain the concept to yourself in terms of C equivalents

## Next Steps After Completion

- Modern C++ features (C++20: concepts, ranges, coroutines)
- Design patterns in C++
- Performance optimization and profiling
- Build systems (CMake, Make)
- Testing frameworks (Google Test, Catch2)

---

**Remember**: C++ is not "C with classes" - it's a different paradigm. Embrace the features that make C++ unique rather than writing C code in C++ syntax!
