#ifndef NODE_RBT_HPP
#define NODE_RBT_HPP
#include <string>

#define red true
#define black false

struct Node{
    std::string key;
    int value;
    bool color;
    Node* right;
    Node* left;
    Node* pai;

    Node(std::string k, int v, bool c, Node* r, Node* l, Node* p){
        key = k;
        value = v;
        color = c;
        right = r;
        left = l;
        pai = p;
    }
};

#endif