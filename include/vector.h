//
// Created by Kunhua Huang on 10/15/24.
//
#pragma once
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* elements;
    size_t size;
    size_t capacity;

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }
        T* new_elements = new T[new_capacity];
        std::copy(elements, elements + size, new_elements);
        delete[] elements;
        elements = new_elements;
        capacity = new_capacity;
    }

public:
    Vector() : elements(nullptr), size(0), capacity(0) {}

    ~Vector() {
        delete[] elements;
    }

    Vector(const Vector& other) : size(other.size), capacity(other.capacity) {
        elements = new T[capacity];
        std::copy(other.elements, other.elements + size, elements);
    }

    Vector& operator=(const Vector& other) {
        if (this != other) {
            delete[] elements;
            size = other.size;
            capacity = other.capacity;
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
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

    size_t get_size() const {
        return size;
    }

    size_t get_capacity() const {
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
        std::copy_backward(elements + index, elements + size, elements + size + 1);
        elements[index] = value;
        size++;
    }

    bool empty() const {
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
        return elements;
    }

    T* end() {
        return elements + size;
    }

    const T* begin() const {
        return elements;
    }

    const T* end() const {
        return elements + size;
    }

};