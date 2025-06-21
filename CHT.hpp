#ifndef CHT_HPP
#define CHT_HPP
#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <functional>

template <typename Key, typename Value, typename Hash = std::hash<Key>>

class CHT{
    private:
    //variáveis
    size_t numElem;
    size_t maxLoadFactor;
    size_t tableSize;
    Hash hashing;
    std::vector<std::list<std::pair<Key, Value>>> table;

    //função que vai receber o tamanho da tabela e pegar o próximo valor primo mais próximo dele
    size_t get_next_prime(size_t x) {
        if(x <= 2) return 3;
        x = (x % 2 == 0) ? x + 1 : x;
        bool not_prime = true;
        while(not_prime) {
            not_prime = false;
            for(int i = 3; i <= sqrt(x); i+=2) {
                if(x % i == 0) {
                    not_prime = true;
                    break;
                }
            }
            x += 2;
        }
        return x - 2;
    }

    //função de compressão da hash, por meio do módulo do código do hash code e do tamanho da tabela 
    //ela define para onde um determinado dado vai dentro da tabela
    size_t compress(const Key& k) const {
        return hashing(k) % tableSize;
    }

    public:
    //construtor 
    CHT(size_t table_size, float load_factor = 1.0){
        numElem = 0;
        tableSize = get_next_prime(table_size);
        table.resize(tableSize);
        if(load_factor <= 0) {
            maxLoadFactor = 1.0;
        } else {
            maxLoadFactor = load_factor;
        }
    }

    //funções gerais
    bool insert(const Key& k, const Value& v){
        if(load_factor() >= max_load_factor){
            rehash(2 * tableSize);
        }

        size_t slot  = compress(k);
        for(auto p : table[slot]){
            if(p.first == k){
                return false;
            }
        }

        table[slot].push_back(std::make_pair(k, v));
        numElem++;
        return true;
    }

    bool erase(const Key& k){
        size_t slot = compress(k);
        for(size_t it = table[slot].begin(); it != table[slot].end(); it++){
            if(it.first == k){
                table[slot].erase(it);
                numElem--;
                return true;
            }
        }
        return false;
    }

    bool contains(const Key& k){
        size_t slot = compress(k);

        for(auto p : table[slot]){
            if(p.first == k){
                return true;
            }
        }

        return false;
    }

    void clear(){
        for(size_t i = 0; i < tableSize; i++){
            table[i].clear();
        }
        numElem = 0;
    }

    bool empty() const{
        return numElem == 0;
    }

    size_t size() const{
        return numElem;
    }

    //funções da hash

    //retorna quantos slots tem disponivel na tabela hash
    size_t num_slot() const{
        return tableSize;
    }

    //retorna quantos elementos estão dentro de um determinado slot
    size_t slot_size(size_t n) const{
        if(n >= tableSize){
            throw std::out_of_range("invalid index");
        }
        return table[n].size();
    }

    //função que retorna o slot de uma determinada chave
    size_t getSlot(const Key& k) const{
        return compress(k);
    }

    float load_factor() const{
        return static_cast<float>(numElem) / tableSize;
    }

    float max_load_factor() const{
        return maxLoadFactor;
    }

    void set_max_load_factor(float lf){
        if(lf <= 0) {
            throw std::out_of_range("invalid load factor");
        }
        maxLoadFactor = lf;
        reserve(numElem);
    }

    Value& at(const Key& k){
        size_t slot = compress(k);

        for(auto p = table[slot]){
            if(p.first == k){
                return p.second;
            }
        }

        throw std::invalid_argument();
    }

    const Value& at(const Key& k) const{
        size_t slot = compress(k);

        for(auto p = table[slot]){
            if(p.first == k){
                return p.second;
            }
        }

        throw std::invalid_argument();
    }

    void rehash(size_t m) {
        size_t newTableSize = get_next_prime(m);
        if(newTableSize > tableSize) {
            std::vector<std::list<std::pair<Key,Value>>> old_vec;
            old_vec = table; 
            table.clear();
            table.resize(newTableSize);
            numElem = 0;
            tableSize = newTableSize;
            for(size_t i = 0; i < old_vec.size(); ++i) {
                for(auto& par : old_vec[i]) {
                    add(par.first, par.second);
                }
                old_vec[i].clear();
            }            
        }
    }

    void reserve(size_t n){
        if(n > tableSize * maxLoadFactor){
            rehash( n / maxLoadFactor);
        }
    }

    Value& operator[](const Key& k){
        if(load_factor() >= maxLoadFactor) {
            rehash(2 * tableSize);
        }
        size_t slot = hash_code(k);
        for(auto& par : table[slot]) {
            if(par.first == k) {
                return par.second;
            }
        }
        table[slot].push_back({k, Value()});
        numElem++;
        return table[slot].back().second;
    }

    const Value& operator[](const Key& k) const{
        return at(k);
    }
};

#endif