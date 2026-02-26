# Module 07: Polymorphism

## What C++ Adds: Runtime Polymorphism with Virtual Functions

**C has**: Function pointers in structs (manual vtables)
**C++ adds**: Virtual functions with automatic runtime dispatch

## Key Concept

Different behavior based on actual object type at runtime:

```cpp
class Animal {
public:
    virtual void makeSound() {  // virtual keyword!
        std::cout << "Some generic sound\n";
    }
};

class Dog : public Animal {
public:
    void makeSound() override {  // override keyword (C++11)
        std::cout << "Woof!\n";
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        std::cout << "Meow!\n";
    }
};

Animal* animals[] = {new Dog(), new Cat()};
for (auto* animal : animals) {
    animal->makeSound();  // Calls correct version at runtime!
}
// Output: Woof! Meow!
```

## Virtual Functions

```cpp
class Base {
public:
    virtual void virtualFunc() {
        std::cout << "Base::virtualFunc\n";
    }
    
    void normalFunc() {
        std::cout << "Base::normalFunc\n";
    }
};

class Derived : public Base {
public:
    void virtualFunc() override {  // Overrides base version
        std::cout << "Derived::virtualFunc\n";
    }
    
    void normalFunc() {  // Hides base version (NOT override!)
        std::cout << "Derived::normalFunc\n";
    }
};

Derived d;
Base* ptr = &d;

ptr->virtualFunc();  // Derived::virtualFunc (runtime polymorphism)
ptr->normalFunc();   // Base::normalFunc (static binding)
```

## How It Works: VTable

Compiler creates a **virtual table** (vtable) for each class with virtual functions:

```cpp
class Base {
public:
    virtual void func1();
    virtual void func2();
};

// Compiler generates (conceptually):
// Base_VTable:
// [0] -> pointer to Base::func1
// [1] -> pointer to Base::func2

// Each Base object has hidden vptr pointing to Base_VTable
```

**Cost**: One pointer per object + one vtable per class

## Pure Virtual Functions (Abstract Classes)

```cpp
class Shape {  // Abstract class
public:
    virtual double area() const = 0;  // Pure virtual function
    virtual double perimeter() const = 0;
    
    virtual ~Shape() {}  // Virtual destructor!
};

// Cannot instantiate:
// Shape s;  // ERROR: cannot create object of abstract class

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    
    // Must implement pure virtual functions
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
};

// Now can instantiate:
Circle c(5.0);
Shape* s = &c;  // Polymorphic use
```

## Virtual Destructors

**Critical**: Always make destructor virtual in base classes:

```cpp
class Base {
public:
    Base() { data = new int[100]; }
    ~Base() { delete[] data; }  // NOT virtual - BAD!
private:
    int* data;
};

class Derived : public Base {
public:
    Derived() { moreData = new int[100]; }
    ~Derived() { delete[] moreData; }
private:
    int* moreData;
};

Base* ptr = new Derived();
delete ptr;  // Only calls ~Base()! Memory leak!

// FIX: Make base destructor virtual
class Base {
public:
    virtual ~Base() { delete[] data; }  // GOOD!
private:
    int* data;
};

// Now delete ptr calls ~Derived() then ~Base()
```

**Rule**: If a class has any virtual functions, its destructor should be virtual.

## override and final (C++11)

```cpp
class Base {
public:
    virtual void func() {}
    virtual void process(int x) {}
};

class Derived : public Base {
public:
    void func() override {}  // OK: overrides Base::func
    
    // void process(double x) override {}  // ERROR: doesn't match base
    // override keyword catches typos!
    
    void newFunc() final {}  // Cannot override in further derived classes
};

class MoreDerived : public Derived {
    // void newFunc() override {}  // ERROR: func is final
};

class FinalClass final : public Base {  // Cannot inherit from this
};

// class Illegal : public FinalClass {};  // ERROR
```

## Polymorphic Use Cases

### Interface (Abstract Base Class)
```cpp
class ILogger {  // Interface (I prefix convention)
public:
    virtual void log(const std::string& msg) = 0;
    virtual ~ILogger() {}
};

class FileLogger : public ILogger {
public:
    void log(const std::string& msg) override {
        // Write to file
    }
};

class ConsoleLogger : public ILogger {
public:
    void log(const std::string& msg) override {
        std::cout << msg << std::endl;
    }
};

void doSomething(ILogger& logger) {  // Polymorphic parameter
    logger.log("Event occurred");
}
```

### Factory Pattern
```cpp
class Animal {
public:
    virtual void makeSound() = 0;
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void makeSound() override { std::cout << "Woof!\n"; }
};

class Cat : public Animal {
public:
    void makeSound() override { std::cout << "Meow!\n"; }
};

Animal* createAnimal(const std::string& type) {  // Factory
    if (type == "dog") return new Dog();
    if (type == "cat") return new Cat();
    return nullptr;
}
```

## Dynamic Cast

```cpp
class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void derivedFunc() {}
};

Base* base = new Derived();

// Dynamic cast (runtime type checking)
Derived* derived = dynamic_cast<Derived*>(base);
if (derived) {
    derived->derivedFunc();  // Safe!
} else {
    // base didn't actually point to Derived
}
```

**Requires**: RTTI (RunTime Type Information) enabled and at least one virtual function

## Comparison with C

| Feature | C | C++ Polymorphism |
|---------|---|------------------|
| **Runtime dispatch** | Manual function pointers | Automatic with virtual |
| **Vtable** | Manual implementation | Compiler-generated |
| **Type safety** | None (void* casting) | Compile-time checks |
| **Overhead** | Manual management | One vptr per object |
| **Abstract types** | Convention only | Enforced (pure virtual) |

### C Example (Manual Polymorphism)
```c
struct Animal {
    void (*makeSound)(struct Animal*);  // Function pointer
};

void dog_bark(struct Animal* self) {
    printf("Woof!\n");
}

struct Animal dog;
dog.makeSound = dog_bark;
dog.makeSound(&dog);  // Manual dispatch
```

## Performance

- **Virtual function call**: ~1 pointer dereference overhead
- **Normal function call**: Direct jump
- **Inline**: No call overhead

**When it matters**: Tight loops with millions of calls
**Usually**: Negligible impact, worth it for clean design

## Best Practices

1. **Virtual destructor**: Always in base classes
2. **Use override**: Catches mistakes
3. **Use final**: When you don't want further overriding
4. **Interfaces**: Pure virtual functions for abstract contracts
5. **Don't overthink**: Virtual is cheap, use when needed

## Next Module

**08_templates**: Compile-time polymorphism (vs runtime polymorphism shown here).
