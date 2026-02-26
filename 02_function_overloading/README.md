# Module 02: Function Overloading

## What C++ Adds: Function Overloading

**C has**: Each function must have a unique name
**C++ adds**: Multiple functions can share the same name with different parameters

## Key Concept

**Function overloading** allows you to define multiple functions with the same name but different parameter lists (different number or types of parameters). The compiler selects the correct function based on the arguments provided.

## Why C Doesn't Have This

In C, function names directly map to symbol names in the object file. Each symbol must be unique.

```c
// In C, you must do this:
void print_int(int x);
void print_float(float x);
void print_string(const char* str);
```

## C++ Solution: Name Mangling

C++ compilers use **name mangling** to encode parameter types into the symbol name:

```cpp
// In C++, you can do this:
void print(int x);          // Mangled to something like: _Z5printi
void print(float x);        // Mangled to something like: _Z5printf
void print(const char* str);// Mangled to something like: _Z5printPKc

// User just calls:
print(42);        // Calls print(int)
print(3.14f);     // Calls print(float)
print("hello");   // Calls print(const char*)
```

## Overloading Rules

### Valid Overloads (Different Signatures)

```cpp
void func(int x);
void func(double x);              // Different type
void func(int x, int y);          // Different number of parameters
void func(const std::string& s);  // Different type
```

### Invalid Overloads

```cpp
int func(int x);
void func(int x);        // ERROR: return type alone doesn't matter

void func(int x);
void func(int y);        // ERROR: parameter names don't matter

void func(int x);
void func(const int x);  // ERROR: top-level const ignored (by value)
```

### Const with Pointers/References (Valid)

```cpp
void func(int* ptr);        // OK
void func(const int* ptr);  // OK: different (const applies to what's pointed to)

void func(int& ref);        // OK
void func(const int& ref);  // OK: different (const affects binding rules)
```

## Overload Resolution

The compiler selects the best match through a multi-step process:

1. **Exact match**: Perfect type match
2. **Promotion**: Small integer types to int, float to double
3. **Standard conversion**: int to double, derived to base pointer, etc.
4. **User-defined conversion**: Through constructors/conversion operators

```cpp
void print(int x) { std::cout << "int: " << x << std::endl; }
void print(double x) { std::cout << "double: " << x << std::endl; }

print(5);       // Exact match: print(int)
print(5.0);     // Exact match: print(double)
print(5.0f);    // Promotion: float -> double, calls print(double)

short s = 10;
print(s);       // Promotion: short -> int, calls print(int)
```

## Common Use Cases

### 1. Different Types for Same Operation

```cpp
int max(int a, int b) { return (a > b) ? a : b; }
double max(double a, double b) { return (a > b) ? a : b; }
```

### 2. Optional Parameters via Overloading

```cpp
void log(const std::string& message);
void log(const std::string& message, int level);
void log(const std::string& message, int level, const std::string& file);
```

### 3. Different Representations

```cpp
class Point {
public:
    Point(int x, int y);              // Cartesian coordinates
    Point(double r, double theta);    // ERROR: same signature as above!
                                      // Need different approach (named constructors)
};

// Better approach:
class Point {
public:
    static Point fromCartesian(int x, int y);
    static Point fromPolar(double r, double theta);
};
```

## Ambiguity Examples

```cpp
void func(int x);
void func(double x);

func(5);       // OK: calls func(int)
func(5.0);     // OK: calls func(double)

// Ambiguous cases:
func('A');     // Ambiguous if char can promote to int or convert to double
               // Actually, char promotes to int, so func(int) is called

void bar(int x, double y);
void bar(double x, int y);

bar(1, 2);     // ERROR: Ambiguous! Both require one conversion
```

## Default Arguments vs Overloading

C++ also has default arguments, which can sometimes replace overloading:

```cpp
// Using overloading:
void print(const std::string& str);
void print(const std::string& str, bool newline);

// Using default arguments:
void print(const std::string& str, bool newline = true);
```

**Warning**: Don't combine overloading and default arguments carelessly:

```cpp
void func(int x);
void func(int x, int y = 10);  // Dangerous!

func(5);  // ERROR: Ambiguous - could call either version
```

## Overloading and References

Remember from Module 01 that references enable overloading based on const:

```cpp
void process(std::string& str) {
    std::cout << "Non-const: can modify" << std::endl;
    str += " modified";
}

void process(const std::string& str) {
    std::cout << "Const: read-only" << std::endl;
    // str += " modified";  // ERROR
}

std::string s1 = "hello";
const std::string s2 = "world";

process(s1);  // Calls non-const version
process(s2);  // Calls const version
```

## Benefits Over C

1. **Cleaner APIs**: Users remember one name, not many
2. **Type Safety**: Compiler checks argument types
3. **Extensibility**: Add new overloads without renaming existing ones
4. **Intuitive**: Same operation, same name

## Viewing Name Mangling (Optional)

On Linux/Mac:
```bash
g++ -c file.cpp
nm file.o | grep func
c++filt _Z4funcv  # Demangle symbol
```

On Windows (MSVC):
```bash
dumpbin /symbols file.obj
undname ?func@@YAXXZ  # Demangle symbol
```

## Common Pitfalls

### 1. Expecting Return Type to Matter

```cpp
int getValue();
double getValue();  // ERROR: Can't overload on return type alone
```

### 2. Forgetting Type Promotions

```cpp
void func(int x);
void func(long x);

short s = 10;
func(s);  // Which one? (Promotes to int)
```

### 3. Pointer vs Array

```cpp
void func(int* arr);
void func(int arr[]);     // Same as above! Not an overload
void func(int arr[10]);   // Still the same! Array size ignored
```

## Exercises

See `exercise.cpp` for:
1. Creating type-specific overloads
2. Understanding overload resolution
3. const overloading
4. Avoiding ambiguity
5. Combining with default arguments

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
./exercise
```

## Next Module

**03_classes_basics**: Function overloading is fundamental to class member functions and constructors.
