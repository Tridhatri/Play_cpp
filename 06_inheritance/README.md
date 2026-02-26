# Module 06: Inheritance

## What C++ Adds: True Inheritance with Access Control

**C has**: Struct composition (embedding structs)
**C++ adds**: Inheritance with access specifiers and proper OOP

## Key Concept

Create new classes based on existing ones:

```cpp
class Animal {  // Base class
protected:
    std::string name;
public:
    Animal(const std::string& n) : name(n) {}
    void eat() { std::cout << name << " is eating\n"; }
};

class Dog : public Animal {  // Derived class
public:
    Dog(const std::string& n) : Animal(n) {}
    void bark() { std::cout << name << " says woof!\n"; }
};

Dog d("Buddy");
d.eat();   // Inherited from Animal
d.bark();  // Defined in Dog
```

## Inheritance Syntax

```cpp
class Derived : access_specifier Base {
    // Derived class members
};
```

Access specifiers: `public`, `protected`, `private`

## Access Control

```cpp
class Base {
private:
    int privateData;     // Only accessible in Base
protected:
    int protectedData;   // Accessible in Base and Derived
public:
    int publicData;      // Accessible everywhere
};

class Derived : public Base {
    void function() {
        // privateData = 1;    // ERROR: can't access private
        protectedData = 2;     // OK: can access protected
        publicData = 3;        // OK: can access public
    }
};
```

## Types of Inheritance

### Public Inheritance (Most Common)
```cpp
class Derived : public Base {
    // public stays public
    // protected stays protected
};
```

**Use**: "is-a" relationship (Dog IS-A Animal)

### Protected Inheritance
```cpp
class Derived : protected Base {
    // public becomes protected
    // protected stays protected
};
```

**Use**: Rare, implementation inheritance

### Private Inheritance
```cpp
class Derived : private Base {
    // public becomes private
    // protected becomes private
};
```

**Use**: "implemented-in-terms-of" (prefer composition)

## Constructor/Destructor Order

```cpp
class Base {
public:
    Base() { std::cout << "Base constructor\n"; }
    ~Base() { std::cout << "Base destructor\n"; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "Derived constructor\n"; }
    ~Derived() { std::cout << "Derived destructor\n"; }
};

Derived d;
// Output:
// Base constructor
// Derived constructor
// ... (d lives) ...
// Derived destructor
// Base destructor
```

**Rule**: 
- Constructors: Base → Derived
- Destructors: Derived → Base (reverse order)

## Calling Base Constructors

```cpp
class Vehicle {
protected:
    std::string brand;
    int year;
public:
    Vehicle(const std::string& b, int y) : brand(b), year(y) {}
};

class Car : public Vehicle {
private:
    int doors;
public:
    // Must call base constructor in initializer list
    Car(const std::string& b, int y, int d) 
        : Vehicle(b, y), doors(d) {}
};
```

## Multiple Inheritance

C++ supports multiple inheritance (unlike Java/C#):

```cpp
class A {
public:
    void funcA() {}
};

class B {
public:
    void funcB() {}
};

class C : public A, public B {  // Inherits from both
public:
    void funcC() {}
};

C obj;
obj.funcA();  // From A
obj.funcB();  // From B
obj.funcC();  // From C
```

### Diamond Problem
```cpp
class Base {
public:
    int value;
};

class Left : public Base {};
class Right : public Base {};

class Bottom : public Left, public Right {
    void func() {
        // value = 10;  // ERROR: Ambiguous! Which Base::value?
        Left::value = 10;   // OK: explicit
        Right::value = 20;  // OK: different copy!
    }
};
```

**Solution**: Virtual inheritance (Module 07)

## Type Conversion

Can convert derived → base (upcasting):

```cpp
class Base {};
class Derived : public Base {};

Derived d;
Base* basePtr = &d;  // OK: upcast (implicit)
Base& baseRef = d;   // OK

// Base b = d;  // Slicing! Only Base part copied
```

**Object Slicing**: Copying derived to base loses derived data

```cpp
Derived d;
Base b = d;  // Slicing: only Base members copied
```

## Hiding Base Members

```cpp
class Base {
public:
    void print() { std::cout << "Base\n"; }
    void show(int x) {}
};

class Derived : public Base {
public:
    void print() { std::cout << "Derived\n"; }  // Hides Base::print
    // This hides ALL Base::show overloads!
    void show() {}
};

Derived d;
d.print();    // Calls Derived::print
// d.show(5);    // ERROR: Base::show(int) is hidden

// Solution 1: using declaration
class Derived2 : public Base {
public:
    using Base::show;  // Bring Base::show into scope
    void show() {}
};

// Solution 2: Call explicitly
void Derived::someFunc() {
    Base::print();  // Explicitly call base version
}
```

## When to Use Inheritance

**Good reasons**:
- IS-A relationship (Dog is an Animal)
- Substitutability (can use Derived wherever Base is expected)
- Polymorphism (covered in Module 07)

**Bad reasons**:
- Code reuse alone (use composition instead)
- Has-A relationship (Car HAS-A Engine → use composition)

## Composition vs Inheritance

```cpp
// BAD: Car IS-NOT-A Engine
class Car : public Engine {};

// GOOD: Car HAS-A Engine  
class Car {
private:
    Engine engine;  // Composition
public:
    void start() { engine.start(); }
};
```

**Guideline**: Prefer composition over inheritance

## Comparison with C

| Feature | C | C++ Inheritance |
|---------|---|-----------------|
| **Code reuse** | Copy code or function pointers | Inherit members and methods |
| **Access control** | None | private, protected, public |
| **Polymorphism** | Manual (vtables) | Built-in (virtual functions) |
| **Type relationship** | None | IS-A enforced by compiler |
| **Construction** | Manual | Automatic base construction |

## Next Module

**07_polymorphism**: Virtual functions enable runtime polymorphism with inheritance.
