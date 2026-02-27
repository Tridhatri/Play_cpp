#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>

// =============================================================================
// SOLUTION 1: Namespaces
// =============================================================================
namespace Geometry {
    constexpr double PI = 3.14159265358979;

    double circleArea(double radius) {
        return PI * radius * radius;
    }

    double rectangleArea(double w, double h) {
        return w * h;
    }
}

namespace Converter {
    double celsiusToFahrenheit(double c) {
        return c * 9.0 / 5.0 + 32;
    }

    double fahrenheitToCelsius(double f) {
        return (f - 32) * 5.0 / 9.0;
    }
}

void testNamespaces() {
    std::cout << "=== Exercise 1: Namespaces ===" << std::endl;

    std::cout << "Circle area (r=5):    " << Geometry::circleArea(5.0) << std::endl;
    std::cout << "Rectangle (3x4):      " << Geometry::rectangleArea(3.0, 4.0) << std::endl;
    std::cout << "100 C in F:           " << Converter::celsiusToFahrenheit(100.0) << std::endl;
    std::cout << "32 F in C:            " << Converter::fahrenheitToCelsius(32.0) << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// SOLUTION 2: std::string operations
// =============================================================================
void testStrings() {
    std::cout << "=== Exercise 2: std::string ===" << std::endl;

    std::string first = "Hello";
    std::string second = "World";

    // Concatenate
    std::string combined = first + ", " + second + "!";
    std::cout << "Combined: " << combined << std::endl;

    // Length
    std::cout << "Length: " << combined.length() << std::endl;

    // Extract "World" using find + substr
    size_t pos = combined.find("World");
    std::string extracted = combined.substr(pos, 5);
    std::cout << "Extracted: " << extracted << std::endl;

    // Replace "World" with "C++"
    combined.replace(pos, 5, "C++");
    std::cout << "Replaced: " << combined << std::endl;

    // Compare
    std::cout << "Match: " << std::boolalpha << (combined == "Hello, C++!") << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// SOLUTION 3: auto and range-based for
// =============================================================================
void testAutoAndRangeFor() {
    std::cout << "=== Exercise 3: auto & range-based for ===" << std::endl;

    std::vector<int> numbers = {15, 8, 23, 42, 4, 16};

    // Print all numbers
    std::cout << "Original: ";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Square every number in-place
    for (auto& n : numbers) {
        n = n * n;
    }

    // Print squared
    std::cout << "Squared:  ";
    for (const auto& n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Map with structured bindings
    std::map<std::string, double> prices = {
        {"Apple", 1.50},
        {"Banana", 0.75},
        {"Cherry", 3.00}
    };
    for (const auto& [fruit, price] : prices) {
        std::cout << fruit << ": $" << price << std::endl;
    }

    std::cout << std::endl;
}

// =============================================================================
// SOLUTION 4: Default parameters
// =============================================================================
std::string formatNumber(int number, const std::string& prefix = "",
                         const std::string& suffix = "", bool showSign = false) {
    std::string result = prefix;
    if (showSign && number > 0) {
        result += "+";
    }
    result += std::to_string(number);
    result += suffix;
    return result;
}

void testDefaultParams() {
    std::cout << "=== Exercise 4: Default Parameters ===" << std::endl;

    std::cout << formatNumber(42) << std::endl;                       // "42"
    std::cout << formatNumber(42, "$") << std::endl;                  // "$42"
    std::cout << formatNumber(42, "", " kg") << std::endl;            // "42 kg"
    std::cout << formatNumber(-5, "$", "", true) << std::endl;        // "$-5"
    std::cout << formatNumber(7, "", " pts", true) << std::endl;      // "+7 pts"

    std::cout << std::endl;
}

// =============================================================================
// SOLUTION 5: constexpr
// =============================================================================
constexpr int power(int base, int exp) {
    return (exp == 0) ? 1 : base * power(base, exp - 1);
}

constexpr int sumUpTo(int n) {
    return (n <= 0) ? 0 : n + sumUpTo(n - 1);
}

void testConstexpr() {
    std::cout << "=== Exercise 5: constexpr ===" << std::endl;

    constexpr int p = power(2, 10);       // 1024
    constexpr int s = sumUpTo(100);        // 5050
    std::cout << "2^10       = " << p << std::endl;
    std::cout << "sum(1..100)= " << s << std::endl;

    // Use constexpr result as array size — proof it's compile-time
    int buffer[power(2, 4)];  // 16 elements
    std::cout << "buffer size = " << sizeof(buffer) / sizeof(buffer[0]) << std::endl;

    std::cout << std::endl;
}

// =============================================================================
// SOLUTION 6: Enum classes
// =============================================================================
enum class Suit { Hearts, Diamonds, Clubs, Spades };

enum class Rank {
    Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
    Jack, Queen, King
};

std::string suitToString(Suit s) {
    switch (s) {
        case Suit::Hearts:   return "Hearts";
        case Suit::Diamonds: return "Diamonds";
        case Suit::Clubs:    return "Clubs";
        case Suit::Spades:   return "Spades";
        default:             return "Unknown";
    }
}

std::string rankToString(Rank r) {
    switch (r) {
        case Rank::Ace:   return "Ace";
        case Rank::Jack:  return "Jack";
        case Rank::Queen: return "Queen";
        case Rank::King:  return "King";
        default:          return std::to_string(static_cast<int>(r));
    }
}

void testEnumClass() {
    std::cout << "=== Exercise 6: Enum Classes ===" << std::endl;

    Suit s = Suit::Hearts;
    Rank r = Rank::Ace;
    std::cout << rankToString(r) << " of " << suitToString(s) << std::endl;

    s = Suit::Spades;
    r = Rank::King;
    std::cout << rankToString(r) << " of " << suitToString(s) << std::endl;

    // int x = s;  // Does NOT compile with enum class — that's the point!

    std::cout << std::endl;
}

// =============================================================================
// SOLUTION 7: Uniform initialization and structured bindings
// =============================================================================
std::tuple<std::string, int, double> createProduct(
    const std::string& name, int qty, double price) {
    return {name, qty, price};
}

void testStructuredBindings() {
    std::cout << "=== Exercise 7: Structured Bindings ===" << std::endl;

    // Vector with uniform initialization
    std::vector<int> v{10, 20, 30, 40, 50};
    std::cout << "Vector: ";
    for (auto val : v) std::cout << val << " ";
    std::cout << std::endl;

    // Structured binding with tuple
    auto [name, qty, price] = createProduct("Widget", 100, 9.99);
    std::cout << name << ": " << qty << " units @ $" << price << std::endl;

    // Map with structured bindings
    std::map<std::string, long> populations{
        {"USA", 331000000L},
        {"India", 1400000000L},
        {"Japan", 125000000L}
    };
    for (const auto& [country, pop] : populations) {
        std::cout << country << ": " << pop << std::endl;
    }

    std::cout << std::endl;
}

// =============================================================================
// SOLUTION 8: Putting it all together
// =============================================================================
enum class Grade { A, B, C, D, F };

constexpr double gradeToGPA(Grade g) {
    switch (g) {
        case Grade::A: return 4.0;
        case Grade::B: return 3.0;
        case Grade::C: return 2.0;
        case Grade::D: return 1.0;
        case Grade::F: return 0.0;
        default:       return 0.0;
    }
}

std::string gradeToString(Grade g) {
    switch (g) {
        case Grade::A: return "A";
        case Grade::B: return "B";
        case Grade::C: return "C";
        case Grade::D: return "D";
        case Grade::F: return "F";
        default:       return "?";
    }
}

std::pair<double, Grade> analyzeGrades(const std::vector<Grade>& grades) {
    double total = 0.0;
    Grade best = Grade::F;

    for (const auto& g : grades) {
        double gpa = gradeToGPA(g);
        total += gpa;
        if (gpa > gradeToGPA(best)) {
            best = g;
        }
    }

    double avg = grades.empty() ? 0.0 : total / static_cast<double>(grades.size());
    return {avg, best};
}

void testPuttingItTogether() {
    std::cout << "=== Exercise 8: Putting It All Together ===" << std::endl;

    std::vector<Grade> grades{Grade::A, Grade::B, Grade::A, Grade::C, Grade::B};

    auto [avgGPA, bestGrade] = analyzeGrades(grades);

    std::cout << "Grades: ";
    for (const auto& g : grades) {
        std::cout << gradeToString(g) << " ";
    }
    std::cout << std::endl;
    std::cout << "Average GPA: " << avgGPA << std::endl;
    std::cout << "Best grade:  " << gradeToString(bestGrade) << std::endl;

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
