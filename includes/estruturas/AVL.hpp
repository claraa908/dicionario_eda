#ifndef AVL_HPP
#define AVL_HPP
#include <string>
#include <utility>
#include <stdexcept>
#include <algorithm>

//TODO: COMENTAR!!!!!!

template <typename Key, typename Value>
class AVL{
    private:
        //node
        struct Node{
            std::pair <Key, Value> tuple;
            int height;
            Node* left;
            Node* right;

            Node (Key k, Value v, int h, Node* l, Node* r) {
                tuple = std::make_pair(k, v);
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
        int height (Node* node);
        //funão que calcula o balance da arvore/subarvore
        int balance (Node* node);
        //função que rotaciona uma arvore/subarvore para direita
        Node* rightRotation (Node* p);
        //função que rotaciona uma arvore/subarvore para esquerda
        Node* leftRotation (Node* p);
        //insert
        //função que adiciona um nó sem desbalancear a arvore
        Node* _insert(Node *p , const Key& k, const Value& v);
        //função que conserta o balanço da arvore após uma inserção
        Node* fixup_insertion(Node *p, const Key& k);
        Value& _at(Node* p, const Key& k);
        const Value& _at(Node* p, const Key& k) const;

        //erase
        //função que remove um nó sem desbalancear a arvore
        Node* _erase(Node* p, const Key& k);

        Node* getMin(Node* p);
        //função que conserta o balanço da arvore após uma remoção
        Node* fixup_erase(Node* p);
        //contains
        //função booleana que recebe o primeiro nó da árvore e um determinado valor e verifica se este está na árvore
        bool _contains(Node* p, const Key& k);
        //clear
        //função privada que deleta os nos em pos ordem
        Node* _clear(Node* p);
        //empty
        //função que verifica se a arvore é vazia ou não
        bool _empty(Node *p);
        //size
        //função privada que retorna o quantidade de nos que a arvore possui
        int _size(Node *p);
        void bshow(Node *node, std::string heranca) const;

    public:
        //construtor
        AVL();
        //destrutor
        ~AVL();
        //função publica que insere um no
        void insert(const Key& k, const Value& v);
        //função que retorna o valor de um par baseado na chave
        Value& at(const Key& k);
        //função constante que retorna o valor de um par baseado na chave
        const Value& at(const Key& k) const;
        //função publica que apaga um no
        void erase(const Key& k);
        //função publica que retorna se um nó está ou não na árvore
        bool contains(const Key& k);
        //função publica que limpa a arvore
        void clear();
        //função publica que retorna se uma árvore é vazia ou não
        bool empty();
        //função publica que retorna quantos nós uma árvore possui
        int size();
        Value& operator[](const Key& k);
        const Value& operator[](const Key& k) const;
        void show();
        int getCountComparation();
        int getCountRotation();
};

#include "..\src\AVL.tpp"
#endif