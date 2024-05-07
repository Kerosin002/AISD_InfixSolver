#include "Stack.h"

template<typename T>
Stack<T>::Stack() : topPtr(nullptr) {}

template<typename T>
Stack<T>::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

template<typename T>
void Stack<T>::push(const T& data) {
    Node* newNode = new Node(data);
    if (isEmpty()) {
        topPtr = newNode;
    }
    else {
        newNode->next = topPtr;
        topPtr = newNode;
    }
}

template<typename T>
void Stack<T>::pop() {
    if (isEmpty()) {
        std::cerr << "Error: Stack is empty!\n";
        return;
    }
    Node* temp = topPtr;
    topPtr = topPtr->next;
    delete temp;
}

template<typename T>
T& Stack<T>::top() const {
    if (isEmpty()) {
        std::cerr << "Error: Stack is empty!\n";
        throw std::runtime_error("Stack is empty!");
    }
    return topPtr->data;
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return topPtr == nullptr;
}
template<typename T>
void Stack<T>::showStos() {
    if (!isEmpty()) {
        Node* temp = topPtr;
        while (temp != nullptr) {
            std::cout << temp->data<<" ";
            temp = temp->next;
        }
        
    }
}
