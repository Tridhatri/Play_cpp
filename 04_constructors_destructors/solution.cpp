#include <iostream>
#include <cstring>
#include <cstdio>

// SOLUTION: String class with RAII
class String {
private:
    char* data;
    size_t length;
    
public:
    // Default constructor
    String() : data(nullptr), length(0) {
        std::cout << "String: default constructor" << std::endl;
    }
    
    // Constructor from C-string
    String(const char* str) {
        if (str) {
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
            length = 0;
        }
        std::cout << "String: constructor from \"" << (str ? str : "nullptr") << "\"" << std::endl;
    }
    
    // Copy constructor (deep copy)
    String(const String& other) : length(other.length) {
        if (other.data) {
            data = new char[length + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
        std::cout << "String: copy constructor" << std::endl;
    }
    
    // Destructor
    ~String() {
        std::cout << "String: destructor (freeing \"" << (data ? data : "nullptr") << "\")" << std::endl;
        delete[] data;
    }
    
    void print() const {
        std::cout << (data ? data : "(empty)") << std::endl;
    }
    
    const char* c_str() const { return data ? data : ""; }
};

// SOLUTION: RAII File handler
class FileHandler {
private:
    FILE* handle;
    std::string filename;
    
public:
    FileHandler(const char* name, const char* mode) : filename(name) {
        handle = fopen(name, mode);
        if (handle) {
            std::cout << "FileHandler: opened " << filename << std::endl;
        } else {
            std::cout << "FileHandler: failed to open " << filename << std::endl;
        }
    }
    
    ~FileHandler() {
        if (handle) {
            fclose(handle);
            std::cout << "FileHandler: closed " << filename << std::endl;
        }
    }
    
    bool isOpen() const { return handle != nullptr; }
    
    void write(const char* text) {
        if (handle) {
            fputs(text, handle);
        }
    }
    
    std::string read() {
        if (!handle) return "";
        char buffer[256];
        std::string result;
        while (fgets(buffer, sizeof(buffer), handle)) {
            result += buffer;
        }
        return result;
    }
};

int main() {
    std::cout << "=== Solution: String Class ===" << std::endl;
    {
        String s1;
        String s2("Hello");
        String s3 = s2;  // Copy constructor
        
        std::cout << "s1: "; s1.print();
        std::cout << "s2: "; s2.print();
        std::cout << "s3: "; s3.print();
    }  // Destructors called
    std::cout << std::endl;
    
    std::cout << "=== Solution: RAII File Handler ===" << std::endl;
    {
        FileHandler file("test.txt", "w");
        if (file.isOpen()) {
            file.write("Hello from RAII!\n");
            file.write("This file will be auto-closed.\n");
        }
    }  // File automatically closed here!
    
    {
        FileHandler file("test.txt", "r");
        if (file.isOpen()) {
            std::cout << "File contents:\n" << file.read();
        }
    }
    
    return 0;
}
