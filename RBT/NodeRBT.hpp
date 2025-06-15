#ifndef NODE_RBT_HPP
#define NODE_RBT_HPP
#include <string>

#define RED true
#define BLACK false

template <typename T, typename K>
struct Node{
    T key;
    K value;
    bool color;
    Node* right;
    Node* left;
    Node* pai;

    Node(T k, K v, bool c, Node* r, Node* l, Node* p){
        key = k;
        value = v;
        color = c;
        right = r;
        left = l;
        pai = p;
    }
};

#endif