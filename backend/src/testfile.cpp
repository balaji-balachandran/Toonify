#include "Splay.h"
#include "Huffman.h"
#include "../lib/PNG.h"

#include <iostream>
#include <vector>

using namespace std;

// implement catch2;
// make sure to test insert, find, delete, etc.


int main () {
    cout << "Build & Test Splay Tree" << endl;

    Splay<int, int> s;
    s.insert(10, 9999);
    cout << s.get_root()->key << endl;

    s.insert(0, 9998);
    s.insert(20, 9997);

    cout << s.get_root()->left->key << ' ' << s.get_root()->right->key << endl;


    s.insert(5, 9996);
    s.insert(15, 9995);

    cout << "Layer 1: " <<  s.get_root()->left->right->key << ' ' << s.get_root()->right->left->key << endl;
    cout << "Layer 2: " << s.get_root()->left->right->parent->key << ' ' << s.get_root()->right->left->parent->key << endl;
    cout << "Layer 3: " << s.get_root()->left->parent->key << endl;


    Node<int, int>* n = s.find(11);


    if (n) cout << n->key << endl;
    else cout << "nullptr" << endl;

    n = s.find(10);
    cout << "New root: " << s.get_root()->key << endl;
    n = s.find(0);
    cout << "New root: " << s.get_root()->key << ' ' << s.get_root()->right->key << endl;
    n = s.find(20);
    cout << "New root: " << s.get_root()->key << ' ' << s.get_root()->left->key << endl;
    n = s.find(5);
    cout << "New root: " << s.get_root()->key << ' ' << s.get_root()->right->key << endl;
    n = s.find(15);
    cout << "New root: " << s.get_root()->key << ' ' << s.get_root()->left->key << endl;
    

    n = s.find(16);
    
    if (n) cout << n->key << endl;
    else cout << "nullptr" << endl;


    // std::vector<int> vals;
    // vals = s.get_nodes();
    // std::cout << "{ ";
    // for (int i : vals) {
    //     std::cout << i << ' ';
    // }
    // std::cout << '}';

    s.insert(10, 9995);



    return 0;
}