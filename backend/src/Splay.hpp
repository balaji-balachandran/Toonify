/**
 * @file Splay.cpp
 * 
*/

template <class K, class V>
Splay<K,V>::Splay() {
    root = nullptr;
}

template <class K, class V>
Splay<K,V>::Splay(const Splay<K,V>& other) {
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
    else curr->right = new_node;
        
    
    new_node->parent = curr;
    
    splay_nodes(new_node);

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
        splay_nodes(curr);
        return curr;
    }

    return nullptr;
}


template<class K, class V>
Node<K,V>* Splay<K,V>::rotate_right(Node<K,V>* n) {
        // Node<K, V>* curr = n;
		Node<K, V>* p = n->parent;
		Node<K, V>* x = n->left;
		Node<K, V>* T2 = x->right;

		x->right = n;
		n->parent = x;
		n->left = T2;

		if (T2 != nullptr) T2->parent = n;
		x->parent = p;
		if (x->parent != nullptr) {
			if (x->parent->left == n) x->parent->left = x;
            else x->parent->right = x;
		}

		return x;
}

template<class K, class V>
Node<K,V>* Splay<K,V>::rotate_left(Node<K,V>* n) {
        // Node<K, V>* curr = n;
		Node<K, V>* p = n->parent;
		Node<K, V>* x = n->right;
		Node<K, V>* T2 = x->left;

		x->left = n;
		n->parent = x;
		n->right = T2;

		if (T2 != nullptr) T2->parent = n;
		x->parent = p;
		if (x->parent != nullptr) {
			if (x->parent->left == n) x->parent->left = x;
            else x->parent->right = x;
		}

		return x;
}

template <class K, class V>
void Splay<K,V>::splay_nodes(Node<K,V>* n) {

    // 3 cases to consider:
    /**
     * the node is the root --> do nothing
     * the parent of the node to splay is root --> just rotateLeft or rotateRight
     * else there are 4 cases:
        * zig zig
        * zag zag
        * zig zag
        * zag zig
    */


	if (n == root || n == nullptr) return;

	// //zig case
	// if (n->parent == root) {
	// 	if (n->parent->left == n) root = rotate_right(root);
    //     else root = rotate_left(root);
	// 	return;
	// }

	// //zig zig case
	// else if (n->parent->left == n && n->parent->parent->left == n->parent) {
	// 	if (n->parent->parent == root) {
	// 		root = rotate_right(root);
	// 		root = rotate_right(root);
	// 		return;
	// 	}
	// 	else {
	// 		n->parent = rotate_right(n->parent->parent);
	// 		n = rotate_right(n->parent);
	// 		splay_nodes(n);
	// 		return;
	// 	}
	// } 

	// //zag zag case
	// else if (n->parent->right == n && n->parent->parent->right == n->parent) {
	// 	if (n->parent->parent == root) {
	// 		root = rotate_left(root);
	// 		root = rotate_left(root);
	// 		return;
	// 	} else {
	// 		n->parent = rotate_left(n->parent->parent);
	// 		n = rotate_left(n->parent);

	// 		splay_nodes(n);
	// 		return;
	// 	}
	// } 

	// 	//zag-zig cases
	// else if (n->parent->right == n && n->parent->parent->left == n->parent) {
	// 	n = rotate_left(n->parent);
	// 	if (n->parent == root) {
	// 		root = rotate_right(root);
	// 		return;
	// 	} else {
	// 		n = rotate_right(n->parent);
	// 		splay_nodes(n);
	// 		return;
	// 	}
	// } 

	// 	//zig zag case
	// else if (n->parent->left == n && n->parent->parent->right == n->parent) {
	// 	n = rotate_right(n->parent);

	// 	if (n->parent == root) {
	// 		root = rotate_left(root);
	// 		return;
	// 	} else {
	// 		n = rotate_left(n->parent);
	// 		splay_nodes(n);
	// 		return;
	// 	}
	// }

}
