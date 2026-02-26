# Module 01: References

## What C++ Adds: References

**C has**: Pointers
**C++ adds**: References (aliases to existing variables)

## Key Concept

A reference is an **alias** (another name) for an existing variable. Unlike pointers:
- Must be initialized when declared
- Cannot be null
- Cannot be reassigned to refer to another variable
- Automatically dereferenced (no `*` needed)

## Syntax Comparison

### In C (Pointers Only)
```c
void increment(int* ptr) {
    (*ptr)++;  // Must dereference
}

int x = 5;
increment(&x);  // Must take address
```

### In C++ (References)
```cpp
void increment(int& ref) {
    ref++;  // Automatic dereferencing
}

int x = 5;
increment(x);  // No address-of operator needed
```

## Reference vs Pointer

| Feature | Pointer | Reference |
|---------|---------|-----------|
| Can be null | Yes (`nullptr`) | No |
| Must be initialized | No | Yes |
| Can be reassigned | Yes | No |
| Syntax for access | `*ptr` | `ref` |
| Passing to function | `&variable` | `variable` |
| Memory address | Is a variable | Is an alias |

## L-value References

An **l-value** is something that has a memory address (can appear on left side of `=`).

```cpp
int x = 10;      // x is an l-value
int& ref = x;    // ref is an l-value reference to x
// int& ref2;    // ERROR: must initialize
// int& ref3 = 5;  // ERROR: can't bind to r-value (temporary)
```

## Why References Matter

1. **Cleaner syntax** than pointers for pass-by-reference
2. **Cannot be null**: Safer than pointers in many cases
3. **Required for operator overloading**: `operator<<` needs references
4. **Prevents copying**: Efficient for large objects
5. **Return values**: Can return modifiable l-values

## Common Use Cases

### 1. Avoiding Expensive Copies
```cpp
// C way: copies entire struct
struct LargeData {
    int data[1000];
};

void processCopy(struct LargeData data) {  // Copies 4000 bytes!
    // ...
}

// C++ way: no copy
void processRef(const LargeData& data) {  // Just 8 bytes (reference)
    // ... (const prevents modification)
}
```

### 2. Modifying Function Arguments
```cpp
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
```

### 3. Range-based For Loop (C++11)
```cpp
int arr[] = {1, 2, 3, 4, 5};
for (int& num : arr) {  // Reference allows modification
    num *= 2;
}
```

## Const References

```cpp
const int& ref = x;  // Can read x, cannot modify
ref = 20;            // ERROR: assignment to const
```

**Special property**: Const references can bind to temporaries (r-values)!

```cpp
const int& ref = 5;  // OK! Lifetime of temporary extended
int& ref2 = 5;       // ERROR: non-const reference to temporary
```

## Behind the Scenes

Compilers typically implement references as **constant pointers**:

```cpp
int& ref = x;
// Likely implemented as:
int* const ref = &x;
```

But this is implementation detail - treat them as aliases, not pointers!

## When to Use References vs Pointers

**Use references when**:
- Passing/returning function parameters
- The value should always exist (not null)
- You won't need to reassign it

**Use pointers when**:
- You need to represent "no value" (nullptr)
- You need to reassign to different objects
- Working with dynamic memory (new/delete)
- C-style APIs require them

## Common Pitfalls

### 1. Dangling References
```cpp
int& getRef() {
    int local = 42;
    return local;  // ERROR: returns reference to local variable!
}  // local is destroyed here
```

### 2. Cannot Create Reference to Reference
```cpp
int x = 5;
int& ref = x;
int& & ref2 = ref;  // ERROR: no references to references
```

### 3. Cannot Have Array of References
```cpp
int& refs[10];  // ERROR: cannot create array of references
```

## Exercises

See `exercise.cpp` for hands-on practice including:
1. Pass-by-reference for swapping
2. Const references for efficiency
3. Returning references
4. Comparing reference vs pointer behavior

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
./exercise
```

## Next Module

**02_function_overloading**: References enable clean function overloading syntax.
