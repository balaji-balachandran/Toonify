/**
 * @file Splay.cpp
 * 
*/

template <class K, class V>
void Splay<K,V>::splay(Node<K,V>* n) {
    if (n == nullptr) return;
    
}


template <class K, class V>
Node<K,V>* Splay<K,V>::insert(const K& key, const V& data) {
    if (!root) {
        root = new Node<K,V>(key, data);
        return root;
    }

    Node<K,V>* new_node = new Node<K,V>(key, data);



    if (key == root->key && data == 0) return nullptr;
    return nullptr;
}


template <class K, class V>
void Splay<K,V>::remove(const K& key) {
    if (key == root->key) return;
}


template <class K, class V>
Node<K,V>* Splay<K,V>::find(const K& key) {
    if (key == root->key) return nullptr;
    return nullptr;
}