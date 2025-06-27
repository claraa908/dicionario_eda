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
        mutable int count_comp;
        mutable int count_recolor;
        mutable int count_rotation;

        //funções privadas
        Node* rightRotation(Node* x){
            Node* y = x->left;
            x->left = y->right;
            y->right->parent = x;
            y->right = x;
            y->parent = x->parent;
            x->parent = y;

            if(y->parent == nil){
                root = y;
            }else if(y->tuple.first < y->parent->tuple.first){
                y->parent->left = y;
            }else{
                y->parent->right = y;
            }
            return y;
        }

        Node* leftRotation(Node* x){
            Node* y = x->right;
            x->right = y->left;
            y->left->parent = x;
            y->left = x;
            y->parent = x->parent;
            x->parent = y;

            if(y->parent == nil){
                root = y;
            }else if(y->tuple.first < y->parent->tuple.first){
                y->parent->left = y;
            }else{
                y->parent->right = y;
            }
            return y;
        }

        void _insert(T key, K value){
            Node* pai = nil;
            Node* node = root;

            while(node != nil){
                pai = node;
                if(key < node->tuple.first){
                    count_comp++;
                    node = node->left;
                }else if(key > node->tuple.first){
                    count_comp += 2;
                    node = node->right;
                }else{
                    node->tuple.second = value;
                    count_comp += 3;
                    return;
                }
            }

            Node* novoNo = new Node(key, value, RED, nil, nil, nil);
            if(pai == nil){
                root = novoNo;
            }else{
                novoNo->parent = pai;
                if(key < pai->tuple.first){
                    count_comp++;
                    pai->left = novoNo;
                }else{
                    count_comp += 2;
                    pai->right = novoNo;
                }
            }
            fixup_insertion(novoNo);
        }

        void fixup_insertion(Node* x){
            while(x->parent->color == RED){
                if(x->parent == x->parent->parent->left){
                    Node* tio = x->parent->parent->right;
                    if(tio->color == RED){
                        x->parent->parent->color = RED;
                        x->parent->color = BLACK;
                        tio->color = BLACK;
                        count_recolor += 3;
                        x = x->parent->parent;
                    }
                    else{
                        if(x == x->parent->right){
                            x = x->parent;
                            leftRotation(x);
                            count_rotation++;
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        count_recolor += 2;
                        rightRotation(x->parent->parent);
                        count_rotation++;
                    }
                }else if(x->parent == x->parent->parent->right){
                    Node* tio = x->parent->parent->left;
                    if(tio->color == RED){
                        x->parent->parent->color = RED;
                        x->parent->color = BLACK;
                        tio->color = BLACK;
                        count_recolor += 3;
                        x = x->parent->parent;
                    }else{
                        if(x == x->parent->left){
                            x = x->parent;
                            rightRotation(x);
                            count_rotation++;
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        count_recolor += 2;
                        leftRotation(x->parent->parent);
                        count_rotation++;
                    }
                }
            }
            root->color = BLACK;
            count_recolor++;
        }

        K& _at(Node* p, T key){
            if(p == nil){
                throw std::invalid_argument("chave nao encontrada na arvore");
            }

            if(key == p->tuple.first){
                count_comp++;
                return p->tuple.second;
            }else if(key < p->tuple.first){
                count_comp += 2;
                return _at(p->left, key);
            }else{
                count_comp += 3;
                return _at(p->right, key);
            }
        }

        const K& _at(Node* p, const T& key) const {
            if (p == nil) {
                throw std::invalid_argument("chave nao encontrada na arvore");
            }

            if (key == p->tuple.first) {
                count_comp++;
                return p->tuple.second;
            } else if (key < p->tuple.first) {
                count_comp += 2;
                return _at(p->left, key);
            } else {
                count_comp += 3;
                return _at(p->right, key);
            }
        }

        // função que percorre a árvore em busca de um nó que contenha a chave pedida, 
        // se existir chama a função que vai remover esse nó
        void _erase(T key){
            Node* p = root;
            while (p != nil && p->tuple.first != key){
                if(p->tuple.first > key){
                    count_comp++;
                    p = p->left;
                }else{
                    count_comp += 2;
                    p = p->right;
                }
            }

            if(p != nil){
                delete_RB(p);
            }
        }

        void delete_RB(Node* p){
            Node* y = nil;
            if(p->left == nil || p->right == nil){
                y = p;
            }else{
                y = minimum(p->right);
            }

            Node* x;
            if(y->right != nil){
                x = y->right;
            }else{
                x = y->left;
            }

            if(x != nil){
                x->parent = y->parent;
            }

            if(y->parent == nil){
                root = x;
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
                fixup_erase(x);
            }
            delete y;
        }

        Node* minimum(Node* p){
            while(p->left != nil){
                p = p->left;
            }
            return p;
        }


        void fixup_erase(Node* x){
            while(x != root && x->color == BLACK){
                if(x == x->parent->left){
                    Node* w = x->parent->right;
                    if(w->color == RED){
                        w->color = BLACK;
                        x->parent->color = RED;
                        leftRotation(x->parent);
                        count_rotation++;
                        w = x->parent->right;
                        count_recolor += 2;
                    }
                    if(w->left->color == BLACK && w->right->color == BLACK){
                        w->color = RED;
                        x = x->parent;
                        count_recolor++;
                    }
                    else{
                        if(w->right->color == BLACK){
                            w->left->color = BLACK;
                            w->color = RED;
                            rightRotation(w);
                            count_rotation++;
                            w = x->parent->right;
                            count_recolor += 2;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->right->color = BLACK;
                        leftRotation(x->parent);
                        count_rotation++;
                        x = root;
                        count_recolor += 3;
                    }
                } else {
                    Node* w = x->parent->left;
                    if(w->color == RED){
                        w->color = BLACK;
                        x->parent->color = RED;
                        rightRotation(x->parent);
                        count_rotation++;
                        w = x->parent->left;
                        count_recolor += 2;
                    }
                    if(w->right->color == BLACK && w->left->color == BLACK){
                        w->color = RED;
                        x = x->parent;
                        count_recolor++;
                    }
                    else{
                        if(w->left->color == BLACK){
                            w->right->color = BLACK;
                            w->color = RED;
                            leftRotation(w);
                            count_rotation++;
                            w = x->parent->left;
                            count_recolor += 2;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->left->color = BLACK;
                        rightRotation(x->parent);
                        count_rotation++;;
                        x = root;
                        count_recolor += 3;
                    }
                }
            }
            x->color = BLACK;
            count_recolor++;
        }

        bool _contains(T key){
            if(root == nil){
                return false;
            }

            Node* p = root;
            while(p != nil && p->tuple.first != key){
                if(key == p->tuple.first){
                    count_comp++;
                    return true;
                }else if(key < p->tuple.first){
                    count_comp += 2;
                    p = p->left;
                }else{
                    count_comp += 3;
                    p = p->right;
                }
            }
            return false;
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
        count_comp = 0;
        count_recolor = 0;
        count_rotation = 0;
    }

    //destrutor
    ~RBT(){
        root = _clear(root);
    }

    void insert(T key, K value){
        _insert(key, value);
    }

    //função que retorna o valor de um par baseado na chave
    K& at(const T& k){
        if(root == nil){
            throw std::invalid_argument("árvore vazia");
        }
        return _at(root, k);
    }

    //função constante que retorna o valor de um par baseado na chave
    const K& at(const T& k) const{
        if(root == nil){
            throw std::invalid_argument("árvore vazia");
        }
        return _at(root, k);
    }

    void erase(T key){
        _erase(key);
    }

    bool contains(T key){
        return _contains(key);
    }

    void clear(){
        root = _clear(root);
    }

    bool empty(){
        return _empty(root);
    }

    int size(){
        return _size(root);
    }

    K& operator[](const T& key) {
        if (!contains(key)) {
            insert(key, K{});
        }
        return at(key);
    }
    
    void show(){
        bshow(root, "");
    }

    int getCountComparation(){
        return count_comp;
    }

    int getCountRecolor(){
        return count_recolor;
    }

    int getCountRotation(){
        return count_rotation;
    }
};
#endif