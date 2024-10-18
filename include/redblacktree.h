//
// Created by Kunhua Huang on 10/16/24.
//

#ifndef SIMPLESTL_REDBLACKTREE_H
#define SIMPLESTL_REDBLACKTREE_H

#include <iostream>
#include <sstream>
#include <string>

enum class Color { RED, BLACK };

template <typename Key, typename Value> class RedBlackTree {
    class Node {
    public:
        Key key;
        Value value;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Key& k, const Value& v, Color c, Node* l, Node* r, Node* p)
            : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(p) {}

        Node() : color(Color:BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
    };

private:
    Node* root;
    size_t size;

    Node* lookUp(const Key& key) {
        Node* cmpNode = root;

        while (cmpNode) {
            if (key == cmpNode->key) {
                return cmpNode;
            } else if (key < cmpNode->key) {
                cmpNode = cmpNode->left;
            } else {
                cmpNode = cmpNode->right;
            }
        }

        return cmpNode;
    }

    void rightRotate(Node* node) {
        Node* l_child = node->left;
        node->left = l_child->right;
        if (l_child->right) {
            l_child->right->parent = node;
        }

        l_child->parent = node->parent;
        if (!node->parent) {
            root = l_child;
        } else if (node == node->parent->right) {
            node->parent->right = l_child;
        } else {
            node->parent->left = l_child;
        }

        l_child->right = node;
        node->parent = l_child;
    }

    void leftRotate(Node* node) {
        Node* r_child = node->right;
        node->right = r_child->left;
        if (r_child->left) {
            r_child->left->parent = node;
        }

        r_child->parent = node->parent;
        if (!node->parent) {
            root = r_child;
        } else if (node == node->parent->left) {
            node->parent->left = r_child;
        } else {
            node->parent->right = r_child;
        }

        r_child->left = node;
        node->parent = r_child;
    }

    void fixInsert(Node* target) {
        while (target->parent && target->parent->color == Color::RED) {
            if (target->parent == target->parent->parent->left) {
                Node* uncle = target->parent->parent->right;
                if (uncle && uncle->color = Color::RED) {
                    target->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    target = target->parent->parent;
                } else {
                    if (target == target->parent->right) {
                        target = target->parent;
                        leftRotate(target);
                    }
                    target->parent->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    rightRotate(target->parent->parent);
                }
            } else {
                Node* uncle = target->parent->parent->left;
                if (uncle && uncle->color = Color::RED) {
                    target->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    target = target->parent->parent;
                } else {
                    if (target == target->parent->left) {
                        target = target->parent;
                        rightRotate(target);
                    }
                    target->parent->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    leftRotate(target->parent->parent);
                }
            }
        }

        root->color = Color::BLACK;
    }

    void insertNode(const Key& key, const Value& value) {
        Node* newNode = new Node(key, value, Color::RED);
        Node* parent = nullptr;
        Node* cmpNode = root;

        while (cmpNode) {
            parent = cmpNode;
            if (newNode->key < cmpNode->key) {
                cmpNode = cmpNode->left;
            } else if (newNode->key > cmpNode->key) {
                cmpNode = cmpNode->right;
            } else {
                delete newNode;
                return;
            }
        }

        size++;
        newNode->parent = parent;

        if (!parent) {
            root = newNode;
        } else if (newNode->key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        fixInsert(newNode);
    }

    void inorderTraversal(Node *node) const {
        if (node) {
            inorderTraversal(node->left);
            std::cout << "{" << node->key << " : ";
            std::cout << node->value << "} ";
            inorderTraversal(node->right);
        }
    }

    void preorderTraversal(Node *node) const {
        if (node) {
            std::cout << "{" << node->key << " : ";
            std::cout << node->value << "} ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    void postorderTraversal(Node *node) const {
        if (node) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << "{" << node->key << " : ";
            std::cout << node->value << "} ";
        }
    }

    void replaceNode(Node* target, Node* newNode) {
        if (!target->parent) {
            root = newNode;
        } else if (target == target->parent->left) {
            target->parent->left = newNode;
        } else {
            target->parent->right = newNode;
        }

        if (newNode) {
            newNode->parent = target->parent;
        }
    }
};

#endif //SIMPLESTL_REDBLACKTREE_H
