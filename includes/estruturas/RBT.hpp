#ifndef RBT_HPP
#define RBT_HPP
#include <string>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <algorithm>

#define RED true
#define BLACK false

//TODO: COMENTAR!!!!!
template <typename Key, typename Value>
class RBT{
    private:
        //node
        struct Node{
            std::pair<Key,Value> tuple;
            bool color;
            Node* right;
            Node* left;
            Node* parent;
            
                Node(const Key& k, const Value& v, bool c, Node* r, Node* l, Node* p){
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
        Node* rightRotation(Node* x);
        Node* leftRotation(Node* x);
        void _insert(const Key& k, const Value& v);
        void fixup_insertion(Node* x);
        Value& _at(Node* p, const Key& k);
        const Value& _at(Node* p, const Key& k) const;
        void _erase(const Key& k);
        void delete_RB(Node* p);
        Node* minimum(Node* p);
        void fixup_erase(Node* x);
        bool _contains(const Key& k);
        Node* _clear(Node* p);
        bool _empty(Node* p);
        int _size(Node* p);
        void bshow(Node *node, std::string heranca);

    public:
        //construtor default
        RBT();
        //destrutor
        ~RBT();
        void insert(const Key& k, const Value& v);
        //função que retorna o valor de um par baseado na chave
        Value& at(const Key& k);
        //função constante que retorna o valor de um par baseado na chave
        const Value& at(const Key& k) const;
        void erase(const Key& k);
        bool contains(const Key& k);
        void clear();
        bool empty();
        int size();
        Value& operator[](const Key& k);
        const Value& operator[](const Key& k) const;
        void show();
        int getCountComparation();
        int getCountRecolor();
        int getCountRotation();
};
#include "..\src\RBT.tpp"
#endif