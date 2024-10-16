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
class List {
public:
    template <typename L>
    friend std::ostream& operator<<(std::ostream& os, const List<L>& list);

private:
    struct Node {
        T data;
        std::shared_ptr<Node> prev;
        std::shared_ptr<Node> next;

        Node(const T& data, std::shared_ptr<Node> prev = nullptr, std::shared_ptr<Node> next = nullptr)
                : data(data), prev(prev), next(next) {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    size_t size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() { clear(); }

    void clear() {
        while (head) {
            head = head->next;
        }
        tail = nullptr;
        size = 0;
    }

    void push_back(const T& data) {
        Node* new_node = new Node(data, nullptr, tail);
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
        Node* new_node = new Node(data, head, nullptr);
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
            tail->next = nullptr;
        } else {
            head = nullptr;
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


};

#endif //SIMPLESTL_LIST_H
