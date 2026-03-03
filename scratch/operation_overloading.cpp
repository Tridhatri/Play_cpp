#include <iostream>
#include <stdio.h>

// Let's do some basic aaah operating overloading for a class called "Point" that represents a point in 2D space.\

class Point {
    public:
        double x, y;
        Point(double x, double y) : x(x), y(y) {};
        
        // Overload the + operator to add two points together
        Point operator+(const Point& other) {
            return Point(x + other.x , y + other.y);
        }; 

        // Overload the == operator to compare two points for equality
        bool operator==(const Point& other){
            return (x == other.x && y == other.y);
        };


};


int main() {

    Point p1(1.0, 2.0);
    Point p2(3.0, 4.0);

    Point p3 = p1 + p2; // This will call the overloaded + operator
                    
    printf("p3: (%f, %f)\n", p3.x, p3.y); // Should print (4.0, 6.0)

    std::cout << "p1 == p2: " << (p1 == p2) << std::endl; // Should print 0 (false)

    return 0;
}
