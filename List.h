
#pragma once


template<typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& data) : data(data), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    Node<T>* head;
public:
    LinkedList();
    ~LinkedList();
    void push(const T& data);
    void pop();
    bool empty() const;
    T& top();
};


#include "List.cpp"

