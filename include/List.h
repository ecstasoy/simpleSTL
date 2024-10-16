//
// Created by Kunhua Huang on 10/15/24.
//

#ifndef SIMPLESTL_LIST_H
#define SIMPLESTL_LIST_H

#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T>
class list {
public:
    template <typename L>
    friend std::ostream& operator<<(std::ostream& os, const list<L>& list);

private:
    struct Node {
        T data;
        std::shared_ptr<Node> prev;
        std::shared_ptr<Node> next;

        explicit Node(const T& data, std::shared_ptr<Node> prev = nullptr, std::shared_ptr<Node> next = nullptr)
                : data(data), prev(prev), next(next) {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    size_t size;

public:
    list() : head(nullptr), tail(nullptr), size(0) {}

    ~list() { clear(); }

    void clear() {
        while (head) {
            head = head->next;
        }
        head.reset();
        tail.reset();
        size = 0;
    }

    void push_back(const T& data) {
        auto new_node = std::make_shared<Node>(data, nullptr, tail);
        if (tail) {
            tail->next = new_node;
        }
        tail = new_node;
        if (!head) {
            head = new_node;
        }
        ++size;
    }

    void push_front(const T& data) {
        auto new_node = std::make_shared<Node>(data, head, nullptr);
        if (head) {
            head->prev = new_node;
        }
        head = new_node;
        if (!tail) {
            tail = new_node;
        }
        ++size;
    }

    void pop_back() {
        Node* new_tail = tail->prev;
        tail.reset();
        tail = new_tail;
        if (tail) {
            tail->next.reset();
        } else {
            head.reset();
        }
        --size;
    }

    void pop_front() {
        Node* new_head = head->next;
        head.reset();
        head = new_head;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        --size;
    }

    [[nodiscard]] size_t get_size() const {
        return size;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            std::ostringstream os;
            os << "Index " << index << " is out of bounds!";
            throw std::out_of_range(os.str());
        }
        Node* current = head.get();
        for (size_t i = 0; i < index; ++i) {
            current = current->next.get();
        }
        return current->data;
    }

    /*
     * Iterator support
     */
    Node* begin() {
        return head.get();
    }

    Node* end() {
        return nullptr;
    }

    const Node* begin() const {
        return head.get();
    }

    const Node* end() const {
        return nullptr;
    }

    void printElements() const {
        Node* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }
};

/*
 * Overloaded operator << for List
 */
template <typename T>
std::ostream &operator<<(std::ostream &os, const list<T> &pt)
{
    for (typename list<T>::Node *current = pt.head; current;
         current = current->next)
    {
        os << " " << current->data;
    }
    os << std::endl;
    return os;
}

#endif //SIMPLESTL_LIST_H
