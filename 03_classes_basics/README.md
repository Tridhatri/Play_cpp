# Module 03: Classes - Basics

## What C++ Adds: True Classes

**C has**: Structs with data only
**C++ adds**: Classes with data + functions + access control

## Key Concept

In C, structs only hold data. Functions that operate on structs are separate:

```c
// C approach
struct Rectangle {
    int width;
    int height;
};

int area(struct Rectangle* r) {  // Separate function
    return r->width * r->height;
}
```

C++ integrates functions into the class:

```cpp
// C++ approach
class Rectangle {
private:
    int width;
    int height;
    
public:
    int area() {  // Member function
        return width * height;
    }
};
```

## Class vs Struct in C++

**Key difference**: Default access level
- `class`: members are **private** by default
- `struct`: members are **public** by default

```cpp
class MyClass {
    int x;  // private by default
};

struct MyStruct {
    int x;  // public by default
};
```

Otherwise, they're identical! Structs can have methods, constructors, etc.

## Access Specifiers

```cpp
class Example {
private:     // Only accessible within this class
    int secretData;
    
protected:   // Accessible in this class and derived classes
    int protectedData;
    
public:      // Accessible from anywhere
    int publicData;
    
    void publicMethod() {
        secretData = 10;      // OK: same class
        protectedData = 20;   // OK: same class
    }
};

int main() {
    Example e;
    e.publicData = 5;     // OK: public
    // e.secretData = 10;    // ERROR: private
    // e.protectedData = 20; // ERROR: protected
}
```

## The `this` Pointer

Inside member functions, `this` is a pointer to the current object:

```cpp
class Counter {
private:
    int count;
    
public:
    void setCount(int count) {
        this->count = count;  // Disambiguate parameter from member
    }
    
    Counter& getThis() {
        return *this;  // Return reference to current object
    }
};
```

## Member Functions vs Free Functions

### Member Function (Inside Class)
```cpp
class Point {
public:
    int x, y;
    
    double distanceFromOrigin() {  // Has access to x, y directly
        return sqrt(x*x + y*y);
    }
};

Point p{3, 4};
p.distanceFromOrigin();  // Called with dot operator
```

### Free Function (Outside Class)
```cpp
double distance(const Point& p) {  // Need to access through parameter
    return sqrt(p.x*p.x + p.y*p.y);
}

distance(p);  // Called like regular function
```

## Encapsulation

Hide implementation details, expose only interface:

```cpp
class BankAccount {
private:
    double balance;  // Hidden from outside
    std::string accountNumber;
    
public:
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    double getBalance() const {  // const = doesn't modify object
        return balance;
    }
};
```

Benefits:
- Can't accidentally break invariants (balance can't go negative)
- Can change internal implementation without breaking external code
- Clear interface (public methods show what the class does)

## Const Member Functions

```cpp
class Point {
private:
    int x, y;
    
public:
    int getX() const {  // Promise not to modify object
        return x;
    }
    
    void setX(int newX) {  // Non-const: modifies object
        x = newX;
    }
};

const Point p{10, 20};
int x = p.getX();  // OK: const method
// p.setX(30);       // ERROR: can't call non-const on const object
```

## Static Members

### Static Data Members (Shared Across All Instances)
```cpp
class Counter {
private:
    static int count;  // Shared by all Counter objects
    int id;
    
public:
    Counter() {
        id = count++;
    }
    
    static int getCount() {  // Static method
        return count;
    }
};

// Must define static member outside class
int Counter::count = 0;
```

### Static Member Functions
- No `this` pointer
- Can only access static members
- Called with class name or object

```cpp
int total = Counter::getCount();  // Called with class name
```

## Comparison with C

| Feature | C | C++ Classes |
|---------|---|-------------|
| **Data** | struct members | Private, protected, public members |
| **Functions** | Separate | Member functions |
| **Access Control** | None (all public) | private, protected, public |
| **this pointer** | Manual (pass struct*) | Automatic |
| **Encapsulation** | Convention only | Enforced by compiler |
| **Methods** | Free functions | Member functions with direct access |

## Why It Matters

1. **Encapsulation**: Hide implementation, prevent invalid states
2. **Organization**: Related data and functions together
3. **Maintainability**: Clear interfaces, internal changes don't break external code
4. **Type Safety**: Compiler enforces access control

## Common Patterns

### Getter/Setter
```cpp
class Person {
private:
    std::string name;
    int age;
    
public:
    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }
    
    int getAge() const { return age; }
    void setAge(int a) {
        if (a >= 0 && a < 150) {  // Validation!
            age = a;
        }
    }
};
```

### Builder Pattern (Method Chaining)
```cpp
class Query {
private:
    std::string table, where, order;
    
public:
    Query& from(const std::string& t) {
        table = t;
        return *this;
    }
    
    Query& whereClause(const std::string& w) {
        where = w;
        return *this;
    }
};

Query q;
q.from("users").whereClause("age > 18");
```

## Next Steps

**Module 04**: Constructors and destructors enable automatic initialization and cleanup (RAII).
