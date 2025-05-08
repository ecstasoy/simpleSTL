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
    static const size_t CHUNK_SIZE = 4; // Size of each secondary array
    std::unique_ptr<std::unique_ptr<T[]>[]> elements; // Primary array of pointers to secondary arrays
    size_t size;
    size_t capacity;
    size_t front_index;
    size_t back_index;

public:
    Deque() : elements(new std::unique_ptr<T[]>[1]), size(0), capacity(CHUNK_SIZE), front_index(0), back_index(0) {
        elements[0] = std::unique_ptr<T[]>(new T[CHUNK_SIZE]);
    }

    ~Deque() {
        clear();
    }

    void clear() {
        elements.reset();
        size = 0;
        capacity = 0;
        front_index = 0;
        back_index = 0;
    }

    void push_back(const T& data) {
        if (size == capacity) {
            resize();
        }
        elements[back_index / CHUNK_SIZE][back_index % CHUNK_SIZE] = data;
        back_index = (back_index + 1) % capacity;
        ++size;
    }

    void push_front(const T& data) {
        if (size == capacity) {
            resize();
        }
        front_index = (front_index - 1 + capacity) % capacity;
        elements[front_index / CHUNK_SIZE][front_index % CHUNK_SIZE] = data;
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
        return elements[(front_index + index) / CHUNK_SIZE][(front_index + index) % CHUNK_SIZE];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            std::ostringstream os;
            os << "Index " << index << " is out of bounds!";
            throw std::out_of_range(os.str());
        }
        return elements[(front_index + index) / CHUNK_SIZE][(front_index + index) % CHUNK_SIZE];
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
        size_t new_capacity = capacity + CHUNK_SIZE;
        std::unique_ptr<std::unique_ptr<T[]>[]> new_elements(new std::unique_ptr<T[]>[new_capacity / CHUNK_SIZE]);
        for (size_t i = 0; i < new_capacity / CHUNK_SIZE; ++i) {
            new_elements[i] = std::unique_ptr<T[]>(new T[CHUNK_SIZE]);
        }
        for (size_t i = 0; i < size; ++i) {
            size_t actual_index = (front_index + i) % capacity;
            new_elements[i / CHUNK_SIZE][i % CHUNK_SIZE] = elements[actual_index / CHUNK_SIZE][actual_index % CHUNK_SIZE];
        }
        elements = std::move(new_elements);
        capacity = new_capacity;
        front_index = 0;
        back_index = size;
    }

};

#endif //SIMPLESTL_DEQUE_H
