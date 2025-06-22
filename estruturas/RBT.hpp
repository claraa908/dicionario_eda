#ifndef RBT_HPP
#define RBT_HPP
#include <string>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <algorithm>

#define RED true
#define BLACK false

template <typename T, typename K>
class RBT{
        private:
        //node
        struct Node{
        std::pair<T,K> tuple;
        bool color;
        Node* right;
        Node* left;
        Node* parent;

            Node(T k, K v, bool c, Node* r, Node* l, Node* p){
                tuple.first = k;
                tuple.second = v;
                color = c;
                right = r;
                left = l;
                parent = p;
            }
        };

        //variáveis
        Node* root;
        Node* nil;
        int contador_comparacoes;

        //funções privadas
        Node* rightRotation(RBT* Tree, Node* x){
            Node* y = x->left;
            x->left = y->right;
            y->right->parent = x;
            y->right = x;
            y->parent = x->parent;
            x->parent = y;

            if(y->parent == Tree->nil){
                Tree->root = y;
            }else if(y->tuple.first < y->parent->tuple.first){
                y->parent->left = y;
            }else{
                y->parent->right = y;
            }
            return y;
        }

        Node* leftRotation(RBT* Tree, Node* x){
            Node* y = x->right;
            x->right = y->left;
            y->left->parent = x;
            y->left = x;
            y->parent = x->parent;
            x->parent = y;

            if(y->parent == Tree->nil){
                Tree->root = y;
            }else if(y->tuple.first < y->parent->tuple.first){
                y->parent->left = y;
            }else{
                y->parent->right = y;
            }
            return y;
        }

        void _insert(RBT* Tree, T key, K value){
            Node* pai = Tree->nil;
            Node* node = Tree->root;

            while(node != Tree->nil){
                pai = node;
                if(key < node->tuple.first){
                    contador_comparacoes++;
                    node = node->left;
                }else if(key > node->tuple.first){
                    contador_comparacoes++;
                    node = node->right;
                }else{
                    contador_comparacoes++;
                    return;
                }
            }

            Node* novoNo = new Node(key, value, RED, nil, nil, nil);
            if(pai == Tree->nil){
                Tree->root = novoNo;
            }else{
                novoNo->parent = pai;
                if(key < pai->tuple.first){
                    pai->left = novoNo;
                }else{
                    pai->right = novoNo;
                }
            }
            fixup_insertion(Tree, novoNo);
        }

        void fixup_insertion(RBT* Tree, Node* x){
            while(x->parent->color == RED){
                if(x->parent == x->parent->parent->left){
                    Node* tio = x->parent->parent->right;
                    if(tio->color == RED){
                        x->parent->parent->color = RED;
                        x->parent->color = BLACK;
                        tio->color = BLACK;
                        x = x->parent->parent;
                    }
                    else{
                        if(x == x->parent->right){
                            x = x->parent;
                            leftRotation(Tree, x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        rightRotation(Tree, x->parent->parent);
                    }
                }else if(x->parent == x->parent->parent->right){
                    Node* tio = x->parent->parent->left;
                    if(tio->color == RED){
                        x->parent->parent->color = RED;
                        x->parent->color = BLACK;
                        tio->color = BLACK;
                        x = x->parent->parent;
                    }else{
                        if(x == x->parent->left){
                            x = x->parent;
                            rightRotation(Tree, x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        leftRotation(Tree, x->parent->parent);
                    }
                }
            }
            Tree->root->color = BLACK;
        }

        K& _getValue(Node* p, T key){
            if(p == nullptr){
                throw std::invalid_argument("chave nao encontrada na arvore");
            }

            if(key == p->tuple.first){
                return p->tuple.second;
            }else if(key < p->tuple.first){
                return _getValue(p->left, key);
            }else{
                return _getValue(p->right, key);
            }
            return p->tuple.second;
        }

        const K& _getValue(Node* p, const T& key) const {
            if (p == nullptr) {
                throw std::invalid_argument("chave nao encontrada na arvore");
            }

            if (key == p->tuple.first) {
                return p->tuple.second;
            } else if (key < p->tuple.first) {
                return _getValue(p->left, key);
            } else {
                return _getValue(p->right, key);
            }
        }

        // função que percorre a árvore em busca de um nó que contenha a chave pedida, 
        // se existir chama a função que vai remover esse nó
        void _erase(RBT* Tree, T key){
            Node* p = Tree->root;
            while (p != Tree->nil && p->tuple.first != key){
                if(p->tuple.first > key){
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
                x->parent = y->parent;
            }

            if(y->parent == Tree->nil){
                Tree->root = x;
            }else{
                if(y == y->parent->left){
                    y->parent->left = x;
                }else{
                    y->parent->right = x;
                }
            }

            if(y != p){
                p->tuple = y->tuple;
            }
            if(y->color == BLACK){
                fixup_erase(Tree, x);
            }
            delete y;
        }

        Node* minimum(RBT* Tree, Node* p){
            while(p->left != Tree->nil){
                p = p->left;
            }
            return p;
        }


        void fixup_erase(RBT* Tree, Node* x){
            while(x != Tree->root && x->color == BLACK){
                if(x == x->parent->left){
                    Node* w = x->parent->right;
                    if(w->color == RED){
                        w->color = BLACK;
                        x->parent->color = RED;
                        leftRotation(Tree, x->parent);
                        w = x->parent->right;
                    }
                    if(w->left->color == BLACK && w->right->color == BLACK){
                        w->color = RED;
                        x = x->parent;
                    }
                    else{
                        if(w->right->color == BLACK){
                            w->left->color = BLACK;
                            w->color = RED;
                            rightRotation(Tree, w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->right->color = BLACK;
                        leftRotation(Tree, x->parent);
                        x = Tree->root;
                    }
                } else {
                    Node* w = x->parent->left;
                    if(w->color == RED){
                        w->color = BLACK;
                        x->parent->color = RED;
                        rightRotation(Tree, x->parent);
                        w = x->parent->left;
                    }
                    if(w->right->color == BLACK && w->left->color == BLACK){
                        w->color = RED;
                        x = x->parent;
                    }
                    else{
                        if(w->left->color == BLACK){
                            w->right->color = BLACK;
                            w->color = RED;
                            leftRotation(Tree, w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->left->color = BLACK;
                        rightRotation(Tree, x->parent);
                        x = Tree->root;
                    }
                }
            }
            x->color = BLACK;
        }

        bool _contains(RBT* Tree, T key){
            if(Tree->root == Tree->nil){
                return false;
            }

            Node* p = Tree->root;
            while(p != Tree->nil && p->tuple.first != key){
                if(key < p->tuple.first){
                    p = p->left;
                }else{
                    p = p->right;
                }
            }
            return p->tuple.first == key;
        }

        Node* _clear(Node* p){
            if(p == nil) return nil;

            _clear(p->left);
            _clear(p->right);
            delete p;

            return nil;
        }

        bool _empty(Node* p){
            return p == nil;
        }

        int _size(Node* p) {
            if (p == nil) return 0;
            return 1 + _size(p->left) + _size(p->right);
        }

        void bshow(Node *node, std::string heranca) {
            if(node != nil && (node->left != nil || node->right != nil))
                bshow(node->right , heranca + "r");

            for(int i = 0; i < (int) heranca.size() - 1; i++)
                std::cout << (heranca[i] != heranca[i + 1] ? "|   " : "    ");

            if(heranca != "")
                std::cout << (heranca.back() == 'r' ? "|-- " : "|-- ");
            
            if(node == nil){
                std::cout << "#" << std::endl;
                return;
            }

            if (node->color == RED)
                std::cout << "\033[1;31m" << node->tuple.first << ": " << node->tuple.second << "\033[0m" << std::endl ;
            else
                std::cout << "\033[1;30m" << node->tuple.first << ": " << node->tuple.second << "\033[0m" << std::endl;

            if(node != nil && (node->left != nil || node->right != nil))
                bshow(node->left, heranca + "l");
        }

    public:

    //construtor default
    RBT(){
        nil = new Node(T{}, K{}, BLACK, nullptr, nullptr, nullptr);
        nil->left = nil->right = nil;
        root = nil;
        root->parent = nil;
        contador_comparacoes = 0;
    }

    //destrutor
    ~RBT(){
        root = _clear(this->root);
    }

    void insert(T key, K value){
        _insert(this, key, value);
    }

    //função que retorna o valor de um par baseado na chave
    K& getValue(const T& k){
        if(root == nullptr){
            throw std::invalid_argument("árvore vazia");
        }
        return _getValue(root, k);
    }

    //função constante que retorna o valor de um par baseado na chave
    const K& getValue(const T& k) const{
        if(root == nullptr){
            throw std::invalid_argument("árvore vazia");
        }
        return _getValue(root, k);
    }

    void erase(T key){
        _erase(this, key);
    }

    bool contains(T key){
        return _contains(this, key);
    }

    void clear(){
        root = _clear(this->root);
    }

    bool empty(){
        _empty(root);
    }

    int size(){
        return _size(root);
    }

    void show(){
        bshow(this->root, "");
    }

    int getContador(){
        return contador_comparacoes;
    }
};
#endif