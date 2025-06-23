#ifndef AVL_HPP
#define AVL_HPP
#include <string>
#include <utility>
#include <stdexcept>
#include <algorithm>

template <typename T, typename K>
class AVL{
    private:
        //node
        struct Node{
            std::pair <T, K> tuple;
            int height;
            Node* left;
            Node* right;

            Node (T k, K v, int h, Node* l, Node* r) {
                tuple.first = k;
                tuple.second = v;
                left = l;
                right = r;
                height = h;
            }
        };

        //variáveis
        Node* root;
        mutable int count_comp;
        mutable int count_rotation;


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

            p->height = 1 +  std::max(height(p->left), height(p->right));
            u->height = 1 +  std::max(height(u->left), height(u->right));
            return u;
        }

        //função que rotaciona uma arvore/subarvore para esquerda
        Node * leftRotation (Node *p){
            Node* u = p->right;
            p->right = u->left;
            u->left = p;

            p->height = 1 +  std::max(height(p->left), height(p->right));
            u->height = 1 +  std::max(height(u->left), height(u->right));
            return u;
        }

        //insert
        //função que adiciona um nó sem desbalancear a arvore
        Node* _insert(Node *p , T key, K value){
            if(_empty(p)){
                return new Node{key, value, 1, nullptr, nullptr};
            }
            
            if(key == p->tuple.first){
                count_comp++;
                p->tuple.second = value;
                return p;
            }
            if(key < p->tuple.first){
                count_comp++;
                p->left = _insert(p->left, key, value);
            }
            else if(key>p->tuple.first){
                count_comp++;
                p->right = _insert(p->right, key, value);
            }
            p = fixup_insertion(p, key);
            return p;
        }
        
        //função que conserta o balanço da arvore após uma inserção
        Node* fixup_insertion(Node *p, T key){
            int bal = balance(p);
            if(bal < -1 && key < p->left->tuple.first){
                count_comp++;
                count_rotation++;
                return rightRotation(p);
            }
            if(bal < -1 && key > p->left->tuple.first){
                count_comp++;
                count_rotation += 2;
                p->left = leftRotation(p->left);
                return rightRotation(p);
            }
            if(bal > 1 && key > p->right->tuple.first){
                count_comp++;
                count_rotation++;
                return leftRotation(p);
            }
            if(bal > 1 && key < p->right->tuple.first){
                count_comp++;
                count_rotation += 2;
                p->right = rightRotation(p->right);
                return leftRotation(p);
            }
            p->height = 1 + std::max(height(p->left), height(p->right));
            return p;
        }

        K& _getValue(Node* p, T key){
            if(p == nullptr){
                throw std::invalid_argument("chave nao encontrada na arvore");
            }

            if(key == p->tuple.first){
                count_comp++;
                return p->tuple.second;
            }else if(key < p->tuple.first){
                count_comp++;
                return _getValue(p->left, key);
            }else{
                count_comp++;
                return _getValue(p->right, key);
            }
            return p->tuple.second;
        }

        const K& _getValue(Node* p, const T& key) const {
            if (p == nullptr) {
                throw std::invalid_argument("chave nao encontrada na arvore");
            }

            if (key == p->tuple.first) {
                count_comp++;
                return p->tuple.second;
            } else if (key < p->tuple.first) {
                count_comp++;
                return _getValue(p->left, key);
            } else {
                count_comp++;
                return _getValue(p->right, key);
            }
        }

        //erase
        //função que remove um nó sem desbalancear a arvore
        Node* _erase(Node* p, T key){
            if(_empty(p)){
                return nullptr;
            }

            if(key < p->tuple.first){
                count_comp++;
                p->left = _erase(p->left, key);
            } else if(key > p->tuple.first){
                count_comp++;
                p->right = _erase(p->right, key);
            } else {
                if(p->left == nullptr){
                    Node* aux = p->right;
                    delete p;
                    return aux;
                } else if(p->right == nullptr){
                    Node* aux = p->left;
                    delete p;
                    return aux;
                } else {
                    Node* suc = getMin(p->right);
                    p->tuple = suc->tuple;
                    p->right = _erase(p->right, suc->tuple.first);
                }
            }

            p->height = 1 + std::max(height(p->left), height(p->right));
            return fixup_erase(p);
        }

        Node* getMin(Node* p){
            while(p->left != nullptr){
                p = p->left;
            }
            return p;
        }

        //função que conserta o balanço da arvore após uma remoção
        Node* fixup_erase(Node* p){
            int bal = balance(p);
            if(bal < -1 && balance(p->left) <= 0){
                count_rotation++;
                return rightRotation(p);
            }
            if(bal < -1 && balance(p->left) > 0){
                count_rotation += 2;
                p->left = leftRotation(p->left);
                return rightRotation(p);
            }
            if(bal > 1 && balance(p->right) >= 0){
                count_rotation++;
                return leftRotation(p);
            }
            if(bal > 1 && balance(p->right) < 0){
                count_rotation += 2;
                p->right = rightRotation(p->right);
                return leftRotation(p);
            }
            p->height = 1 + std::max(height(p->left), height(p->right));
            return p;
        }

        //contains
        //função booleana que recebe o primeiro nó da árvore e um determinado valor e verifica se este está na árvore
        bool _contains(T key, Node* p){
            if(_empty(p)){
                return false;
            }
            if(key == p->tuple.first){
                count_comp++;
                return true;
            }

            if(key < p->tuple.first){
                count_comp++;
                return _contains(key, p->left);
            }else{
                count_comp++;
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

        void bshow(Node *node, std::string heranca) const {
            if(node != nullptr && (node->left != nullptr || node->right != nullptr))
                bshow(node->right , heranca + "r");
            for(int i = 0; i < (int) heranca.size() - 1; i++)
                std::cout << (heranca[i] != heranca[i + 1] ? "|   " : "    ");
            if(heranca != "")
                std::cout << (heranca.back() == 'r' ? "|--" : "|--");
            if(node == nullptr){
                std::cout << "#" << std::endl;
                return;
            }
            std::cout << node->tuple.first << ": " << node->tuple.second<< std::endl;
            if(node != nullptr && (node->left != nullptr || node->right != nullptr))
                bshow(node->left, heranca + "l");
        }

    public:
    //construtor
        AVL() {
            root = nullptr;
            count_comp = 0;
            count_rotation = 0;
        }

        //destrutor
        ~AVL(){
            root = _clear(root);
        }

        //função publica que insere um no
        void insert(T key, K value){
            root = _insert(root, key, value);
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

        //função publica que apaga um no
        void erase(T key){
            if(!contains(key)){
                throw std::invalid_argument("esse valor nao existe na arvore para remocao");
            }
            root = _erase(root, key);
        }

        //função publica que retorna se um nó está ou não na árvore
        bool contains(T key){
            return _contains(key, root);
        }

        //função publica que limpa a arvore
        void clear(){
            if(_empty(root)){
                throw std::runtime_error("nao ha o que limpar");
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

        void show(){
            bshow(root, "");
        }

        int getCountComparation(){
            return count_comp;
        }

        int getCountRotation(){
            return count_rotation;
        }
};

#endif