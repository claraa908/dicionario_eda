#ifndef OHT_HPP
#define OHT_HPP
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <functional>

enum status{
    EMPTY,
    ACTIVE,
    DELETED
};

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class OHT{
    private:
        struct Node{
            std::pair<Key, Value> tuple;
            status n_status;

            Node() : tuple(), n_status(EMPTY){}

            Node(Key k, Value v){
                this->tuple = std::make_pair(k, v);
                n_status = ACTIVE;
            }
        };

        //variáveis da hash
        size_t numElem;
        float maxLoadFactor;
        size_t tableSize;
        Hash hashing;
        std::vector<Node> table;
        mutable int count_comp;
        mutable int count_collisions;
        mutable int count_rehash;

        //função que vai receber o tamanho da tabela e pegar o próximo valor primo mais próximo dele
        size_t get_next_prime(size_t x);
        int _contains(const Key& k);

        //funções de hashing duplo
        //função do primeiro hash que recebe uma chave e determina onde a inserção vai iniciar
        size_t hash1 (const Key& k) const;
        //função do segundo hash que determina quantos valores vão ser pulados na lista
        size_t hash2 (const Key& k) const;
        //Usa hashing duplo para calcular a posição de tentativa i para a chave k
        size_t compress(const Key& k, size_t i);
        
    public:
        OHT(size_t table_size = 10, float load_factor = 1.0);
        ~OHT();
        bool insert(const Key& k, const Value& v);
        Value& at(const Key& k);
        const Value& at(const Key& k) const;
        bool erase(const Key& k);
        bool contains(const Key& k);
        void clear();
        bool empty() const;
        size_t size() const;
        
        //funções da hash
        size_t num_slot() const;
        //função que retorna o slot de uma determinada chave
        size_t getSlot(const Key& k);
        float load_factor()const;
        float max_load_factor() const;
        void set_max_load_factor(float lf);
        void rehash(size_t m);
        void reserve(size_t n);
        Value& operator[](const Key& k);
        //sobrecarga do operador de colchetes constante
        const Value& operator[](const Key& k) const;
        void show();
        int getCountComparation();
        int getCountCollision();
        int getCountRehash();
};
#include "..\src\OHT.tpp"
#endif