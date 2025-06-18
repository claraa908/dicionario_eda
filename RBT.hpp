#ifndef RBT_HPP
#define RBT_HPP
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

template <typename T, typename K>
class RBT{
    private:
    using Node = Node<T, K>;
    Node* root;
    Node* nil;

    void _insertion(RBT* Tree, T key, K value){
        Node* pai = Tree->nil;
        Node* node = Tree->root;

        while(node != Tree->nil){
            pai = node;
            if(key < node->key){
                node = node->left;
            }else if(key > node->key){
                node = node->right;
            }else return;
        }

        Node* novoNo = new Node(key, value, RED, nil, nil, nil);
        if(pai == Tree->nil){
            Tree->root = novoNo;
        }else{
            novoNo->pai = pai;
            if(key < pai->key){
                pai->left = novoNo;
            }else{
                pai->right = novoNo;
            }
        }
        fixupInsert(Tree, novoNo);
    }

    void fixupInsert(RBT* Tree, Node* x){
        while(x->pai->color == RED){
            if(x->pai == x->pai->pai->left){
                Node* tio = x->pai->pai->right;
                if(tio->color == RED){
                    x->pai->pai->color = RED;
                    x->pai->color = BLACK;
                    tio->color = BLACK;
                    x = x->pai->pai;
                }
                else{
                    if(x == x->pai->right)
                        x = x->pai;
                        leftRotation(T, x);
                    x->pai->color = BLACK;
                    x->pai->pai->color = RED;
                    rightRotation(T, x->pai->pai);
                }
            }else if(x->pai == x->pai->pai->right){
                Node* tio = x->pai->pai->left;
                if(tio->color == RED){
                    x->pai->pai->color = RED;
                    x->pai->color = BLACK;
                    tio->color = BLACK;
                    x = x->pai->pai;
                }else{
                    if(x == x->pai->left){
                        x = x->pai;
                        rightRotation(Tree, x);
                    }
                    x->pai->color = BLACK;
                    x->pai->pai->color = RED;
                    leftRotation(Tree, x->pai->pai);
                }
            }
        }
        Tree->root->color = BLACK;
    }

    Node* rightRotation(RBT* Tree, Node* x){
        Node* y = x->left;
        x->left = y->right;
        y->right->pai = x;
        y->right = x;
        y->pai = x->pai;
        x->pai = y;

        if(y->pai == Tree->nil){
            Tree->root = y;
        }else if(y->key < y->pai->key){
            y->pai->left = y;
        }else{
            y->pai->right = y;
        }
        return y;
    }

    Node* leftRotation(RBT* Tree, Node* x){
        Node* y = x->right;
        x->right = y->left;
        y->left->pai = x;
        y->left = x;
        y->pai = x->pai;
        x->pai = y;

        if(y->pai == Tree->nil){
            Tree->root = y;
        }else if(y->key < y->pai->key){
            y->pai->left = y;
        }else{
            y->pai->right = y;
        }
        return y;
    }

    void _remove(RBT* Tree, T key){
        Node* p = Tree->root;
        while (p != Tree->nil && p->key != key){
            if(p->key > key){
                p = p->left;
            }else{
                p = p->right;
            }
        }

        if(p != Tree->nil){
            delete_RB(Tree, p);
        }
    }

    void delete_RB(RBT* Tree, Node* p){
        Node* y = Tree->nil;
        if(p->left == Tree->nil || p->right == Tree->nil){
            y = p;
        }else{
            y = minimum(Tree, p->right);
        }

        Node* x;
        if(y->right != Tree->nil){
            x = y->right;
        }else{
            x = y->left;
        }

        if(x != Tree->nil){
            x->pai = y->pai;
        }

        if(y->pai == Tree->nil){
            Tree->root = x;
        }else{
            if(y == y->pai->left){
                y->pai->left = x;
            }else{
                y->pai->right = x;
            }
        }

        if(y != p){
            p->key = y->key;
            p->value = y->value;
        }
        if(y->color == BLACK){
            fixupDelete(Tree, x);
        }
        delete y;
    }

    Node* minimum(RBT* Tree, Node* p){
        while(p->left != Tree->nil){
            p = p->left;
        }
        return p;
    }

    void fixupDelete(RBT* Tree, Node* x){
        while(x != Tree->root && x->color == BLACK){
            if(x == x->pai->left){
                Node* w = x->pai->right;
                if(w->color == RED){
                    w->color = BLACK;
                    x->pai->color = RED;
                    leftRotation(Tree, x->pai);
                    w = x->pai->right;
                }
                if(w->left->color == BLACK && w->right->color == BLACK){
                    w->color = RED;
                    x = x->pai;
                }
                else{
                    if(w->right->color == BLACK){
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotation(Tree, w);
                        w = x->pai->right;
                    }
                    w->color = x->pai->color;
                    x->pai->color = BLACK;
                    w->right->color = BLACK;
                    leftRotation(Tree, x->pai);
                    x = Tree->root;
                }
            } else {
                Node* w = x->pai->left;
                if(w->color == RED){
                    w->color = BLACK;
                    x->pai->color = RED;
                    rightRotation(Tree, x->pai);
                    w = x->pai->left;
                }
                if(w->right->color == BLACK && w->left->color == BLACK){
                    w->color = RED;
                    x = x->pai;
                }
                else{
                    if(w->left->color == BLACK){
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotation(Tree, w);
                        w = x->pai->left;
                    }
                    w->color = x->pai->color;
                    x->pai->color = BLACK;
                    w->left->color = BLACK;
                    rightRotation(Tree, x->pai);
                    x = Tree->root;
                }
            }
        }
        x->color = BLACK;
    }

    public:
    RBT(){
        nil = new Node(T{}, K{}, BLACK, nullptr, nullptr, nullptr);
        nil->left = nil->right = nil;
        root = nil;
        root->pai = nil;
    }

    void insertion(T key, K value){
        _insertion(this, key, value);
    }

    void remove(T key){
        _remove(this, key);
    }
};
#endif