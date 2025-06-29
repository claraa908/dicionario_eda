#ifndef CHT_HPP
#define CHT_HPP
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <functional>

//TODO: COMENTAR!!!!!!

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class CHT{
    private:
        size_t numElem;
        float maxLoadFactor;
        size_t tableSize;
        Hash hashing;
        std::vector<std::list<std::pair<Key, Value>>> table;
        mutable int count_comp;
        mutable int count_collisions;
        mutable int count_rehash;


        size_t get_next_prime(size_t x);
        size_t compress(const Key& k) const;

    public:
        CHT(size_t table_size = 10, float load_factor = 1.0);
        ~CHT();
        bool insert(const Key& k, const Value& v);
        Value& at(const Key& k);
        const Value& at(const Key& k) const;
        bool erase(const Key& k);
        bool contains(const Key& k);
        void clear();
        bool empty() const;

        //função que retorna quantos elementos uma tabela possui no total, ou seja, seu tamanho
        size_t size() const;
        //função que retorna quantos slots tem disponivel na tabela hash
        size_t num_slot() const;
        //função que retorna quantos elementos estão dentro de um determinado slot
        size_t slot_size(size_t n) const;
        //função que retorna o slot de uma determinada chave
        size_t getSlot(const Key& k) const;
        float load_factor() const;
        float max_load_factor() const;
        void set_max_load_factor(float lf);
        void rehash(size_t m);
        void reserve(size_t n);
        Value& operator[](const Key& k);
        const Value& operator[](const Key& k) const;
        void show();
        int getCountComparation();
        int getCountCollision();
        int getCountRehash();
};

#include "..\..\src\estruturas\CHT.tpp"
#endif