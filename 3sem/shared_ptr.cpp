
#ifndef INCLUDE_SHARED_HPP_
#define INCLUDE_SHARED_HPP_

#include <header.hpp>
#include <utility>

template <typename T>
class SharedPtr {
private:
    T* ptr;
    std::atomic_uint* count;

public:
    SharedPtr() : ptr(nullptr), count(nullptr) {}
    explicit SharedPtr(T* ptr_raw) : ptr(ptr_raw) {
        count = new std::atomic_uint(1);
    }
    SharedPtr(const SharedPtr& r) : ptr(r.ptr), count(r.count) { (*count)++; }
    SharedPtr(SharedPtr&& r) noexcept {
        ptr = std::move(r.ptr);
        count = std::move(r.count);
        (*count)++;
    }
    ~SharedPtr() {
        if (count) {
            if (*count == 1) {
                delete count;
                delete ptr;
            } else {
                --(*count);
            }
        }
    }
    auto operator=(const SharedPtr& r) -> SharedPtr& {
        if (this != &r) {
            if (count) {
                if (*count == 1) {
                    delete count;
                    delete ptr;
                } else {
                    --(*count);
                }
            }
            ptr = r.ptr;
            count = r.count;
            ++(*count);
        }
        return *this;
    }
    auto operator=(SharedPtr&& r) -> SharedPtr& {
        if (this != &r) {
            if (count) {
                if (*count == 1) {
                    delete count;
                    delete ptr;
                } else {
                    --(*count);
                }
            }
            ptr = r.ptr;
            count = r.count;
            ++(*count);
        }
        return *this;
    }

    // проверяет, указывает ли указатель на объект
    operator bool() const { return (ptr != nullptr); }
    auto operator*() const -> T& { return *ptr; }
    auto operator->() const -> T* { return ptr; }
    auto get() -> T* { return ptr; }

    void reset() {
        --*count;
        if (*count == 0) {
            delete ptr;
            delete count;
        }
        ptr = nullptr;
        count = nullptr;
    }

    void reset(T* ptr_raw) {
        if (ptr != ptr_raw) {
            --(*count);
            if (*count == 0) {
                delete ptr;
                delete count;
            }
            ptr = ptr_raw;
            count = new std::atomic_uint(1);
        }
    }

    void swap(SharedPtr& r) {
        std::swap(ptr, r.ptr);
        std::swap(count, r.count);
    }
    //  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
    //  управляемый объект
    auto use_count() const -> size_t { return *count; }
};

#endif  // INCLUDE_SHARED_HPP_