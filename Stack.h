#pragma once

#include <iostream>


template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* topPtr;

public:
    Stack();
    ~Stack();
    void push(const T& data);
    void pop();
    T& top() const;
    bool isEmpty() const;
    void showStos();

};




