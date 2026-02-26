#include <iostream>
#include <string>
#include <vector>

/*
 * TODO: Implement these classes following the requirements
 */

// EXERCISE 1: Create a Circle class
class Circle {
private:
    // TODO: Add private member for radius
    
public:
    // TODO: Add method to set radius
    // TODO: Add method to calculate area (π * r²)
    // TODO: Add method to calculate circumference (2 * π * r)
    // TODO: Make calculation methods const
};

// EXERCISE 2: Student class with encapsulation
class Student {
private:
    // TODO: Add private members: name (string), grades (vector<int>)
    
public:
    // TODO: Constructor that takes name
    // TODO: Method to add grade (validate 0-100)
    // TODO: Method to get average (const)
    // TODO: Method to get name (const)
};

// EXERCISE 3: Counter with static member
class GlobalCounter {
private:
    // TODO: Add static int totalCount
    // TODO: Add instance int myCount
    
public:
    // TODO: Constructor increments totalCount
    // TODO: Static method getTotalCount()
    // TODO: Method getMyCount() const
};

// TODO: Don't forget to define the static member outside the class!

// EXERCISE 4: Shopping cart with method chaining
class ShoppingCart {
private:
    // TODO: vector<string> items
    // TODO: double total
    
public:
    // TODO: addItem(name, price) -> return *this for chaining
    // TODO: removeItem(name) -> return *this
    // TODO: getTotal() const
    // TODO: printItems() const
};

int main() {
    std::cout << "Test your implementations here!" << std::endl;
    
    // TODO: Test Circle
    // TODO: Test Student
    // TODO: Test GlobalCounter
    // TODO: Test ShoppingCart with chaining
    
    return 0;
}
