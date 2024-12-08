#ifndef CUSTOM_ALLOCATOR_H
#define CUSTOM_ALLOCATOR_H

#include <cstdlib>
#include <memory>
#include <limits>

template<typename T>
class CustomAllocator {
public:
    using value_type = T;

    CustomAllocator(size_t initial_size = 10) : size(initial_size), allocated(0), buffer(nullptr) {
        buffer = static_cast<T*>(::operator new(size * sizeof(T)));
    }

    ~CustomAllocator() {
        deallocate_all();
    }

    T* allocate(std::size_t n) {
        if (n > size - allocated) {
            resize((size + n) * 2);
        }
        T* result = buffer + allocated;
        allocated += n;
        return result;
    }

    void deallocate(T* ptr, std::size_t n) {
        // Можно реализовать поэлементное освобождение
        // Для простоты не реализуем здесь
    }

    void deallocate_all() {
        ::operator delete(buffer);
        buffer = nullptr;
        allocated = 0;
        size = 0;
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p) {
        p->~U();
    }

private:
    void resize(size_t new_size) {
        T* new_buffer = static_cast<T*>(::operator new(new_size * sizeof(T)));
        for (size_t i = 0; i < allocated; ++i) {
            new (&new_buffer[i]) T(std::move(buffer[i]));
            buffer[i].~T(); // Вызов деструктора для старых объектов
        }
        ::operator delete(buffer);
        buffer = new_buffer;
        size = new_size;
    }

    size_t size;
    size_t allocated;
    T* buffer;
};

#endif // CUSTOM_ALLOCATOR_H
