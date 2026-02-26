#include <iostream>
#include <string>
#include <cmath>

// Example 1: Basic class with public and private members
class Rectangle {
private:
    int width;
    int height;
    
public:
    void setDimensions(int w, int h) {
        width = w;
        height = h;
    }
    
    int area() const {
        return width * height;
    }
    
    int perimeter() const {
        return 2 * (width + height);
    }
};

// Example 2: Class vs Struct (default access)
class MyClass {
    int x;  // private by default
};

struct MyStruct {
    int x;  // public by default
};

// Example 3: this pointer usage
class Point {
private:
    int x, y;
    
public:
    void set(int x, int y) {
        this->x = x;  // this-> disambiguates
        this->y = y;
    }
    
    Point& move(int dx, int dy) {
        x += dx;
        y += dy;
        return *this;  // Return reference for chaining
    }
    
    void print() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};

// Example 4: Encapsulation (Bank Account)
class BankAccount {
private:
    std::string owner;
    double balance;
    
public:
    BankAccount(std::string name, double initial) : owner(name), balance(initial) {}
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    double getBalance() const {
        return balance;
    }
    
    std::string getOwner() const {
        return owner;
    }
};

// Example 5: Static members
class IDGenerator {
private:
    static int nextID;  // Shared across all instances
    int myID;
    
public:
    IDGenerator() {
        myID = nextID++;
    }
    
    int getID() const {
        return myID;
    }
    
    static int getNextID() {
        return nextID;
    }
};

// Must define static member outside class
int IDGenerator::nextID = 1;

// Example 6: Const correctness
class Temperature {
private:
    double celsius;
    
public:
    Temperature(double c) : celsius(c) {}
    
    double getCelsius() const {  // Const method
        return celsius;
    }
    
    double getFahrenheit() const {  // Const method
        return celsius * 9.0 / 5.0 + 32.0;
    }
    
    void setCelsius(double c) {  // Non-const method
        celsius = c;
    }
};

int main() {
    std::cout << "=== Example 1: Basic Class ===" << std::endl;
    Rectangle rect;
    rect.setDimensions(10, 5);
    std::cout << "Area: " << rect.area() << std::endl;
    std::cout << "Perimeter: " << rect.perimeter() << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Example 2: Class vs Struct Access ===" << std::endl;
    MyStruct s;
    s.x = 10;  // OK: public by default
    
    MyClass c;
    // c.x = 10;  // ERROR: private by default
    std::cout << "Struct has public default, class has private default" << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Example 3: this Pointer and Chaining ===" << std::endl;
    Point p;
    p.set(0, 0);
    std::cout << "Initial point: ";
    p.print();
    
    p.move(3, 4).move(1, 1);  // Chaining!
    std::cout << "After move(3,4).move(1,1): ";
    p.print();
    std::cout << std::endl;
    
    std::cout << "=== Example 4: Encapsulation ===" << std::endl;
    BankAccount account("Alice", 1000.0);
    std::cout << "Owner: " << account.getOwner() << std::endl;
    std::cout << "Initial balance: $" << account.getBalance() << std::endl;
    
    account.deposit(500.0);
    std::cout << "After deposit $500: $" << account.getBalance() << std::endl;
    
    if (account.withdraw(200.0)) {
        std::cout << "Withdrew $200" << std::endl;
    }
    std::cout << "Final balance: $" << account.getBalance() << std::endl;
    
    if (!account.withdraw(2000.0)) {
        std::cout << "Cannot withdraw $2000 (insufficient funds)" << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "=== Example 5: Static Members ===" << std::endl;
    std::cout << "Next ID will be: " << IDGenerator::getNextID() << std::endl;
    
    IDGenerator gen1;
    IDGenerator gen2;
    IDGenerator gen3;
    
    std::cout << "gen1 ID: " << gen1.getID() << std::endl;
    std::cout << "gen2 ID: " << gen2.getID() << std::endl;
    std::cout << "gen3 ID: " << gen3.getID() << std::endl;
    std::cout << "Next ID will be: " << IDGenerator::getNextID() << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Example 6: Const Correctness ===" << std::endl;
    Temperature temp(25.0);
    std::cout << "Temperature: " << temp.getCelsius() << "°C" << std::endl;
    std::cout << "            " << temp.getFahrenheit() << "°F" << std::endl;
    
    const Temperature freezing(0.0);
    std::cout << "Freezing: " << freezing.getCelsius() << "°C" << std::endl;
    // freezing.setCelsius(10);  // ERROR: can't call non-const method on const object
    std::cout << std::endl;
    
    std::cout << "All examples completed!" << std::endl;
    return 0;
}
