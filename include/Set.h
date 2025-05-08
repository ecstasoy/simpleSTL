//
// Created by Kunhua Huang on 5/8/25.
//

#ifndef SIMPLESTL_SET_H
#define SIMPLESTL_SET_H

#include "RedBlackTree.h"

template <typename Key> class Set {
private:
    RedBlackTree<Key, Key> rbTree;

public:
    Set() : rbTree() {}

    void insert(const Key& key) {
        rbTree.insert(key, key);
    }

    void erase(const Key& key) {
        rbTree.remove(key);
    }

    size_t getSize() const {
        return rbTree.size();
    }

    bool empty() const {
        return rbTree.empty();
    }

    bool contains(const Key& key) const {
        return rbTree.at(key) != nullptr;
    }
};

#endif //SIMPLESTL_SET_H
