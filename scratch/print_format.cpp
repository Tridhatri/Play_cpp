#include <format>
#include <iostream>
#include <print>

int main(){

    std::cout << std::format("{:b}\n", 0b1010); // C++20 {:b} formats the argument as binary digits
    std::cout << std::format("{;#b}\n", 0b1010); // C++20 {:#b} formats the arguments as 0b-prefixed.
    

    std::println("{:b},{:#b}", 0b1010, 0b1010); //C++23 , format /print two arguments(same as above)

    return 0;
}

