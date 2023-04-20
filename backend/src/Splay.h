#pragma once

/*
* Splay Tree Class Implementation

* Search,
* Insert, 
* Delete

*/

template <class K, class V>
class Splay{
public:

    void insert(const K& key, const V& data);
    void remove(const K& key);
    V find(const K& key) const;

private:

    void rebalance(Node*& r);
    int balance(Node* r);
    int height(Node* r);

    struct Node{
        Node() = default;
        Node(const K& k_, const V& d_) : key(k_), data(d_), left(nullptr), right(nullptr);
        K key;
        V data;
        Node* left;
        Node* right;
    };

    Node* root_;

};