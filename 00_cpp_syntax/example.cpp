#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>

// =============================================================================
// Example 1: Namespaces
// C has one global scope; C++ lets you organize names into namespaces.
// =============================================================================
namespace Math {
    constexpr double PI = 3.14159265358979;

    double circleArea(double radius) {
        return PI * radius * radius;
    }
}

namespace Physics {
    constexpr double PI = 3.14159265358979;   // No collision with Math::PI
    constexpr double G  = 9.81;               // Gravity (m/s^2)

    double fallingDistance(double time) {
        return 0.5 * G * time * time;
    }
}

void demoNamespaces() {
    std::cout << "=== Namespaces ===" << std::endl;

    std::cout << "Math::PI           = " << Math::PI << std::endl;
    std::cout << "Circle area (r=5)  = " << Math::circleArea(5.0) << std::endl;
    std::cout << "Fall distance (3s) = " << Physics::fallingDistance(3.0) << " m" << std::endl;

    // 'using' imports a single name into the current scope
    using Math::circleArea;
    std::cout << "circleArea(10)     = " << circleArea(10.0) << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// Example 2: iostream — type-safe I/O
// No format specifiers, no type mismatches.
// =============================================================================
void demoIOStream() {
    std::cout << "=== iostream ===" << std::endl;

    int age = 30;
    double gpa = 3.87;
    std::string name = "Alice";

    // Output — types are resolved at compile time
    std::cout << name << " is " << age << " years old with GPA " << gpa << std::endl;

    // Chaining: each << returns the stream, so calls can be chained
    std::cout << "Hex: " << std::hex << 255 << std::dec << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// Example 3: std::string vs C strings
// =============================================================================
void demoString() {
    std::cout << "=== std::string ===" << std::endl;

    std::string a = "Hello";
    std::string b = ", World!";
    std::string c = a + b;                     // Concatenation (no strcat)

    std::cout << "c         = " << c << std::endl;
    std::cout << "length    = " << c.length() << std::endl;
    std::cout << "substr    = " << c.substr(0, 5) << std::endl;
    std::cout << "find ','  = position " << c.find(',') << std::endl;

    // Comparison — just use == (no strcmp)
    if (a == "Hello") {
        std::cout << "a equals \"Hello\"" << std::endl;
    }

    // Iterate characters
    std::cout << "Characters: ";
    for (char ch : c) {
        std::cout << ch << ' ';
    }
    std::cout << std::endl << std::endl;
}

// =============================================================================
// Example 4: bool, nullptr, and new/delete
// =============================================================================
void demoTypesAndMemory() {
    std::cout << "=== bool, nullptr, new/delete ===" << std::endl;

    // bool is a first-class type
    bool isEven = (42 % 2 == 0);
    std::cout << std::boolalpha;  // Print "true"/"false" instead of 1/0
    std::cout << "42 is even? " << isEven << std::endl;

    // nullptr — a typed null pointer constant (not 0 or NULL)
    int* p = nullptr;
    if (p == nullptr) {
        std::cout << "p is null" << std::endl;
    }

    // new / delete — type-aware heap allocation
    int* value = new int(99);           // Allocate + initialize
    std::cout << "Heap value = " << *value << std::endl;
    delete value;                        // Free

    int* arr = new int[5]{10, 20, 30, 40, 50};
    std::cout << "arr[2]     = " << arr[2] << std::endl;
    delete[] arr;                        // Free array

    std::cout << std::endl;
}

// =============================================================================
// Example 5: C++ style casts
// =============================================================================
void demoCasts() {
    std::cout << "=== C++ Casts ===" << std::endl;

    double pi = 3.14159;

    // static_cast — safe, compile-time checked conversion
    int truncated = static_cast<int>(pi);
    std::cout << "static_cast<int>(3.14159) = " << truncated << std::endl;

    // const_cast — strip const (use with extreme care)
    const int secret = 42;
    const int* cp = &secret;
    int* mp = const_cast<int*>(cp);
    std::cout << "const_cast: *mp = " << *mp << std::endl;

    // reinterpret_cast — raw bit-level cast
    long address = reinterpret_cast<long>(&pi);
    std::cout << "Address of pi as long: " << address << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// Example 6: auto and type deduction
// =============================================================================
void demoAuto() {
    std::cout << "=== auto ===" << std::endl;

    auto x = 42;           // int
    auto pi = 3.14;        // double
    auto greeting = std::string("Hello, auto!");  // std::string

    std::cout << "x        = " << x << " (int)" << std::endl;
    std::cout << "pi       = " << pi << " (double)" << std::endl;
    std::cout << "greeting = " << greeting << " (std::string)" << std::endl;

    // auto is invaluable with complex types
    std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
    auto it = scores.begin();  // std::map<std::string,int>::iterator
    std::cout << "First entry: " << it->first << " -> " << it->second << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// Example 7: Range-based for loop
// =============================================================================
void demoRangeFor() {
    std::cout << "=== Range-based for ===" << std::endl;

    std::vector<int> nums = {10, 20, 30, 40, 50};

    // Read-only iteration
    std::cout << "Values: ";
    for (const auto& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Modify in-place
    for (auto& n : nums) {
        n += 1;
    }
    std::cout << "After +1: ";
    for (const auto& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Works with maps too
    std::map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}};
    for (const auto& [name, age] : ages) {       // Structured binding (C++17)
        std::cout << name << " is " << age << std::endl;
    }

    std::cout << std::endl;
}

// =============================================================================
// Example 8: Default parameters
// =============================================================================
void greet(const std::string& name, const std::string& greeting = "Hello", int times = 1) {
    for (int i = 0; i < times; ++i) {
        std::cout << greeting << ", " << name << "!" << std::endl;
    }
}

void demoDefaultParams() {
    std::cout << "=== Default Parameters ===" << std::endl;

    greet("Alice");                    // Uses defaults: "Hello", 1
    greet("Bob", "Hi");               // Uses default: 1
    greet("Charlie", "Hey", 3);       // All specified

    std::cout << std::endl;
}

// =============================================================================
// Example 9: constexpr — compile-time computation
// =============================================================================
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void demoConstexpr() {
    std::cout << "=== constexpr ===" << std::endl;

    constexpr int fact5 = factorial(5);     // Evaluated at compile time
    constexpr int fib10 = fibonacci(10);

    std::cout << "5!  = " << fact5  << std::endl;   // 120
    std::cout << "F10 = " << fib10  << std::endl;   // 55

    // Can be used as array size (must be compile-time constant)
    constexpr int SIZE = factorial(3);  // 6
    int buffer[SIZE];
    std::cout << "buffer has " << SIZE << " elements" << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// Example 10: Enum classes (scoped enums)
// =============================================================================
// Old C-style enum — pollutes enclosing scope
enum OldColor { RED, GREEN, BLUE };

// C++ scoped enum — names are scoped, no implicit int conversion
enum class Direction { North, South, East, West };
enum class TrafficLight { Red, Yellow, Green };

void demoEnumClass() {
    std::cout << "=== Enum Classes ===" << std::endl;

    // Old style — implicit conversion to int, names in global scope
    OldColor c = RED;
    int colorVal = c;   // OK (implicit)
    std::cout << "OldColor RED = " << colorVal << std::endl;

    // Scoped enum — explicit casting required
    Direction d = Direction::North;
    // int dirVal = d;   // ERROR: no implicit conversion
    int dirVal = static_cast<int>(d);
    std::cout << "Direction::North = " << dirVal << std::endl;

    // No name collision — TrafficLight::Red != OldColor::RED ambiguity
    TrafficLight light = TrafficLight::Green;
    if (light == TrafficLight::Green) {
        std::cout << "Traffic light is green — go!" << std::endl;
    }

    std::cout << std::endl;
}

// =============================================================================
// Example 11: Uniform initialization and initializer lists
// =============================================================================
void demoUniformInit() {
    std::cout << "=== Uniform Initialization ===" << std::endl;

    // Brace initialization works everywhere
    int x{42};
    double pi{3.14};
    std::string s{"Hello"};
    std::vector<int> v{1, 2, 3, 4, 5};

    std::cout << "x  = " << x << std::endl;
    std::cout << "pi = " << pi << std::endl;
    std::cout << "s  = " << s << std::endl;
    std::cout << "v  = ";
    for (auto val : v) std::cout << val << " ";
    std::cout << std::endl;

    // Prevents narrowing conversions
    // int narrow{3.14};  // ERROR: narrowing conversion
    int ok = 3.14;        // C style: silently truncates to 3 (legal but risky)
    std::cout << "int ok = 3.14 -> " << ok << std::endl;

    // Initializer list with map
    std::map<std::string, int> m{{"one", 1}, {"two", 2}, {"three", 3}};
    for (const auto& [key, val] : m) {
        std::cout << key << " -> " << val << std::endl;
    }

    std::cout << std::endl;
}

// =============================================================================
// Example 12: Structured bindings (C++17)
// =============================================================================
std::tuple<int, std::string, double> getStudentInfo() {
    return {101, "Alice", 3.9};
}

void demoStructuredBindings() {
    std::cout << "=== Structured Bindings ===" << std::endl;

    // Unpack a tuple
    auto [id, name, gpa] = getStudentInfo();
    std::cout << "ID: " << id << ", Name: " << name << ", GPA: " << gpa << std::endl;

    // Unpack a pair
    std::pair<std::string, int> p{"Bob", 42};
    auto [pName, pAge] = p;
    std::cout << pName << " is " << pAge << std::endl;

    // Iterate map with structured bindings
    std::map<std::string, double> temps = {
        {"New York", 22.5},
        {"London", 15.0},
        {"Tokyo", 28.3}
    };
    for (const auto& [city, temp] : temps) {
        std::cout << city << ": " << temp << " C" << std::endl;
    }

    std::cout << std::endl;
}

// =============================================================================
// main
// =============================================================================
int main() {
    demoNamespaces();
    demoIOStream();
    demoString();
    demoTypesAndMemory();
    demoCasts();
    demoAuto();
    demoRangeFor();
    demoDefaultParams();
    demoConstexpr();
    demoEnumClass();
    demoUniformInit();
    demoStructuredBindings();

    return 0;
}
