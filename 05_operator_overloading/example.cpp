#include <iostream>
#include <cmath>

// Example: Complex number class with operator overloading
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Arithmetic operators
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }
    
    // Compound assignment
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    // Comparison
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // Unary operators
    Complex operator-() const {
        return Complex(-real, -imag);
    }
    
    // Stream operators (must be non-member!)
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend std::istream& operator>>(std::istream& is, Complex& c);
};

// Stream operators (non-member)
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) os << "+";
    os << c.imag << "i";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c) {
    is >> c.real >> c.imag;
    return is;
}

// Example: Vector class
class Vector2D {
public:
    double x, y;
    
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}
    
    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }
    
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    double operator*(const Vector2D& v) const {  // Dot product
        return x * v.x + y * v.y;
    }
    
    Vector2D& operator++() {  // Prefix
        ++x; ++y;
        return *this;
    }
    
    Vector2D operator++(int) {  // Postfix
        Vector2D temp = *this;
        ++(*this);
        return temp;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};

// Non-member operator for scalar * vector
Vector2D operator*(double scalar, const Vector2D& v) {
    return v * scalar;
}

int main() {
    std::cout << "=== Complex Number Operators ===" << std::endl;
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    
    Complex c3 = c1 + c2;
    std::cout << "c1 + c2 = " << c3 << std::endl;
    
    Complex c4 = c1 * c2;
    std::cout << "c1 * c2 = " << c4 << std::endl;
    
    Complex c5 = -c1;
    std::cout << "-c1 = " << c5 << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "=== Vector Operators ===" << std::endl;
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);
    
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    
    Vector2D v3 = v1 + v2;
    std::cout << "v1 + v2 = " << v3 << std::endl;
    
    Vector2D v4 = v1 * 2.5;
    std::cout << "v1 * 2.5 = " << v4 << std::endl;
    
    Vector2D v5 = 3.0 * v1;
    std::cout << "3.0 * v1 = " << v5 << std::endl;
    
    double dot = v1 * v2;
    std::cout << "v1 · v2 = " << dot << std::endl;
    
    Vector2D v6 = v1++;
    std::cout << "After v1++: v1 = " << v1 << ", returned = " << v6 << std::endl;
    
    Vector2D v7 = ++v1;
    std::cout << "After ++v1: v1 = " << v1 << ", returned = " << v7 << std::endl;
    
    return 0;
}
