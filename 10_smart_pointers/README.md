# Module 10: Smart Pointers

## What C++ Adds: Automatic Memory Management

**C has**: Manual new/delete, malloc/free
**C++ adds**: Smart pointers that automatically manage memory

## Key Concept

Never use raw `new`/`delete` - use smart pointers instead:

```cpp
// BAD (C-style):
int* ptr = new int(42);
// ... use ptr ...
delete ptr;  // Easy to forget! Memory leak if exception thrown!

// GOOD (C++11):
std::unique_ptr<int> ptr = std::make_unique<int>(42);
// ... use ptr ...
// Automatically deleted when ptr goes out of scope!
```

## RAII (Resource Acquisition Is Initialization)

Smart pointers use RAII:
- Constructor acquires resource (allocates memory)
- Destructor releases resource (deallocates memory)
- Automatic, exception-safe!

## unique_ptr - Exclusive Ownership

**One owner**: Cannot be copied, only moved

```cpp
#include <memory>

// Creation
std::unique_ptr<int> ptr1 = std::make_unique<int>(42);  // Preferred
std::unique_ptr<int> ptr2(new int(42));                 // Also works

// Access
*ptr1 = 100;
int value = *ptr1;
int* raw = ptr1.get();  // Get raw pointer (don't delete it!)

// Cannot copy
// std::unique_ptr<int> ptr3 = ptr1;  // ERROR: deleted copy constructor

// Can move
std::unique_ptr<int> ptr3 = std::move(ptr1);  // ptr1 is now nullptr
```

### With Classes
```cpp
class Person {
public:
    std::string name;
    Person(const std::string& n) : name(n) {
        std::cout << "Person " << name << " created\n";
    }
    ~Person() {
        std::cout << "Person " << name << " destroyed\n";
    }
};

{
    auto person = std::make_unique<Person>("Alice");
    person->name = "Bob";  // Use -> like regular pointer
}  // Automatically deleted here!
```

### Arrays
```cpp
std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);
arr[0] = 42;  // Array access
arr[1] = 100;
```

### Custom Deleters
```cpp
void customDelete(int* ptr) {
    std::cout << "Custom delete\n";
    delete ptr;
}

std::unique_ptr<int, decltype(&customDelete)> ptr(new int(42), customDelete);
```

**When to use**:
- Single ownership
- Dynamic objects with clear lifetime
- Replacing raw `new`/`delete`
- Factory functions (return unique_ptr)

## shared_ptr - Shared Ownership

**Reference counting**: Multiple owners, deleted when last owner destroyed

```cpp
#include <memory>

std::shared_ptr<int> ptr1 = std::make_shared<int>(42);  // Refcount = 1
{
    std::shared_ptr<int> ptr2 = ptr1;  // Refcount = 2 (shared!)
    std::cout << *ptr2 << std::endl;   // Both point to same object
}  // ptr2 destroyed, refcount = 1
// Object still alive (ptr1 still exists)

// ptr1 destroyed, refcount = 0, object deleted
```

### Reference Count
```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
std::cout << "Use count: " << ptr1.use_count() << std::endl;  // 1

std::shared_ptr<int> ptr2 = ptr1;
std::cout << "Use count: " << ptr1.use_count() << std::endl;  // 2

ptr2.reset();  // Release ptr2's ownership
std::cout << "Use count: " << ptr1.use_count() << std::endl;  // 1
```

### Copying vs Moving
```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(42);

auto ptr2 = ptr1;              // Copy: refcount increases
auto ptr3 = std::move(ptr1);   // Move: refcount unchanged, ptr1 becomes nullptr
```

**When to use**:
- Multiple owners with unclear lifetimes
- Shared resources (caches, pools)
- Circular data structures (with weak_ptr)

## weak_ptr - Non-Owning Reference

**Breaks cycles**: Points to shared_ptr-managed object without ownership

```cpp
std::shared_ptr<int> shared = std::make_shared<int>(42);
std::weak_ptr<int> weak = shared;  // Doesn't increase refcount

// To use weak_ptr, must convert to shared_ptr
if (auto temp = weak.lock()) {  // Returns shared_ptr if object alive
    std::cout << *temp << std::endl;
} else {
    std::cout << "Object deleted\n";
}

shared.reset();  // Delete object
if (weak.expired()) {  // Check if object still exists
    std::cout << "Weak pointer expired\n";
}
```

### Breaking Circular References
```cpp
class Node {
public:
    std::shared_ptr<Node> next;  // Strong reference
    std::weak_ptr<Node> prev;    // Weak reference (breaks cycle!)
    
    ~Node() {
        std::cout << "Node destroyed\n";
    }
};

auto node1 = std::make_shared<Node>();
auto node2 = std::make_shared<Node>();

node1->next = node2;  // node1 owns node2
node2->prev = node1;  // node2 doesn't own node1 (weak!)

// When node1 and node2 go out of scope, both are deleted
// Without weak_ptr, would have memory leak!
```

**When to use**:
- Parent-child relationships (child has weak_ptr to parent)
- Observers/callbacks (observer has weak_ptr to subject)
- Cache entries
- Breaking circular references

## Comparison Table

| Feature | unique_ptr | shared_ptr | weak_ptr |
|---------|------------|------------|----------|
| **Ownership** | Exclusive | Shared | None |
| **Copyable** | No | Yes | Yes |
| **Movable** | Yes | Yes | Yes |
| **Overhead** | None | Refcount + control block | Minimal |
| **Thread-safe** | N/A | Refcount is atomic | Yes |
| **Use case** | Single owner | Multiple owners | Non-owning reference |

## make_unique vs make_shared

**Always prefer make_unique/make_shared**:

```cpp
// GOOD:
auto ptr = std::make_unique<Widget>();
auto sptr = std::make_shared<Widget>();

// BAD:
std::unique_ptr<Widget> ptr(new Widget());
std::shared_ptr<Widget> sptr(new Widget());
```

**Why?**
1. Exception safety
2. Less typing
3. Efficiency (make_shared does single allocation)

## Casting Smart Pointers

```cpp
class Base {
    virtual ~Base() = default;
};

class Derived : public Base {};

std::shared_ptr<Derived> derived = std::make_shared<Derived>();

// Upcast (implicit)
std::shared_ptr<Base> base = derived;  // OK

// Downcast (use dynamic_pointer_cast)
std::shared_ptr<Base> base2 = std::make_shared<Derived>();
std::shared_ptr<Derived> derived2 = std::dynamic_pointer_cast<Derived>(base2);
if (derived2) {
    // Successful cast
}

// Also available:
// std::static_pointer_cast<T>
// std::const_pointer_cast<T>
// std::reinterpret_pointer_cast<T>
```

## Common Pitfalls

### 1. Don't Mix Raw and Smart Pointers
```cpp
// BAD:
Widget* raw = new Widget();
std::unique_ptr<Widget> smart(raw);
delete raw;  // CRASH: double delete!

// GOOD:
auto smart = std::make_unique<Widget>();
Widget* raw = smart.get();  // OK: just looking, not owning
```

### 2. Don't Create shared_ptr from Raw Pointer Twice
```cpp
// BAD:
Widget* raw = new Widget();
std::shared_ptr<Widget> ptr1(raw);
std::shared_ptr<Widget> ptr2(raw);  // BUG: two separate refcounts!
// When ptr1 or ptr2 is destroyed -> double delete!

// GOOD:
auto ptr1 = std::make_shared<Widget>();
auto ptr2 = ptr1;  // Share ownership
```

### 3. Circular References with shared_ptr
```cpp
// BAD: Memory leak!
struct Node {
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;  // Circular reference!
};

// GOOD: Use weak_ptr
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // Breaks cycle
};
```

### 4. Returning unique_ptr from Function
```cpp
// This works! (move semantics)
std::unique_ptr<Widget> createWidget() {
    return std::make_unique<Widget>();
}

auto widget = createWidget();  // Efficient move
```

## Comparison with C

| Feature | C | C++ Smart Pointers |
|---------|---|-------------------|
| **Allocation** | malloc/new | make_unique/make_shared |
| **Deallocation** | free/delete (manual) | Automatic (RAII) |
| **Memory leaks** | Common | Rare (if you use smart pointers) |
| **Exception safety** | Hard to achieve | Automatic |
| **Ownership** | Unclear | Explicit (unique vs shared) |
| **Dangling pointers** | Common | Prevented by design |

## When to Use What

1. **Default**: `unique_ptr` (lowest overhead, clearest ownership)
2. **Multiple owners needed**: `shared_ptr`
3. **Non-owning reference to shared_ptr**: `weak_ptr`
4. **Factory functions**: Return `unique_ptr`
5. **Never**: Raw `new`/`delete` (except in very low-level code)

## Best Practices

1. **Prefer unique_ptr** as default
2. **Use make_unique/make_shared** always
3. **Don't mix raw and smart pointers** for ownership
4. **Use weak_ptr** to break circular references
5. **Pass smart pointers by const reference** if not transferring ownership
6. **Pass raw pointers** if function doesn't affect ownership

## Next Module

**11_exceptions**: Error handling with exception safety guarantees (enabled by RAII).
