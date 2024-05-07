#include "String.h"

String::String(const char* s) {
    if (s == nullptr) {
        capacity = 100;
        str = new char[capacity];
        *str = '\0';
    }
    else {
        int len = strlen(s);
        if (len >= 1)
            capacity = 20 * len;
        else
            capacity = 100;
        str = new char[capacity];
        strcpy(str, s);
    }
}

String::String(const String& source) {
    capacity = source.capacity;
    str = new char[capacity];
    strcpy(str, source.str);
}

String::~String() {
    delete[] str;
}

int String::length() const {
    return strlen(str);
}

int String::getCapacity()const {
    return capacity;
}



String& String::operator=(const String& source) {
    if (this == &source)
        return *this;

    // Reallocate memory only if necessary
    if (capacity <= source.capacity) {
        delete[] str;
        capacity = source.capacity;
        str = new char[capacity];
    }
    strcpy(str, source.str);
    return *this;
}

String String::operator+(const String& source) const {
    // Allocate memory only once for the new concatenated string
    int newCapacity = length() + source.length() + 1;
    char* temp = new char[newCapacity];
    strcpy(temp, str);
    strcat(temp, source.str);
    String result(temp);
    delete[] temp;
    return result;
}


String& String::operator+=(const String& source) {
    // Allocate memory for the concatenated string
    if (capacity <= length() + source.length()) {
        capacity = capacity + source.getCapacity();
        char* temp = new char[capacity];
        strcpy(temp, str);
        strcat(temp, source.str);

        // Deallocate old memory and assign the new concatenated string
        delete[] str;
        str = temp;
    }
    else
        strcat(str, source.str);
    

    return *this;
}

char& String::operator[](int index) {
    return str[index];
}

const char& String::operator[](int index) const {
    return str[index];
}

const char* String::c_str() const {
    return str;
}

void String::appendChar(char c) {
    int len = length();
    if (len + 1 >= capacity) {
        capacity *= 5; 
        char* temp = new char[capacity];
        strcpy(temp, str);
        delete[] str;
        str = temp;
    }
    str[len] = c;
    str[len + 1] = '\0';
}



bool String::isNum() const {
    int len = length();
    for (int i = 0; i < len; i++) {
        if (str[i] > '9' || str[i] < '0')
            return false;
    }
    return true;
}


void String::reverse() {
    int len = length();
    for (int i = 0; i < len / 2; ++i) {
        // Swap characters from the beginning and end of the string
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

bool operator==(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.str;
    return os;
}