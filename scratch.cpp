#include <bitset>
#include <iostream>


int main(){


std::bitset<8> bin1{ 0b1100'0101};
std::bitset<8> bin2{ 0xC5};
std::bitset<8> bin3{ 0b11000101};

std::cout << "Bin1: " << bin1 << "\n";
std::cout << "Bin2: " << bin2 << "\n";
std::cout << "Bin3: " << bin3 << "\n";


return 0;

}









