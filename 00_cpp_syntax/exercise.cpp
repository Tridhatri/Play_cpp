#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>

// =============================================================================
// EXERCISE 1: Namespaces
// Create two namespaces (Geometry and Converter) with functions inside them.
// =============================================================================
// TODO: Create a namespace called Geometry containing:
//   - a constexpr double PI = 3.14159265358979
//   - double circleArea(double radius)        — returns PI * r * r
//   - double rectangleArea(double w, double h) — returns w * h


// TODO: Create a namespace called Converter containing:
//   - double celsiusToFahrenheit(double c)    — returns c * 9.0/5.0 + 32
//   - double fahrenheitToCelsius(double f)    — returns (f - 32) * 5.0/9.0


void testNamespaces() {
    std::cout << "=== Exercise 1: Namespaces ===" << std::endl;

    // TODO: Uncomment after implementing the namespaces above
    // std::cout << "Circle area (r=5):    " << Geometry::circleArea(5.0) << std::endl;
    // std::cout << "Rectangle (3x4):      " << Geometry::rectangleArea(3.0, 4.0) << std::endl;
    // std::cout << "100 C in F:           " << Converter::celsiusToFahrenheit(100.0) << std::endl;
    // std::cout << "32 F in C:            " << Converter::fahrenheitToCelsius(32.0) << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// EXERCISE 2: std::string operations
// Perform various string operations WITHOUT using C string functions.
// =============================================================================
void testStrings() {
    std::cout << "=== Exercise 2: std::string ===" << std::endl;

    std::string first = "Hello";
    std::string second = "World";

    // TODO: Create a variable 'combined' that is first + ", " + second + "!"
    // std::string combined = ???;

    // TODO: Print the length of combined
    // std::cout << "Length: " << ??? << std::endl;

    // TODO: Extract the substring "World" from combined using substr()
    // Hint: find() gives you the starting position
    // std::string extracted = ???;
    // std::cout << "Extracted: " << extracted << std::endl;

    // TODO: Replace "World" with "C++" in combined using replace() or find+erase+insert
    // std::cout << "Replaced: " << combined << std::endl;

    // TODO: Compare combined with "Hello, C++!" using == and print the result
    // std::cout << "Match: " << std::boolalpha << ??? << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// EXERCISE 3: auto and range-based for
// Use auto and range-based for to process collections.
// =============================================================================
void testAutoAndRangeFor() {
    std::cout << "=== Exercise 3: auto & range-based for ===" << std::endl;

    std::vector<int> numbers = {15, 8, 23, 42, 4, 16};

    // TODO: Use a range-based for with auto to print all numbers separated by spaces
    // Your code here

    // TODO: Use a range-based for with auto& to square every number in-place
    // Your code here

    // TODO: Print the squared numbers
    // Your code here

    // TODO: Create a map of fruit -> price, iterate with structured bindings, and print
    // std::map<std::string, double> prices = { ... };
    // for (const auto& [fruit, price] : prices) { ... }

    std::cout << std::endl;
}

// =============================================================================
// EXERCISE 4: Default parameters
// Write a function that formats a number for display with configurable options.
// =============================================================================
// TODO: Write a function called formatNumber that takes:
//   - int number          (required)
//   - std::string prefix  (default: "")
//   - std::string suffix  (default: "")
//   - bool showSign       (default: false)
//   It should return a std::string like "[prefix][+/-]number[suffix]"
//   If showSign is true, prepend "+" for positive numbers.
//
// Examples:
//   formatNumber(42)                         -> "42"
//   formatNumber(42, "$")                    -> "$42"
//   formatNumber(42, "", " kg")              -> "42 kg"
//   formatNumber(-5, "$", "", true)          -> "$-5"
//   formatNumber(7, "", " pts", true)        -> "+7 pts"

// std::string formatNumber(???) {
//     // Your code here
// }

void testDefaultParams() {
    std::cout << "=== Exercise 4: Default Parameters ===" << std::endl;

    // TODO: Uncomment after implementing formatNumber
    // std::cout << formatNumber(42) << std::endl;                       // "42"
    // std::cout << formatNumber(42, "$") << std::endl;                  // "$42"
    // std::cout << formatNumber(42, "", " kg") << std::endl;            // "42 kg"
    // std::cout << formatNumber(-5, "$", "", true) << std::endl;        // "$-5"
    // std::cout << formatNumber(7, "", " pts", true) << std::endl;      // "+7 pts"

    std::cout << std::endl;
}

// =============================================================================
// EXERCISE 5: constexpr
// Write compile-time functions.
// =============================================================================
// TODO: Write a constexpr function called power(int base, int exp) that
//       computes base^exp at compile time using recursion.

// constexpr int power(int base, int exp) {
//     // Your code here
// }

// TODO: Write a constexpr function called sumUpTo(int n) that returns
//       1 + 2 + ... + n at compile time.

// constexpr int sumUpTo(int n) {
//     // Your code here
// }

void testConstexpr() {
    std::cout << "=== Exercise 5: constexpr ===" << std::endl;

    // TODO: Uncomment after implementing the functions
    // constexpr int p = power(2, 10);       // Should be 1024
    // constexpr int s = sumUpTo(100);        // Should be 5050
    // std::cout << "2^10       = " << p << std::endl;
    // std::cout << "sum(1..100)= " << s << std::endl;

    // TODO: Use power() result as an array size to prove it's compile-time
    // int buffer[power(2, 4)];  // 16 elements
    // std::cout << "buffer size = " << sizeof(buffer)/sizeof(buffer[0]) << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// EXERCISE 6: Enum classes
// Create a scoped enum and a function that uses it.
// =============================================================================
// TODO: Create an enum class called Suit with values: Hearts, Diamonds, Clubs, Spades

// TODO: Create an enum class called Rank with values: Ace = 1, Two, Three, ... Ten, Jack, Queen, King

// TODO: Write a function std::string suitToString(Suit s) that returns the name as a string

// TODO: Write a function std::string rankToString(Rank r) that returns the name
//       (for face cards return "Ace", "Jack", "Queen", "King"; for numbers return the number)

void testEnumClass() {
    std::cout << "=== Exercise 6: Enum Classes ===" << std::endl;

    // TODO: Uncomment after implementing
    // Suit s = Suit::Hearts;
    // Rank r = Rank::Ace;
    // std::cout << rankToString(r) << " of " << suitToString(s) << std::endl;

    // s = Suit::Spades;
    // r = Rank::King;
    // std::cout << rankToString(r) << " of " << suitToString(s) << std::endl;

    // Demonstrate that Suit and int don't accidentally mix
    // int x = s;  // This should NOT compile with enum class (that's the point!)

    std::cout << std::endl;
}

// =============================================================================
// EXERCISE 7: Uniform initialization and structured bindings
// =============================================================================
// TODO: Write a function that returns a std::tuple<std::string, int, double>
//       representing a product: (name, quantity, price)
// std::tuple<std::string, int, double> createProduct(
//     const std::string& name, int qty, double price) {
//     // Your code here
// }

void testStructuredBindings() {
    std::cout << "=== Exercise 7: Structured Bindings ===" << std::endl;

    // TODO: Create a vector using uniform initialization with at least 5 elements
    // std::vector<int> v{ ... };

    // TODO: Call createProduct and unpack with structured bindings
    // auto [name, qty, price] = createProduct("Widget", 100, 9.99);
    // std::cout << name << ": " << qty << " units @ $" << price << std::endl;

    // TODO: Create a map of country -> population (at least 3 entries)
    //       using uniform initialization, then iterate with structured bindings
    // std::map<std::string, long> populations{ ... };
    // for (const auto& [country, pop] : populations) {
    //     std::cout << country << ": " << pop << std::endl;
    // }

    std::cout << std::endl;
}

// =============================================================================
// EXERCISE 8: Putting it all together
// Build a small student grade tracker using everything from this module.
// =============================================================================
// TODO:
// 1. Create an enum class called Grade { A, B, C, D, F }
// 2. Write a constexpr function gradeToGPA(Grade g) that returns a double
//    (A=4.0, B=3.0, C=2.0, D=1.0, F=0.0)
// 3. Write a function that takes a std::vector<Grade>& and returns a
//    std::pair<double, Grade> with the (averageGPA, bestGrade)
// 4. In testPuttingItTogether(), create a vector of grades, call your function,
//    use structured bindings to unpack the result, and print it.

void testPuttingItTogether() {
    std::cout << "=== Exercise 8: Putting It All Together ===" << std::endl;

    // Your code here

    std::cout << std::endl;
}

// =============================================================================
// main
// =============================================================================
int main() {
    testNamespaces();
    testStrings();
    testAutoAndRangeFor();
    testDefaultParams();
    testConstexpr();
    testEnumClass();
    testStructuredBindings();
    testPuttingItTogether();

    return 0;
}
