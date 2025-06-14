#ifndef NODE_AVL_HPP
#define NODE_AVL_HPP

template <typename T, typename K>
struct Node{
    T key;
    K value;
    int height;
    Node* left;
    Node* right;

    Node (T k, K v, int h, Node* l, Node* r) {
        key = k;
        value = v;
        left = l;
        right = r;
        height = h;
    }
};

#endif