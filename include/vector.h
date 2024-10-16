//
// Created by Kunhua Huang on 10/15/24.
//
#ifndef SIMPLESTL_LIST_H
#define SIMPLESTL_LIST_H

#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <memory>

template <typename T>
class Vector {
private:
    std::shared_ptr<T[]> elements;
    size_t size;
    size_t capacity;

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }
        std::shared_ptr<T[]> new_elements(new T[new_capacity]);
        std::copy(elements.get(), elements.get() + size, new_elements.get());
        elements = new_elements;
        capacity = new_capacity;
    }

public:
    Vector() : elements(new T[1]), size(0), capacity(0) {}

    ~Vector() = default;

    Vector(const Vector& other) : size(other.size), capacity(other.capacity) {
        elements = std::shared_ptr<T[]>(new T[capacity]);
        std::copy(other.elements.get(), other.elements.get() + size, elements.get());
    }

    Vector& operator=(const Vector& other) {
        if (this != other) {
            delete[] elements;
            size = other.size;
            capacity = other.capacity;
            elements = std::shared_ptr<T[]>(new T[capacity]);
            std::copy(other.elements.get(), other.elements.get() + size, elements.get());
        }
        return *this;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            std::ostringstream os;
            os << "Index " << index << " is out of bounds!";
            throw std::out_of_range(os.str());
        }
        return elements[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            std::ostringstream os;
            os << "Index " << index << " is out of bounds!";
            throw std::out_of_range(os.str());
        }
        return elements[index];
    }

    [[nodiscard]] size_t get_size() const {
        return size;
    }

    [[nodiscard]] size_t get_capacity() const {
        return capacity;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        elements[size++] = value;
    }

    void pop_back() {
        if (size == 0) {
            throw std::out_of_range("Cannot pop from an empty vector!");
        }
        size--;
    }

    void insert(size_t index, const T& value) {
        if (index > size) {
            std::ostringstream os;
            os << "Index " << index << " is out of bounds!";
            throw std::out_of_range(os.str());
        }
        if (size == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        std::copy_backward(elements.get() + index, elements.get() + size, elements.get() + size + 1);
        elements[index] = value;
        size++;
    }

    [[nodiscard]] bool empty() const {
        return size == 0;
    }

    void clear() {
        size = 0;
    }

    void printElements() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }

    /*
     * Iterator support
     */
    T* begin() {
        return elements.get();
    }

    T* end() {
        return elements.get() + size;
    }

    const T* begin() const {
        return elements.get();
    }

    const T* end() const {
        return elements.get() + size;
    }

};

#endif //SIMPLESTL_LIST_H
