#include <iostream>


class Student {
    public:
        std::string name;
        int age;

        void display() {
            std::cout << "Name: " << name << ", Age: " << age << std::endl;
        }
};

// Why use Public keyword?
// The public keyword in C++ is an access specifier that allows members of a class to be accessible from outside the class. 
// When you declare a member as public, it can be accessed and modified by any code that has access to an instance of the class. 
// This is useful for allowing users of the class to interact


// Public can be accessed from anywhere in the program, while private members can only be accessed from within the class itself.
// Public can be used for both data members and member functions, while private can only be used for data members.
// Public members can be accessed and modified by any code that has access to an instance of the class, 
// while private members can only be accessed and modified by member functions of the class.
//
//
// A puublic member function is a function that is declared as public in a class. This means that it can be accessed and called from outside the class, allowing users of the class to interact with its functionality.
// There is no such thing as private member function, 
// but there are private data members. 
// Private data members are variables that are declared as private in a class, 
// meaning they can only be accessed and modified by member functions of the class. 
// This encapsulation helps to protect the internal state of the object and ensures that it can only be modified in controlled ways through the class's public interface.


// Why is there no private member function?
// In C++, there is no such thing as a private member function because member functions are typically used to provide an interface for interacting with the class's data members.
// Private member functions would not be accessible from outside the class, which would limit their usefulness in providing functionality to users of the class.
// Instead, private member functions can be used within the class to perform internal operations or calculations that are not intended to be exposed to users of the class.
// For example, a private member function might be used to validate input data or perform a complex calculation that is not relevant to the user of the class.
// 


// Inheritance example
//

class GraduateStudent : public Student {
    public:
        std:: string thesisTitle;
        void displayThesis() {
            std::cout << "Thesis Title: " << thesisTitle << std::endl;
        }
};


int main(){

    Student student1;
    student1.name = "Alice";
    student1.age = 20;
    student1.display();

    GraduateStudent gradStudent1;
    gradStudent1.name = "Bob";
    gradStudent1.age = 25;
    gradStudent1.thesisTitle = "Machine Learning in Healthcare";
    gradStudent1.display();
    gradStudent1.displayThesis();

    return 0;


};


class Calculator {
    private:
        int value;
    

    public:
        // How to write a constructor
        Calculator(int initialValue) {
            value = initialValue;
        }

        // What are the different ways to write a constructor?
        // 1. Default constructor: A constructor that takes no arguments and initializes the object with default values. 
        // 2. Parameterized constructor: A constructor that takes arguments to initialize the object with specific values.
        // 3. Copy constructor: A constructor that creates a new object as a copy of an existing object.
        // 4. Move constructor: A constructor that transfers ownership of resources from a temporary object to a new object.
        //
















}

















