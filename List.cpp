#include "List.h"
#include <stdexcept>

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
void LinkedList<T>::push(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    newNode->next = head;
    head = newNode;
}

template<typename T>
void LinkedList<T>::pop() {
    if (!head) return;
    Node<T>* temp = head;
    head = head->next;
    delete temp;
}

template<typename T>
bool LinkedList<T>::empty() const {
    return head == nullptr;
}

template<typename T>
T& LinkedList<T>::top() {
    if (!head) throw std::out_of_range("Stack is empty");
    return head->data;
}