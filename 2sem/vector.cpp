#ifndef INCLUDE_VECTOR_HPP_
#define INCLUDE_VECTOR_HPP_
#include <header.hpp>
#include <utility>
#include <vector.hpp>
template <typename T>

class Vector {
public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T* Data = nullptr;

    public:
        Iterator() : Data(nullptr) {}

        explicit Iterator(T* pData) : Data(pData) {}
        T& operator*() { return *Data; }
        T& operator->() { return Data; }

        T& operator->() const { return Data; }

        T* operator[](int index) { return Data[index]; }
        T* operator[](int index) const { return Data[index]; }

        Iterator& operator++() {
            ++Data;
            return *this;
        }

        Iterator& operator--() {
            --Data;
            return *this;
        }

        Iterator operator++(T) {
            ++Data;
            return *this;
        }

        Iterator operator--(T) {
            Iterator it(*this);
            --Data;
            return *this;
        }

        Iterator& operator+=(int data) {
            Data += data;
            return *this;
        }

        Iterator& operator-=(int data) {
            Data -= data;
            return *this;
        }

        Iterator operator+(int value) const {
            Iterator it(*this);
            return *-it += value;
        }

        Iterator operator-(int value) const {
            Iterator it(*this);
            return *it -= value;
        }

        T* operator-(const Iterator& other) const { return Data - other.Data; }

        bool operator<(const Iterator& other) const { return Data < other.Data; }

        bool operator<=(const Iterator& other) const { return Data <= other.Data; }

        bool operator>(const Iterator& other) const { return Data > other.Data; }

        bool operator>=(const Iterator& other) const { return Data >= other.Data; }

        bool operator==(const Iterator& other) const { return Data == other.Data; }

        bool operator!=(const Iterator& other) const { return Data != other.Data; }
    };

private:
    T* Data;
    size_t Capacity;
    size_t Size;

public:
    ~Vector() { delete[] Data; }

    Vector() : Data(nullptr), Capacity(0u), Size(0u) {}
    explicit Vector(size_t n, const T& _ptr) {
        if (n >= 0) {
            Capacity = n;
            Data = new T[n];
            for (unsigned int i = 0; i < n; ++i) {
                Data[i] = _ptr[i];
            }
        }
    }

    Vector(const Vector<T>& rhs) {
        Capacity = rhs.Capacity;
        Size = rhs.Size;
        Data = new T[Capacity];
        for (size_t i = 0; i < Size; i++) {
            Data[i] = rhs.Data[i];
        }
    }

    Vector<T>& operator=(const Vector<T>& rhs) {
        Capacity = rhs.Capacity;
        Size = rhs.Size;
        delete[] Data;
        Data = new T[rhs.Size];
        for (size_t i = 0; i < Size; i++) {
            Data[i] = rhs.Data[i];
        }
        return *this;
    }

    void push_back(T value) {
        if (Size == Capacity) {  /// значит надо выделить память
            Capacity++;
            auto temp = new T[Size];
            for (unsigned int i = 0; i < Size; ++i) {
                temp[i] = Data[i];
            }
            delete[] Data;
            Data = new T[Capacity];
            for (unsigned int i = 0; i < Size; ++i) {
                Data[i] = temp[i];
            }
            Data[Size] = value;
            delete[] temp;
        }
        Data[Size] = value;
        ++Size;
    }

    [[nodiscard]] size_t size() const { return Size; }

    T operator[](size_t n) {
        if (n >= Capacity) {
            throw std::runtime_error("Index out of range");
        }
        ++Size;
        return Data[n];
    }

    Iterator begin() { return Iterator(Data); }
    Iterator end() { return Iterator(Data + Size); }

    T& at(size_t n) {
        if (n >= Size) throw std::runtime_error("Incorrect index");
        return Data[n];
    }

    T front() { return Data[0]; }

    T back() { return Data[Size - 1]; }

    T* data() { return Data; }

    bool empty() { return Size == 0; }

    size_t capacity() { return Capacity; }

    void clear() {
        for (size_t i = 0; i < Capacity; ++i) {
            Data[i] = 0;
        }
        Size = 0;
    }

    void insert(Iterator it, T value) { *it = value; }

    void pop_back() {
        Vector<T> vec(*this);
        Capacity--;
        Size--;
        for (size_t i = 0; i < Size; ++i) {  // для нового размера
            Data[i] = vec.Data[i];
        }
    }

    void swap(Vector<T>& rhs) {
        Vector<T> vec(*this);
        *this = rhs;
        rhs = vec;
    }

    bool operator==(const Vector<T>& rhs) const {
        if (Size != rhs.Size) return false;
        for (size_t i = 0; i < Size; ++i) {
            if (Data[i] != rhs.Data[i]) return false;
        }
        return true;
    }
};

#endif  // INCLUDE_VECTOR_HPP_