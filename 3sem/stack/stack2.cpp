// Copyright 2021 Nikita Pushkin

#ifndef INCLUDE_STACK2_HPP_
#define INCLUDE_STACK2_HPP_
#include <utility>

#include "header.hpp"
template <typename T>
class Stack2 {
private:
    T* ptr;
    size_t size;

public:
    Stack2();

    ~Stack2();

    template <typename... Args>
    void push_emplace(Args&&... value);

    void push(T&& value);

    const T& head() const;

    T pop();
};

template <typename T>
Stack2<T>::Stack2() : ptr(nullptr), size(0) {}

template <typename T>
Stack2<T>::~Stack2() {
    delete[] ptr;
}

// template <typename T>
// template <typename... Args>
// void Stack2<T>::push_emplace(Args&&... value) {
//
//   Stack2.push(std::forward<Args>(value)...);
// }

template <typename T>
void Stack2<T>::push(T&& value) {
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
    if (size > 1) delete[] buf;
    ptr[size - 1] = std::move(value);
}

template <typename T>
const T& Stack2<T>::head() const {
    if (!size) throw std::logic_error("stack is empty");
    return ptr[size - 1];
}
template <typename T>
T Stack2<T>::pop() {
    if (!size) throw std::logic_error("stack is empty");
    if (!--size) {
        return *ptr;
    }
    T result = ptr[size];
    T* buf;
    if (size) {
        buf = new T[size];
        for (size_t i = 0; i < size; ++i) {
            buf[i] = ptr[i];
        }
        delete[] ptr;
    }
    ptr = new T[size];
    for (size_t i = 0; i < size; ++i) {
        ptr[i] = buf[i];
    }
    if (size != 0) delete[] buf;
    return result;
}

template <typename T>
template <typename... Args>
void Stack2<T>::push_emplace(Args&&... value) {
    T object(value...);
    T* buf;
    if (size) {
        buf = new T[size];
        for (size_t i = 0; i < size; ++i) {
            buf[i] = std::forward<T>(ptr[i]);
        }
    }
    delete[] ptr;
    ptr = new T[++size];
    for (size_t i = 0; i < size - 1; ++i) {
        ptr[i] = std::forward<T>(buf[i]);
    }

    ptr[size - 1] = std::forward<T>(object);
}

#endif  // INCLUDE_STACK2_HPP_