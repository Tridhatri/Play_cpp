#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

const double PI = 3.14159265359;

// SOLUTION 1: Circle class
class Circle {
private:
    double radius;
    
public:
    void setRadius(double r) {
        radius = (r > 0) ? r : 0;
    }
    
    double getRadius() const {
        return radius;
    }
    
    double area() const {
        return PI * radius * radius;
    }
    
    double circumference() const {
        return 2 * PI * radius;
    }
};

// SOLUTION 2: Student class
class Student {
private:
    std::string name;
    std::vector<int> grades;
    
public:
    Student(const std::string& studentName) : name(studentName) {}
    
    void addGrade(int grade) {
        if (grade >= 0 && grade <= 100) {
            grades.push_back(grade);
        } else {
            std::cout << "Invalid grade: " << grade << " (must be 0-100)" << std::endl;
        }
    }
    
    double getAverage() const {
        if (grades.empty()) return 0.0;
        return std::accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
    }
    
    std::string getName() const {
        return name;
    }
    
    size_t getGradeCount() const {
        return grades.size();
    }
};

// SOLUTION 3: Counter with static member
class GlobalCounter {
private:
    static int totalCount;
    int myCount;
    
public:
    GlobalCounter() {
        myCount = totalCount++;
    }
    
    static int getTotalCount() {
        return totalCount;
    }
    
    int getMyCount() const {
        return myCount;
    }
};

int GlobalCounter::totalCount = 0;

// SOLUTION 4: Shopping cart with chaining
struct Item {
    std::string name;
    double price;
};

class ShoppingCart {
private:
    std::vector<Item> items;
    
public:
    ShoppingCart& addItem(const std::string& name, double price) {
        items.push_back({name, price});
        return *this;
    }
    
    ShoppingCart& removeItem(const std::string& name) {
        items.erase(
            std::remove_if(items.begin(), items.end(),
                [&name](const Item& item) { return item.name == name; }),
            items.end()
        );
        return *this;
    }
    
    double getTotal() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.price;
        }
        return total;
    }
    
    void printItems() const {
        std::cout << "Shopping Cart:" << std::endl;
        for (const auto& item : items) {
            std::cout << "  - " << item.name << ": $" << item.price << std::endl;
        }
        std::cout << "Total: $" << getTotal() << std::endl;
    }
};

int main() {
    std::cout << "=== Solution 1: Circle ===" << std::endl;
    Circle c;
    c.setRadius(5.0);
    std::cout << "Radius: " << c.getRadius() << std::endl;
    std::cout << "Area: " << c.area() << std::endl;
    std::cout << "Circumference: " << c.circumference() << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 2: Student ===" << std::endl;
    Student alice("Alice");
    alice.addGrade(85);
    alice.addGrade(90);
    alice.addGrade(78);
    alice.addGrade(150);  // Invalid
    std::cout << alice.getName() << "'s average: " << alice.getAverage() << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 3: Global Counter ===" << std::endl;
    GlobalCounter c1, c2, c3;
    std::cout << "c1 count: " << c1.getMyCount() << std::endl;
    std::cout << "c2 count: " << c2.getMyCount() << std::endl;
    std::cout << "c3 count: " << c3.getMyCount() << std::endl;
    std::cout << "Total created: " << GlobalCounter::getTotalCount() << std::endl;
    std::cout << std::endl;
    
    std::cout << "=== Solution 4: Shopping Cart ===" << std::endl;
    ShoppingCart cart;
    cart.addItem("Apple", 1.50)
        .addItem("Banana", 0.75)
        .addItem("Orange", 1.25);
    cart.printItems();
    
    std::cout << "\nAfter removing Banana:" << std::endl;
    cart.removeItem("Banana");
    cart.printItems();
    
    return 0;
}
