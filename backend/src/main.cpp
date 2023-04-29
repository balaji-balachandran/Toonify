#include "Splay.h"
#include "Huffman.h"
#include <iostream>


using namespace std;

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

    cout << s.get_root()->left->right->key << ' ' << s.get_root()->right->left->key << endl;


    Node<int, int>* n = s.find(10000);

    if (n) cout << n->key << endl;
    else cout << "nullptr" << endl;



    return 0;
}