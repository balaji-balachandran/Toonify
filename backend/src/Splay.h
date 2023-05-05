#pragma once
#include <vector>

/**
 * @file Splay.h
 * Splay Tree Class Implementation
 * Search,
 * Insert, 
 * Delete - just delete all nodes at once using destructor
 * 
*/
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
    Node<K,V>* find(const K& key);

    Node<K,V>* get_root();

    // std::vector<K> get_nodes();


private:
    void splay_nodes(Node<K,V>* n);
    Node<K,V>* rotate_right(Node<K,V>* n);
    Node<K,V>* rotate_left(Node<K,V>* n);
    // void get_nodes_rec(Node<K,V>* n, std::vector<K>& v);
    void remove(Node<K,V>* n);

    
    Node<K,V>* root;

};

#include "./Splay.hpp"
