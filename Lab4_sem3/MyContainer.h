#ifndef MY_CONTAINER_H
#define MY_CONTAINER_H

#include <iostream>
#include <memory>
#include <utility> // Для std::move

template <typename T>
class CustomAllocator {
public:
    using value_type = T;

    CustomAllocator() = default;

    template <typename U>
    CustomAllocator(const CustomAllocator<U>&) {}

    T* allocate(std::size_t n) {
        if (n > std::size_t(-1) / sizeof(T)) {
            throw std::bad_alloc();
        }
        if (auto p = static_cast<T*>(::operator new(n * sizeof(T)))) {
            return p;
        }
        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t) {
        ::operator delete(p);
    }
};

template<typename T, typename Allocator = CustomAllocator<T>>
class MyContainer {
public:
    using allocator_type = Allocator;
    using iterator = T*;

    MyContainer(allocator_type alloc = allocator_type())
        : alloc(alloc), size(0), capacity(10) {
        data = alloc.allocate(capacity);
    }

    ~MyContainer() {
        clear();
        alloc.deallocate(data, capacity);
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            resize(capacity * 2);
        }
        new(&data[size]) T(value);
        size++;
    }

    void clear() {
        for (size_t i = 0; i < size; ++i) {
            data[i].~T();
        }
        size = 0;
    }

    size_t getSize() const { return size; }
    bool empty() const { return size == 0; }
    iterator begin() { return data; }
    iterator end() { return data + size; }

private:
    void resize(size_t new_capacity) {
        T* new_data = alloc.allocate(new_capacity);
        for (size_t i = 0; i < size; ++i) {
            new(new_data + i) T(std::move(data[i]));
            data[i].~T();
        }
        alloc.deallocate(data, capacity);
        data = new_data;
        capacity = new_capacity;
    }

    Allocator alloc;
    T* data;
    size_t size;
    size_t capacity;
};

#endif // MY_CONTAINER_H
