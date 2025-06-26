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
    struct Node{
        std::pair<Key, Value> tuple;
        status n_status;

        Node() : tuple(), n_status(EMPTY){}

        Node(Key k, Value v){
            this->tuple = std::make_pair(k, v);
            n_status = ACTIVE;
        }
    };

    private:
    //variáveis da hash
    size_t numElem;
    float maxLoadFactor;
    size_t tableSize;
    Hash hashing;
    std::vector<Node> table;
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

    //funções de hashing duplo

    //função do primeiro hash que recebe uma chave e determina onde a inserção vai iniciar
    size_t hash1 (const Key& k) const {
        return hashing(k) % tableSize;
    }


    //função do segundo hash que determina quantos valores vão ser pulados na lista
    size_t hash2 (const Key& k) const{
        return 1 + (k % tableSize-1);
    }

    //Usa hashing duplo para calcular a posição de tentativa i para a chave k
    size_t compress(const Key& k, size_t i){
        return (hash1(k) + i * hash2(k)) % tableSize;
    }

    public:
    OHT(size_t table_size = 10, float load_factor = 1.0){
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

    bool insert(const Key& k, const Value& v){
        if(loadFactor() >= maxLoadFactor){
            rehash(2 * tableSize);
        }

        int aux = contains(k);
        if(aux != -1){
            table[aux].tuple.second = v;
            return false;
        }

        size_t i = 0;
        while(i < tableSize){
            size_t slot = compress(k, i);
            if(table[slot].n_status != ACTIVE){
                table[slot] = Node(k, v);
                numElem++;
                return true;
            }
            count_collisions++;
            i++;
        }

        throw std::overflow_error("tabela cheia");
    }

    Value& at(const Key& k){
        int aux = contains(k);
        if(aux != -1){
            return table[aux].tuple.second;
        }
        throw std::invalid_argument("chave nao encontrada");
    }

    const Value& at(const Key& k) const{
        int aux = contains(k);
        if(aux != -1){
            return table[aux].tuple.second;
        }
        throw std::invalid_argument("chave nao encontrada");
    }

    bool erase(){

    }

    int contains(Key& k){
        size_t i = 0;
        while(i < tableSize){
            size_t slot = compress(k, i);
            if(table[slot].n_status ==  EMPTY){
                count_comp++;
                return -1;
            }

            if(table[slot].n_status == ACTIVE && table[slot].tuple.first == k){
                count_comp++;
                return slot;
            }
            i++;
            count_comp++;
        }
        return -1;
    }

    void clear(){
        for(auto& node : table){
            node = Node();
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
    size_t num_slot() const{
        return tableSize;
    }

    //função que retorna o slot de uma determinada chave
    size_t getSlot(const Key& k) const{
        return compress(k);
    }

    float loadFactor()const{
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

    void rehash(size_t m){
        size_t newTableSize = get_next_prime(m);
        if(newTableSize > tableSize) {
            std::vector<Node> old_vector = table;
            tableSize = newTableSize;
            table = std::vector<Node>(newTableSize);
            numElem = 0;

            for(const auto& node : old_vector) {
                if(node.n_status ==  ACTIVE){
                    insert(node.tuple.first, node.tuple.second);
                }  
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

        int aux = contains(k);
        if(aux != -1){
            return table[aux].tuple.second;
        }

        size_t i = 0;
        while(i < tableSize){
            size_t slot = compress(k, i);
            if(table[slot].n_status != ACTIVE){
                table[slot] = Node(k, Value());
                numElem++;
                return table[slot].tuple.second;
            }
            i++;
        }
        throw std::overflow_error("tabela cheia");
    }

    //sobrecarga do operador de colchetes constante
    const Value& operator[](const Key& k) const{
        return at(k);
    }

    void show(){
        if(empty()){
            std::cout << "'Hash sem elementos'";
        }else{
            bool first = true;
            for (const auto& node : table) {
                if(node.n_status == ACTIVE){
                    if (!first) {
                    std::cout << ", ";
                    }
                    std::cout << "(" << node.tuple.first << ": " << node.tuple.second << ")";
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