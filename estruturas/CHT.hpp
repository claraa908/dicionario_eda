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

template <typename Key, typename Value, typename Hash = std::hash<Key>>

class CHT{
    private:
    //variáveis
    size_t numElem;
    float maxLoadFactor;
    size_t tableSize;
    Hash hashing;
    std::vector<std::list<std::pair<Key, Value>>> table;
    mutable int count_comp;
    mutable int count_collisions;

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
    CHT(size_t table_size = 10, float load_factor = 1.0){
        numElem = 0;
        tableSize = get_next_prime(table_size);
        table.resize(tableSize);
        if(load_factor <= 0) {
            maxLoadFactor = 1.0;
        } else {
            maxLoadFactor = load_factor;
        }
        count_comp = 0;
        count_collisions = 0;
    }

    //funções gerais

    //função que vai fazer uma busca na tabela para ver se encontra a chave k, caso já exista na tabela retorna falso
    //caso não exista adiciona o par na tabela e retorna verdadeiro
    bool insert(const Key& k, const Value& v){
        if(load_factor() >= max_load_factor()){
            rehash(2 * tableSize);
        }

        size_t slot  = compress(k);
        bool colision = false;
        for(auto& p : table[slot]){
            if(p.first == k){
                count_comp++;
                p.second = v;
                return false;
            }
            colision = true; 
        }

        if(colision){
            count_collisions++;
        }

        table[slot].push_back(std::make_pair(k, v));
        numElem++;
        return true;
    }

    //função que retorna o valor de um par baseado na chave
    Value& getValue(const Key& k){
        size_t slot = compress(k);

        for(auto& p : table[slot]){
            if(p.first == k){
                count_comp++;
                return p.second;
            }
        }
        throw std::invalid_argument("chave nao encontrada");
    }

    //função constante que retorna o valor de um par baseado na chave
    const Value& getValue(const Key& k) const{
        size_t slot = compress(k);

        for(const auto& p : table[slot]){
            if(p.first == k){
                count_comp++;
                return p.second;
            }
        }
        throw std::invalid_argument("chave nao encontrada");
    }

    //função que recebe uma chave k faz a busca na tabela e caso exista exclui o par e retorna verdadeiro
    //caso não exista retorna falso
    bool erase(const Key& k){
        size_t slot = compress(k);
        for(auto it = table[slot].begin(); it != table[slot].end(); it++){
            if(it->first == k){
                count_comp++;
                table[slot].erase(it);
                numElem--;
                return true;
            }
        }
        return false;
    }

    //função que diz se um par de chave k existe ou não na tabela
    bool contains(const Key& k){
        size_t slot = compress(k);

        for(auto p : table[slot]){
            if(p.first == k){
                count_comp++;
                return true;
            }
        }

        return false;
    }

    //função que limpa todas listas de cada slot na tabela
    void clear(){
        for(size_t i = 0; i < tableSize; i++){
            table[i].clear();
        }
        numElem = 0;
    }

    //função que verifica se a tabela possui ou não elementos
    bool empty() const{
        return numElem == 0;
    }

    //função que retorna quantos elementos uma tabela possui no total, ou seja, seu tamanho
    size_t size() const{
        return numElem;
    }

    //funções da hash

    //função que retorna quantos slots tem disponivel na tabela hash
    size_t num_slot() const{
        return tableSize;
    }

    //função que retorna quantos elementos estão dentro de um determinado slot
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
                    insert(par.first, par.second);
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

    //sobrecarga do operador de colchetes, permitindo a criação de hash no formato de Hash[chave] = valor
    Value& operator[](const Key& k){
        if(load_factor() >= maxLoadFactor) {
            rehash(2 * tableSize);
        }
        size_t slot = compress(k);
        for(auto& par : table[slot]) {
            if(par.first == k) {
                count_comp++;
                return par.second;
            }
        }
        table[slot].push_back({k, Value()});
        numElem++;
        return table[slot].back().second;
    }

    //sobrecarga do operador de colchetes constante
    const Value& operator[](const Key& k) const{
        return getValue(k);
    }

    void show(){
        if(empty()){
            std::cout << "'Hash sem elementos'";
        }else{
            bool first = true;
            for (size_t i = 0; i < tableSize; i++) {
                for (const auto& p : table[i]) {
                    if (!first) {
                        std::cout << ", ";
                    }
                    std::cout << "(" << p.first << ": " << p.second << ")";
                    first = false;
                }
            }
        }
    }
    int getCountComparation(){
        return count_comp;
    }

    int getCountCollision(){
        return count_collisions;
    }
};

#endif