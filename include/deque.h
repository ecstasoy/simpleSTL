//
// Created by Kunhua Huang on 10/16/24.
//

#ifndef SIMPLESTL_DEQUE_H
#define SIMPLESTL_DEQUE_H

#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T>
class Deque {
private:
    std::shared_ptr<T[]> elements;
    size_t size;
    size_t capacity;
    size_t front_index;
    size_t back_index;

public:
    Deque() : elements(nullptr), size(0), capacity(0), front_index(0), back_index(0) {}

    ~Deque() {
        clear();
        delete[] elements;
    }

    void clear() {
        while (size > 0) {
            pop_front();
        }
    }

    void push_back(const T& data) {
        if (size == capacity) {
            resize();
        }
        elements[back_index] = data;
        back_index = (back_index + 1) % capacity;
        ++size;
    }

    void push_front(const T& data) {
        if (size == capacity) {
            resize();
        }
        front_index = (front_index - 1 + capacity) % capacity;
        elements[front_index] = data;
        ++size;
    }

    void pop_back() {
        if (size == 0) {
            std::ostringstream os;
            os << "Deque is empty!";
            throw std::out_of_range(os.str());
        }
        back_index = (back_index - 1 + capacity) % capacity;
        --size;
    }

    void pop_front() {
        if (size == 0) {
            std::ostringstream os;
            os << "Deque is empty!";
            throw std::out_of_range(os.str());
        }
        front_index = (front_index + 1) % capacity;
        --size;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            std::ostringstream os;
            os << "Index " << index << " is out of bounds!";
            throw std::out_of_range(os.str());
        }
        return elements[(front_index + index) % capacity];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            std::ostringstream os;
            os << "Index " << index << " is out of bounds!";
            throw std::out_of_range(os.str());
        }
        return elements[(front_index + index) % capacity];
    }

    [[nodiscard]] size_t get_size() const {
        return size;
    }

    void print_elements() {
        for (size_t i = 0; i < size; ++i) {
            std::cout << elements[(front_index + i) % capacity] << " ";
        }
        std::cout << std::endl;
    }

private:
    void resize() {
        size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        std::shared_ptr<T[]> new_elements(new T[new_capacity]);
        for (size_t i = 0; i < size; ++i) {
            new_elements[i] = elements[(front_index + i) % capacity];
        }
        elements = new_elements;
        capacity = new_capacity;
        front_index = 0;
        back_index = size;
    }

};

#endif //SIMPLESTL_DEQUE_H
