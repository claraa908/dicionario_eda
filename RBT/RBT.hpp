#ifndef RBT_HPP
#define RBT_HPP
#include "NodeRBT.hpp"

template <typename T, typename K>
class RBT{
    private:
    Node* root;
    Node* nil;

    void _insertion(RBT* T, T key, K value){
        Node* pai = T->nil;
        Node* node = T->root;

        while(node != T->nil){
            pai = node;
            if(key < node->key){
                node = node->left;
            }else if(key > node->key){
                node = node->right;
            }else return;
        }

        Node* novoNo = new Node(key, value, red, nil, nil, nil);
        if(pai == T->nil){
            T->root = novoNo;
        }else{
            novoNo->pai = pai;
            if(key < pai->key){
                pai->left = novoNo;
            }else{
                pai->right = novoNo;
            }
        }
        fixupInsert(T, novoNo);
    }

    void fixupInsert(RBT* T, Node* x){
        while(x->pai->color == red){
            if(x->pai == x->pai->pai->left){
                Node* tio = x->pai->pai->right;
                if(tio->color == red){
                    x->pai->pai->color = red;
                    x->pai->color = black;
                    tio->color = black;
                    x = x->pai->pai;
                }
                else{
                    if(x == x->pai->right)
                        x = x->pai;
                        leftRotation(T, x);
                    x->pai->color = black;
                    x->pai->pai->color = red;
                    rightRotation(T, x->pai->pai);
                }
            }else if(x->pai == x->pai->pai->right){
                Node* tio = x->pai->pai->left;
                if(tio->color == red){
                    x->pai->pai->color = red;
                    x->pai->color = black;
                    tio->color = black;
                    x = x->pai->pai;
                }else{
                    if(x == x->pai->left){
                        x = x->pai;
                        rightRotation(T, x);
                    }
                    x->pai->color = black;
                    x->pai->pai->color = red;
                    leftRotation(T, x->pai->pai);
                }
            }
        }
        T->root->color = black;
    }

    Node* rightRotation(RBT* T, Node* x){
        Node* y = x->left;
        x->left = y->right;
        y->right->pai = x;
        y->right = x;
        y->pai = x->pai;
        x->pai = y;

        if(y->pai == T->nil){
            T->root = y;
        }else if(y->key < y->pai->key){
            y->pai->left = y;
        }else{
            y->pai->right = y;
        }
        return y;
    }

    Node* leftRotation(RBT* T, Node* x){
        Node* y = x->right;
        x->right = y->left;
        y->left->pai = x;
        y->left = x;
        y->pai = x->pai;
        x->pai = y;

        if(y->pai == T->nil){
            T->root = y;
        }else if(y->key < y->pai->key){
            y->pai->left = y;
        }else{
            y->pai->right = y;
        }
        return y;
    }

    public:
    RBT(){
        nil = new Node(0, black, nullptr, nullptr, nullptr);
        nil->left = nil->right = nil;
        root = nil;
        root->pai = nil;
    }

    void insertion(T key, K value){
        _insertion(this, key, value);
    }

};
#endif