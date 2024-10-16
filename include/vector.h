//
// Created by Kunhua Huang on 10/15/24.
//
#ifndef SIMPLESTL_VECTOR_H
#define SIMPLESTL_VECTOR_H

#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <memory>

template <typename T>
class Vector {
private:
    std::shared_ptr<T[]> elements;
    size_t vectorSize;
    size_t capacity;

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }
        std::shared_ptr<T[]> new_elements(new T[new_capacity]);
        std::copy(elements.get(), elements.get() + vectorSize, new_elements.get());
        elements = new_elements;
        capacity = new_capacity;
    }

public:
    Vector() : elements(new T[1]), vectorSize(0), capacity(1) {}

    ~Vector() = default;

    Vector(const Vector& other) : vectorSize(other.vectorSize), capacity(other.capacity) {
        elements = std::shared_ptr<T[]>(new T[capacity]);
        std::copy(other.elements.get(), other.elements.get() + vectorSize, elements.get());
    }

    Vector& operator=(const Vector& other) {
        if (this != other) {
            vectorSize = other.vectorSize;
            capacity = other.capacity;
            elements = std::shared_ptr<T[]>(new T[capacity]);
            std::copy(other.elements.get(), other.elements.get() + vectorSize, elements.get());
        }
        return *this;
    }

    T& operator[](size_t index) {
        if (index >= vectorSize) {
            std::ostringstream os;
            os << "Index " << index << " is out of bounds!";
            throw std::out_of_range(os.str());
        }
        return elements[index];
    }

    const T& operator[](size_t index) const {
        if (index >= vectorSize) {
            std::ostringstream os;
            os << "Index " << index << " is out of bounds!";
            throw std::out_of_range(os.str());
        }
        return elements[index];
    }

    [[nodiscard]] size_t get_size() const {
        return vectorSize;
    }

    size_t size() {
        return vectorSize;
    }

    [[nodiscard]] size_t get_capacity() const {
        return capacity;
    }

    void push_back(const T& value) {
        if (vectorSize == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        elements[vectorSize++] = value;
    }

    void pop_back() {
        if (vectorSize == 0) {
            throw std::out_of_range("Cannot pop from an empty vector!");
        }
        vectorSize--;
    }

    void insert(size_t index, const T& value) {
        if (index > vectorSize) {
            std::ostringstream os;
            os << "Index " << index << " is out of bounds!";
            throw std::out_of_range(os.str());
        }
        if (vectorSize == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        std::copy_backward(elements.get() + index, elements.get() + vectorSize, elements.get() + vectorSize + 1);
        elements[index] = value;
        vectorSize++;
    }

    [[nodiscard]] bool empty() const {
        return vectorSize == 0;
    }

    void clear() {
        vectorSize = 0;
    }

    void printElements() const {
        for (size_t i = 0; i < vectorSize; ++i) {
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
        return elements.get() + vectorSize;
    }

    const T* begin() const {
        return elements.get();
    }

    const T* end() const {
        return elements.get() + vectorSize;
    }

};

#endif //SIMPLESTL_VECTOR_H
