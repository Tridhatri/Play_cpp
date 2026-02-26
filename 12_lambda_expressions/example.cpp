#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// Example 1: Basic lambda syntax
void basicLambdas() {
    std::cout << "=== Basic Lambdas ===" << std::endl;
    
    // Simple lambda
    auto greet = []() {
        std::cout << "Hello from lambda!" << std::endl;
    };
    greet();
    
    // Lambda with parameters and return
    auto add = [](int a, int b) {
        return a + b;
    };
    std::cout << "5 + 3 = " << add(5, 3) << std::endl;
    
    // Explicit return type
    auto divide = [](int a, int b) -> double {
        return static_cast<double>(a) / b;
    };
    std::cout << "7 / 2 = " << divide(7, 2) << std::endl;
    
    std::cout << std::endl;
}

// Example 2: Capture by value and reference
void captureExamples() {
    std::cout << "=== Capture Examples ===" << std::endl;
    
    int x = 10;
    int y = 20;
    
    // Capture by value
    auto byValue = [x, y]() {
        std::cout << "Captured by value: x=" << x << ", y=" << y << std::endl;
        // x++;  // ERROR: captured by value is const
    };
    byValue();
    
    // Capture by reference
    auto byRef = [&x, &y]() {
        x += 5;
        y += 10;
        std::cout << "Modified via reference: x=" << x << ", y=" << y << std::endl;
    };
    byRef();
    std::cout << "After lambda: x=" << x << ", y=" << y << std::endl;
    
    // Capture all by value
    auto captureAll = [=]() {
        std::cout << "All by value: x=" << x << ", y=" << y << std::endl;
    };
    captureAll();
    
    // Capture all by reference
    auto captureAllRef = [&]() {
        x *= 2;
        y *= 2;
    };
    captureAllRef();
    std::cout << "After doubling: x=" << x << ", y=" << y << std::endl;
    
    std::cout << std::endl;
}

// Example 3: Mutable lambdas
void mutableLambdas() {
    std::cout << "=== Mutable Lambdas ===" << std::endl;
    
    int counter = 0;
    auto incrementCopy = [counter]() mutable {
        return ++counter;  // Modifies captured copy
    };
    
    std::cout << "Call 1: " << incrementCopy() << std::endl;  // 1
    std::cout << "Call 2: " << incrementCopy() << std::endl;  // 2
    std::cout << "Original counter: " << counter << std::endl;  // Still 0
    
    std::cout << std::endl;
}

// Example 4: Lambdas with STL algorithms
void stlAlgorithms() {
    std::cout << "=== Lambdas with STL ===" << std::endl;
    
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7};
    
    // Sort descending
    std::sort(numbers.begin(), numbers.end(),
        [](int a, int b) { return a > b; });
    
    std::cout << "Sorted descending: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // Find first even number
    auto it = std::find_if(numbers.begin(), numbers.end(),
        [](int n) { return n % 2 == 0; });
    if (it != numbers.end()) {
        std::cout << "First even: " << *it << std::endl;
    }
    
    // Count numbers > 5
    int count = std::count_if(numbers.begin(), numbers.end(),
        [](int n) { return n > 5; });
    std::cout << "Numbers > 5: " << count << std::endl;
    
    // Transform: double all values
    std::vector<int> doubled(numbers.size());
    std::transform(numbers.begin(), numbers.end(), doubled.begin(),
        [](int n) { return n * 2; });
    
    std::cout << "Doubled: ";
    for (int n : doubled) std::cout << n << " ";
    std::cout << std::endl;
    
    // For_each
    std::cout << "Squared: ";
    std::for_each(numbers.begin(), numbers.end(),
        [](int n) { std::cout << n*n << " "; });
    std::cout << std::endl;
    
    std::cout << std::endl;
}

// Example 5: Generic lambdas (C++14)
void genericLambdas() {
    std::cout << "=== Generic Lambdas ===" << std::endl;
    
    auto print = [](const auto& value) {
        std::cout << value << std::endl;
    };
    
    print(42);
    print(3.14);
    print("Hello");
    print(std::string("World"));
    
    auto add = [](auto a, auto b) {
        return a + b;
    };
    
    std::cout << "5 + 10 = " << add(5, 10) << std::endl;
    std::cout << "3.14 + 2.86 = " << add(3.14, 2.86) << std::endl;
    
    std::cout << std::endl;
}

// Example 6: Lambda as callback
void processData(const std::vector<int>& data, 
                 std::function<void(int)> callback) {
    for (int value : data) {
        callback(value);
    }
}

void callbackExample() {
    std::cout << "=== Lambda as Callback ===" << std::endl;
    
    std::vector<int> data = {1, 2, 3, 4, 5};
    
    int sum = 0;
    processData(data, [&sum](int value) {
        sum += value;
    });
    
    std::cout << "Sum: " << sum << std::endl;
    
    std::cout << "Values: ";
    processData(data, [](int value) {
        std::cout << value << " ";
    });
    std::cout << std::endl << std::endl;
}

// Example 7: Immediately Invoked Lambda Expression
void iile() {
    std::cout << "=== IILE (Immediately Invoked Lambda) ===" << std::endl;
    
    int result = []() {
        int sum = 0;
        for (int i = 1; i <= 10; ++i) {
            sum += i;
        }
        return sum;
    }();  // Called immediately
    
    std::cout << "Sum of 1..10: " << result << std::endl;
    
    // Complex const initialization
    const int value = [](int x) {
        if (x > 10) return x * 2;
        else return x * 3;
    }(7);
    
    std::cout << "Complex init value: " << value << std::endl;
    
    std::cout << std::endl;
}

// Example 8: Init capture (C++14)
void initCapture() {
    std::cout << "=== Init Capture (C++14) ===" << std::endl;
    
    auto ptr = std::make_unique<int>(42);
    
    // Move ptr into lambda
    auto lambda = [ptr = std::move(ptr)]() {
        std::cout << "Value in lambda: " << *ptr << std::endl;
    };
    
    // ptr is now nullptr
    std::cout << "ptr is " << (ptr == nullptr ? "nullptr" : "not null") << std::endl;
    
    lambda();
    
    // Expression capture
    int x = 5;
    auto addTen = [value = x + 10]() {
        return value;
    };
    std::cout << "x + 10 = " << addTen() << std::endl;
    
    std::cout << std::endl;
}

int main() {
    basicLambdas();
    captureExamples();
    mutableLambdas();
    stlAlgorithms();
    genericLambdas();
    callbackExample();
    iile();
    initCapture();
    
    std::cout << "All lambda examples completed!" << std::endl;
    return 0;
}
