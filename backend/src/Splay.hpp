/**
 * @file Splay.cpp
 * 
*/

template <class K, class V>
Splay<K,V>::Splay() {
    root = nullptr;
}

template <class K, class V>
Splay<K,V>::Splay(const Splay& other) {
    *this = other;
}

template <class K, class V>
Splay<K,V>::~Splay() {
    Node<K,V>* n = root;

    if (!n) return;
    remove(n->left);
    remove(n->right);
    delete n;
}

template <class K, class V>
void Splay<K,V>::remove(Node<K,V>* n) {
    if (!n) return;
    remove(n->left);
    remove(n->right);
    delete n;
}


template <class K, class V>
Node<K,V>* Splay<K,V>::get_root() {
    return root;
}


template <class K, class V>
void Splay<K,V>::splay_nodes(Node<K,V>* n) {
    if (!n) return;
    
}


template <class K, class V>
Node<K,V>* Splay<K,V>::insert(const K& key, const V& data) {
    if (!root) {
        root = new Node<K,V>(key, data);
        return root;
    }

    Node<K,V>* new_node = new Node<K,V>(key, data);
    Node<K,V>* curr = root;

    while (curr->left && curr->right) {
        if (key < curr->key) curr = curr->left;
        else if (key > curr->key) curr = curr->right;
    }

    if (key < curr->key) curr->left = new_node;
    else if (key > curr->key) curr->right = new_node;
    
    // splay_nodes(new_node);

    return new_node;
}

template <class K, class V>
Node<K,V>* Splay<K,V>::find(const K& key) {
    Node<K,V>* curr = root;

    while (curr->key != key && (curr->left && curr->right)) {
        if (key < curr->key) curr = curr->left;
        else if (key > curr->key) curr = curr->right;
    }

    if (curr->key == key) {
        // splay_nodes(curr)
        return curr;
    }

    return nullptr;
}