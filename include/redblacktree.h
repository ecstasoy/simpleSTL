//
// Created by Kunhua Huang on 10/16/24.
//

#ifndef SIMPLESTL_REDBLACKTREE_H
#define SIMPLESTL_REDBLACKTREE_H

#include <iostream>
#include <sstream>
#include <string>

enum class Color {
    RED, BLACK
};

template<typename Key, typename Value>
class RedBlackTree {
    class Node {
    public:
        Key key;
        Value value;
        Color color;
        Node *left;
        Node *right;
        Node *parent;

        Node(const Key &k, const Value &v, Color c, Node *l, Node *r, Node *p)
                : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(p) {}

        Node() : color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
    };

private:
    Node *root;
    size_t size;
    Node *Nil;

    Node *lookUp(const Key &key) {
        Node *cmpNode = root;

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

    void rightRotate(Node *node) {
        Node *l_child = node->left;
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

    void leftRotate(Node *node) {
        Node *r_child = node->right;
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

    void fixInsert(Node *target) {
        while (target->parent && target->parent->color == Color::RED) {
            if (target->parent == target->parent->parent->left) {
                Node *uncle = target->parent->parent->right;
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
                Node *uncle = target->parent->parent->left;
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

    void insertNode(const Key &key, const Value &value) {
        Node *newNode = new Node(key, value, Color::RED);
        Node *parent = nullptr;
        Node *cmpNode = root;

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

    void replaceNode(Node *target, Node *newNode) {
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

    Node *findMinimumNode(Node *node) {
        while (node->left) {
            node = node->left;
        }

        return node;
    }

    void removeFix(Node *node) {
        if (node->parent == nullptr && node == Nil) {
            return;
        }

        while (node != root) {
            if (node == node->parent->left) {
                Node *sibling = node->parent->right;

                if (getColor(sibling) == Color::RED) {
                    setColor(sibling, Color::BLACK);
                    setColor(node->parent, Color::RED);
                    leftRotate(node->parent);

                    sibling = node->parent->right;
                }

                if (getColor(sibling->left) == Color::BLACK && getColor(sibling->right) == Color::BLACK) {
                    setColor(sibling, Color::RED);
                    node == node->parent;

                    if (node->color == Color::RED) {
                        node->color = Color::BLACK;
                        node = root;
                    }
                } else {
                    if (getColor(sibling->right) == Color::BLACK) {
                        setColor(sibling->left, Color::BLACK);
                        setColor(sibling, Color::RED);
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }

                    setColor(sibling, node->parent->color);
                    setColor(node->parent, Color::BLACK);
                    setColor(sibling->right, Color::BLACK);
                    leftRotate(node->parent);
                    node = root;
                }
            } else {
                Node *sibling = node->parent->left;

                if (getColor(sibling) == Color::RED) {
                    setColor(sibling, Color::BLACK);
                    setColor(node->parent, Color::RED);
                    rightRotate(node->parent);

                    sibling = node->parent->left;
                }

                if (getColor(sibling->right) == Color::BLACK && getColor(sibling->left) == Color::BLACK) {
                    setColor(sibling, Color::RED);
                    node = node->parent;

                    if (node->color == Color::RED) {
                        node->color = Color::BLACK;
                        node = root;
                    }
                } else {
                    if (getColor(sibling->left) == Color::BLACK) {
                        setColor(sibling->right, Color::BLACK);
                        setColor(sibling, Color::RED);
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }

                    setColor(sibling, node->parent->color);
                    setColor(node->parent, Color::BLACK);
                    setColor(sibling->left, Color::BLACK);
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        setColor(node, Color::BLACK);
    }

    Color getColor(Node *node) {
        return node ? node->color : Color::BLACK;
    }

    void setColor(Node *node, Color color) {
        if (node) {
            node->color = color;
        }
    }

    void disconnectNil() {
        if (Nil == nullptr) {
            return;
        }
        if (Nil->parent != nullptr) {
            if (Nil == Nil->parent->left) {
                Nil->parent->left = nullptr;
            } else {
                Nil->parent->right = nullptr;
            }
        }
    }

    void deleteNode(Node *del) {
        Node *rep = del;
        Node *child = nullptr;
        Node *parentRP;
        Color origColor = rep->color;

        if (!del->left) {
            rep = del->right;
            parentRP = del->parent;
            origColor = getColor(rep);
            replaceNode(del, rep);
        } else if (!del->right) {
            rep = del->left;
            parentRP = del->parent;
            origColor = getColor(rep);
            replaceNode(del, rep);
        } else {
            rep = findMinimumNode(del->right);
            origColor = rep->color;
            if (rep != del->right) {
                parentRP = rep->parent;
                child = rep->right;
                parentRP->left = child;

                if (child) {
                    child->parent = parentRP;
                }

                del->left->parent = rep;
                del->right->parent = rep;
                rep->left = del->left;
                rep->right = del->right;

                if (del->parent) {
                    if (del == del->parent->left) {
                        del->parent->left = rep;
                        rep->parent = del->parent;
                    } else {
                        del->parent->right = rep;
                        rep->parent = del->parent;
                    }
                } else {
                    root = rep;
                    rep->parent = nullptr;
                }
            } else {
                child = rep->right;
                rep->left = del->left;
                del->left->parent = rep;

                if (del->parent) {
                    if (del == del->parent->left) {
                        del->parent->left = rep;
                        rep->parent = del->parent;
                    } else {
                        del->parent->right = rep;
                        rep->parent = del->parent;
                    }
                } else {
                    root = rep;
                    rep->parent = nullptr;
                }

                parentRP = rep;
            }
        }

        if (rep) {
            rep->color = del->color;
        } else {
            origColor = del->color;
        }

        if (origColor == Color::BLACK) {
            if (child) {
                removeFix(child);
            } else {
                Nil->parent = parentRP;

                if (parentRP) {
                    if (!parentRP->left) {
                        parentRP->left = Nil;
                    } else {
                        parentRP->right = Nil;
                    }
                }

                removeFix(Nil);
                disconnectNil();
            }
        }

        delete del;
    }

    void deleteTree(Node *node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    RedBlackTree() : root(nullptr), size(0), Nil(new Node()) {
        Nil->color = Color::BLACK;
    }

    void insert(const Key &key, const Value &value) {
        insertNode(key, value);
    }

    void remove(const Key &key) {
        Node *target = lookUp(key);
        if (target) {
            deleteNode(target);
            size--;
        }
    }

    Value *at(const Key &key) {
        Node *target = lookUp(key);
        if (target) {
            return target->value;
        } else {
            throw std::out_of_range("Key not found");
        }
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void print() const {
        std::cout << "Inorder Traversal: ";
        inorderTraversal(root);
        std::cout << std::endl;
    }

    void clear() {
        while (root) {
            deleteNode(root);
        }
        size = 0;
    }

    ~RedBlackTree() {
        deleteTree(root);
    }
};

#endif //SIMPLESTL_REDBLACKTREE_H
