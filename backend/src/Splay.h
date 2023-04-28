/**
 * @file Splay.h
 * Splay Tree Class Implementation
 * Search,
 * Insert, 
 * Delete - just delete all nodes at once using destructor
 * 
*/


#pragma once
template <class K, class V>
struct Node{
    Node() = default;
    Node(const K& k_, const V& d_) : key(k_), data(d_), left(nullptr), right(nullptr) {}
    K key;
    V data;
    Node* left;
    Node* right;
    Node* parent;
};

template <class K, class V>
class Splay{
public:

    Splay();
    Splay(const Splay& other);
    ~Splay();
    const Splay& operator=(const Splay& rhs);


    Node<K,V>* insert(const K& key, const V& data);
    void remove(const K& key);
    Node<K,V>* find(const K& key);


private:
    void rotateLeft(Node<K,V>* n);
    void rotateRight(Node<K,V>* n);
    void splay(Node<K,V>* n);
    
    Node<K,V>* root;

};

#include "./Splay.hpp"
