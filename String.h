#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class String {
private:
    char* str;
    int capacity; // New member variable to store the capacity of the string

public:
    // Constructors and Destructor
    String(const char* s = "");
    String(const String& source);
    ~String();

    // Member functions
    int length() const;
    int getCapacity() const;
    

    String& operator=(const String& source);
    String operator+(const String& source) const;
    String& operator+=(const String& source);

    // Indexing
    char& operator[](int index);
    const char& operator[](int index) const;

    // Utility functions
    const char* c_str() const;
    void appendChar(char c);
    bool isNum() const;
    void reverse();

    // Friend functions
    friend bool operator==(const String& lhs, const String& rhs);
    friend bool operator!=(const String& lhs, const String& rhs);
    friend std::ostream& operator<<(std::ostream& os, const String& s);
};
