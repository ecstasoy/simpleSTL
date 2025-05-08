//
// Created by Kunhua Huang on 10/16/24.
//

#ifndef SIMPLESTL_HASHTABLE_H
#define SIMPLESTL_HASHTABLE_H

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include "list.h"
#include "vector.h"
#include <utility>
#include <sstream>
#include <string>
#include <memory>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {

    class HashNode {
    public:
        Key key;
        Value value;

        explicit HashNode(const Key &key) : key(key), value() {}

        explicit HashNode(const Key& key, const Value& value) : key(key), value(value) {}

        bool operator==(const HashNode& other) const { return key == other.key; }
        bool operator!=(const HashNode& other) const { return key != other.key; }
        bool operator>(const HashNode& other) const { return key > other.key; }
        bool operator<(const HashNode& other) const { return key < other.key; }
        bool operator==(const Key& other) const { return key == other; }

        void print() const {
            std::cout << "{" << key << ": " << value << "}" << std::endl;
        }
    };

private:
    using Bucket = List<HashNode>;
    Vector<Bucket> buckets;
    Hash hashFunction;
    size_t numElements;
    size_t tableSize;

    float maxLoadFactor = 0.75;

    size_t hash(const Key& key) const {
        return hashFunction(key) % tableSize;
    }

    void rehash(size_t newTableSize) {
        Vector<Bucket> newBuckets(newTableSize);

        for (Bucket& bucket : buckets) {
            for (const HashNode& node : bucket) {
                size_t index = hashFunction(node.key) % newTableSize;
                newBuckets[index].push_back(node);
            }
        }

        buckets = std::move(newBuckets);
        tableSize = newTableSize;
    }
public:
    HashTable(size_t size = 10, const Hash& hashFunc = Hash())
    : buckets(size), hashFunction(hashFunc), numElements(0), tableSize(size) {}

    void insert(const Key& key, const Value& value) {
        if ((numElements + 1) > maxLoadFactor * tableSize) {
            if (tableSize == 0) {
                rehash(1);
            } else {
                rehash(tableSize * 2);
            }
        }

        size_t index = hash(key);
        List<HashNode>& bucket = buckets[index];

        auto node = bucket.find(HashNode(key));

        if (node) {
            node->data.value = value;
        } else {
            bucket.push_back(HashNode(key, value));
            ++numElements;
        }
    }

    void erase(const Key& key) {
        size_t index = hash(key);
        auto& bucket = buckets[index];
        auto node = bucket.find(HashNode(key));
        if (node) {
            bucket.remove(*node);
            --numElements;
        }
    }

    Value* find(const Key& key) const {
        size_t index = hash(key);
        auto& bucket = buckets[index];
        auto node = bucket.find(HashNode(key));
        if (node) {
            return &node->data.value;
        }
        return nullptr;
    }

    size_t size() const {
        return numElements;
    }

    void print() const {
        for (size_t i = 0; i < buckets.size(); ++i) {
            for (const HashNode& element : buckets[i]) {
                element.print();
            }
        }
        std::cout << std::endl;
    }
};
#endif //SIMPLESTL_HASHTABLE_H
