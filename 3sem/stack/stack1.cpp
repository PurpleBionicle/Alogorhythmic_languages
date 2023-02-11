
#ifndef INCLUDE_STACK1_HPP_
#define INCLUDE_STACK1_HPP_
#include <header.hpp>
#include <utility>

template <typename T>
class Stack1 {
private:
    T* ptr;
    size_t size;

public:
    Stack1();

    ~Stack1();

    void push(T&& next_value);

    void push(const T& next_value);

    void pop();

    const T& head() const;
};
template <typename T>
Stack1<T>::Stack1() : ptr(nullptr), size(0) {}
template <typename T>
Stack1<T>::~Stack1() {
    delete[] ptr;
}

template <typename T>
void Stack1<T>::push(T&& next_value) {
    T* buf;
    if (size) {
        buf = new T[size];
        for (size_t i = 0; i < size; ++i) {
            buf[i] = ptr[i];
        }
        delete[] ptr;
    }
    ptr = new T[++size];
    for (size_t i = 0; i < size - 1; ++i) {
        ptr[i] = buf[i];
    }
    if (size) delete[] buf;
    ptr[size - 1] = std::move(next_value);
}

template <typename T>
void Stack1<T>::push(const T& next_value) {
    T* buf;
    if (size) {
        buf = new T[size];
        for (size_t i = 0; i < size; ++i) {
            buf[i] = ptr[i];
        }
    }
    if (size) delete[] ptr;
    ptr = new T[++size];
    for (size_t i = 0; i < size - 1; ++i) {
        ptr[i] = buf[i];
    }
    if (size > 1) delete[] buf;
    ptr[size - 1] = next_value;
}

template <typename T>
void Stack1<T>::pop() {
    if (!size) throw std::logic_error("stack is empty");

    if (size != 1) {
        T* buf = new T[--size];
        for (size_t i = 0; i < size; ++i) {
            buf[i] = ptr[i];
        }
        delete[] ptr;
        ptr = new T[size];
        for (size_t i = 0; i < size; ++i) {
            ptr[i] = buf[i];
        }
        if (size) delete[] buf;
    } else {
        --size;
    }
}

template <typename T>
const T& Stack1<T>::head() const {
    if (!size) throw std::logic_error("Stack is empty");
    return ptr[size - 1];
}

#endif  // INCLUDE_STACK1_HPP_