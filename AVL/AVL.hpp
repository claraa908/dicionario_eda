#ifndef AVL_HPP
#define AVL_HPP
#include "NodeAVL.hpp"

template <typename T, typename K>
class AVL{
    private:
    using Node = Node<T, K>;
    Node* root;
        //fução que calcula a altura da arvore/subarvore
        int height (Node * node){
            return (_empty(node)) ? 0 : node->height;
        }

        //funão que calcula o balance da arvore/subarvore
        int balance (Node * node){
            return height(node->right) - height(node->left);
        }

        //função que rotaciona uma arvore/subarvore para direita
        Node * rightRotation (Node *p){
            Node* u = p->left;
            p->left = u->right;
            u->right = p;

            p->height = 1 +  max(height(p->left), height(p->right));
            u->height = 1 +  max(height(u->left), height(u->right));
            return u;
        }

        //função que rotaciona uma arvore/subarvore para esquerda
        Node * leftRotation (Node *p){
            Node* u = p->right;
            p->right = u->left;
            u->left = p;

            p->height = 1 +  max(height(p->left), height(p->right));
            u->height = 1 +  max(height(u->left), height(u->right));
            return u;
        }

        //insert
        //função que adiciona um nó sem desbalancear a arvore
        Node* _insert(Node *p , T key, K value){
            if(_empty(p)){
                return new Node{key, value, 1, nullptr, nullptr};
            }
            if(key == p->key){
                return p;
            }
            if(key < p->key){
                p->left = _insert(p->left, key);
            }
            else if(key>p->key){
                p->right = _insert(p->right, key);
            }
            p = fixup_insertion(p, key);
            return p;
        }
        
        //função que conserta o balanço da arvore após uma inserção
        Node* fixup_insertion(Node *p , T key){
            int bal = balance(p);
            if(bal < -1 && key < p->left->key){
                return rightRotation(p);
            }
            if(bal < -1 && key > p->left->key){
                p->left = leftRotation(p->left);
                return rightRotation(p);
            }
            if(bal > 1 && key > p->right->key){
                return leftRotation(p);
            }
            if(bal > 1 && key < p->right->key){
                p->right = rightRotation(p->right);
                return leftRotation(p);
            }
            p->height = 1 + max(height(p->left), height(p->right));
            return p;
        }

        //erase
        //função que remove um nó sem desbalancear a arvore
        Node* _erase(Node* p, T key){
            if(_empty(p)){
                return nullptr;
            }
            if(key < p->key){
                p->left = _erase(p->left, key);
            }else if(key > p->key){
                p->right = _erase(p->right, key);
            }else if(p->right == nullptr){
                Node* aux = p->left;
                delete p;
                return aux;
            }else{
                p->right = remove_successor(p, p->right);
            }

            p = fixup_erase(p);
            return p;
        }

        //função que remove o sucessor de um nó
        Node* remove_successor(Node* node, Node* p){
            if(!_empty(p->left)){
                p = remove_successor(node, p->left);
            }else{
                node->key = p->key;
                Node* aux = p->right;
                delete p;
                return aux;
            }
            p = fixup_erase(p);
            return p;
        }

        //função que conserta o balanço da arvore após uma remoção
        Node* fixup_erase(Node* p){
            int bal = balance(p);
            if(bal < -1 && balance(p->left) <= 0){
                return rightRotation(p);
            }
            if(bal < -1 && balance(p->left) > 0){
                p->left = leftRotation(p);
                return rightRotation(p);
            }
            if(bal > 1 && balance(p->right) >= 0){
                return leftRotation(p);
            }
            if(bal > 1 && balance(p->right) < 0){
                p->right = rightRotation(p);
                return leftRotation(p);
            }
            p->height = 1 + max(height(p->left), height(p->right));
            return p;
        }

        //contains
        //função booleana que recebe o primeiro nó da árvore e um determinado valor e verifica se este está na árvore
        bool _contains(int key, Node* p){
            if(_empty(p)){
                return false;
            }
            if(key == p->key){
                return true;
            }

            if(key < p->key){
                return _contains(key, p->left);
            }else{
                return _contains(key, p->right);
            }
        }

        //clear
        //função privada que deleta os nos em pos ordem
        Node* _clear(Node* p){
            if(p != nullptr){
                p->left = _clear(p->left);
                p->right = _clear(p->right);
                delete p;
            }
            return nullptr;
        }

        //empty
        //função que verifica se a arvore é vazia ou não
        bool _empty(Node *p){
            return (p == nullptr) ? true : false;
        }

        //size
        //função privada que retorna o quantidade de nos que a arvore possui
        int _size(Node *p){
            if(_empty(p)){
                return 0;
            }

            return 1 + _size(p->left) + _size(p->right);
        }

    public:
    //construtor
        AVL() {
            root = nullptr;
        }

        //destrutor
        ~AVL(){
            root = _clear(root);
        }

        //função publica que insere um no
        void insert(T key, K value){
            root = _insert(root, key, value);
        }

        //função publica que apaga um no
        void erase(int key){
            if(!contains(key)){
                throw invalid_argument("esse valor nao existe na arvore para remocao");
            }
            root = _erase(root, key);
        }

        //função publica que retorna se um nó está ou não na árvore
        bool contains(int key){
            return _contains(key, root);
        }

        //função publica que limpa a arvore
        void clear(){
            if(_empty(root)){
                throw runtime_error("nao ha o que limpar");
            }
            root = _clear(root);
        }

        //função publica que retorna se uma árvore é vazia ou não
        bool empty(){
            return _empty(root);
        }

        //função publica que retorna quantos nós uma árvore possui
        int size(){
            return _empty(root) ? 0 : _size(root);
        }

        //sobrecarga do operador de atribuição
        Set& operator=(const Set& var){
            if(this != &var){
                this->_clear(root);
                root = copy(var.root);
            }
            return *this;
        }
};
#endif