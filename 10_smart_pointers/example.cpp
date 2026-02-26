#include <iostream>
#include <memory>
#include <vector>

// Example 1: unique_ptr basic usage
void uniquePtrBasics() {
    std::cout << "=== unique_ptr Basics ===" << std::endl;
    
    // Create unique_ptr
    auto ptr = std::make_unique<int>(42);
    std::cout << "Value: " << *ptr << std::endl;
    
    // Cannot copy
    // auto ptr2 = ptr;  // ERROR
    
    // Can move
    auto ptr2 = std::move(ptr);
    std::cout << "After move, ptr2: " << *ptr2 << std::endl;
    std::cout << "ptr is now: " << (ptr == nullptr ? "nullptr" : "not null") << std::endl;
    
    // Array
    auto arr = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }
    
    std::cout << std::endl;
}

// Example 2: shared_ptr basic usage
void sharedPtrBasics() {
    std::cout << "=== shared_ptr Basics ===" << std::endl;
    
    auto ptr1 = std::make_shared<int>(100);
    std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl;
    
    {
        auto ptr2 = ptr1;  // Share ownership
        std::cout << "After creating ptr2, count: " << ptr1.use_count() << std::endl;
        std::cout << "ptr2 value: " << *ptr2 << std::endl;
    }  // ptr2 destroyed
    
    std::cout << "After ptr2 destroyed, count: " << ptr1.use_count() << std::endl;
    
    std::cout << std::endl;
}

// Example 3: weak_ptr to break cycles
class Node {
public:
    int data;
    std::shared_ptr<Node> next;      // Strong reference
    std::weak_ptr<Node> prev;        // Weak reference (breaks cycle)
    
    Node(int d) : data(d) {
        std::cout << "Node " << data << " created\n";
    }
    
    ~Node() {
        std::cout << "Node " << data << " destroyed\n";
    }
};

void weakPtrExample() {
    std::cout << "=== weak_ptr Example ===" << std::endl;
    
    auto node1 = std::make_shared<Node>(1);
    auto node2 = std::make_shared<Node>(2);
    
    node1->next = node2;   // Strong
    node2->prev = node1;   // Weak (doesn't increase ref count)
    
    std::cout << "node1 count: " << node1.use_count() << std::endl;  // 1
    std::cout << "node2 count: " << node2.use_count() << std::endl;  // 2
    
    // Access through weak_ptr
    if (auto temp = node2->prev.lock()) {
        std::cout << "Previous node data: " << temp->data << std::endl;
    }
    
    std::cout << "Exiting scope...\n";
    std::cout << std::endl;
}  // Both nodes properly destroyed (no leak!)

// Example 4: Factory function returning unique_ptr
class Widget {
    int id;
public:
    Widget(int i) : id(i) {
        std::cout << "Widget " << id << " created\n";
    }
    
    ~Widget() {
        std::cout << "Widget " << id << " destroyed\n";
    }
    
    void use() {
        std::cout << "Using Widget " << id << std::endl;
    }
};

std::unique_ptr<Widget> createWidget(int id) {
    return std::make_unique<Widget>(id);
}

void factoryExample() {
    std::cout << "=== Factory Pattern ===" << std::endl;
    
    auto widget = createWidget(42);
    widget->use();
    
    std::cout << std::endl;
}

// Example 5: Container of smart pointers
void containerExample() {
    std::cout << "=== Containers with Smart Pointers ===" << std::endl;
    
    std::vector<std::unique_ptr<Widget>> widgets;
    
    widgets.push_back(std::make_unique<Widget>(1));
    widgets.push_back(std::make_unique<Widget>(2));
    widgets.push_back(std::make_unique<Widget>(3));
    
    for (const auto& w : widgets) {
        w->use();
    }
    
    std::cout << "Exiting scope...\n";
    std::cout << std::endl;
}  // All widgets automatically destroyed

// Example 6: Polymorphism with smart pointers
class Animal {
public:
    virtual void makeSound() = 0;
    virtual ~Animal() { std::cout << "Animal destroyed\n"; }
};

class Dog : public Animal {
public:
    void makeSound() override {
        std::cout << "Woof!\n";
    }
    ~Dog() { std::cout << "Dog destroyed\n"; }
};

class Cat : public Animal {
public:
    void makeSound() override {
        std::cout << "Meow!\n";
    }
    ~Cat() { std::cout << "Cat destroyed\n"; }
};

void polymorphismExample() {
    std::cout << "=== Polymorphism with Smart Pointers ===" << std::endl;
    
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make unique<Dog>());
    animals.push_back(std::make_unique<Cat>());
    
    for (const auto& animal : animals) {
        animal->makeSound();
    }
    
    std::cout << "Exiting scope...\n";
    std::cout << std::endl;
}

int main() {
    uniquePtrBasics();
    sharedPtrBasics();
    weakPtrExample();
    factoryExample();
    containerExample();
    polymorphismExample();
    
    std::cout << "All examples completed!" << std::endl;
    return 0;
}
