#include "..\..\includes\estruturas\OHT.hpp"
//TODO: DESTRUTOR!!!!!!!

//funções privadas
template <typename Key, typename Value, typename Hash>
size_t OHT<Key, Value, Hash>::get_next_prime(size_t x) {
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

template <typename Key, typename Value, typename Hash>
int OHT<Key, Value, Hash>::_contains(const Key& k){
    size_t i = 0;
    while(i < tableSize){
        size_t slot = compress(k, i);
        if(table[slot].n_status ==  EMPTY){
            return -1;
        }

        if(table[slot].n_status == ACTIVE && table[slot].tuple.first == k){
            count_comp++;
            return slot;
        }
        i++;
    }
    return -1;
}

template <typename Key, typename Value, typename Hash>
size_t OHT<Key, Value, Hash>::hash1 (const Key& k) const {
    return hashing(k) % tableSize;
}

template <typename Key, typename Value, typename Hash>
size_t OHT<Key, Value, Hash>::hash2 (const Key& k) const{
    return 1 + (k % tableSize-1);
}

template <typename Key, typename Value, typename Hash>
size_t OHT<Key, Value, Hash>::compress(const Key& k, size_t i){
    return (hash1(k) + i * hash2(k)) % tableSize;
}

//funções públicas
template <typename Key, typename Value, typename Hash>
OHT<Key, Value, Hash>::OHT(size_t table_size, float load_factor){
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
    count_rehash = 0;
}

template <typename Key, typename Value, typename Hash>
OHT<Key, Value, Hash>::~OHT() = default;

template <typename Key, typename Value, typename Hash>
bool OHT<Key, Value, Hash>::insert(const Key& k, const Value& v){
    if(load_factor() >= maxLoadFactor){
        rehash(2 * tableSize);
        count_rehash++;
    }

    int aux = _contains(k);
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
            count_collisions += i;
            return true;
        }
        i++;
    }

    count_collisions += i;
    throw std::overflow_error("tabela cheia");
}

template <typename Key, typename Value, typename Hash>
Value& OHT<Key, Value, Hash>::at(const Key& k){
    int aux = _contains(k);
    if(aux != -1){
        return table[aux].tuple.second;
    }
    throw std::invalid_argument("chave nao encontrada");
}

template <typename Key, typename Value, typename Hash>
const Value& OHT<Key, Value, Hash>::at(const Key& k) const{
    int aux = _contains(k);
    if(aux != -1){
        return table[aux].tuple.second;
    }
    throw std::invalid_argument("chave nao encontrada");
}

template <typename Key, typename Value, typename Hash>
bool OHT<Key, Value, Hash>::erase(const Key& k){
    int aux = _contains(k);
    if(aux != -1){
        table[aux].n_status = DELETED;
        numElem--;
        return true;
    }
    return false;
}

template <typename Key, typename Value, typename Hash>
bool OHT<Key, Value, Hash>::contains(const Key& k){
    return _contains(k) != -1 ? true : false;
}

template <typename Key, typename Value, typename Hash>
void OHT<Key, Value, Hash>::clear(){
    for(auto& node : table){
        node = Node();
    }
    numElem = 0;
}

template <typename Key, typename Value, typename Hash>
bool OHT<Key, Value, Hash>::empty() const{
    return numElem == 0;
}

template <typename Key, typename Value, typename Hash>
size_t OHT<Key, Value, Hash>::size() const{
    return numElem;
}

template <typename Key, typename Value, typename Hash>
size_t OHT<Key, Value, Hash>::num_slot() const{
    return tableSize;
}

template <typename Key, typename Value, typename Hash>
size_t OHT<Key, Value, Hash>::getSlot(const Key& k){
    int aux = _contains(k);
    if(aux == -1){
        throw std::invalid_argument("chave nao encontrada");
    }
    return aux;
}

template <typename Key, typename Value, typename Hash>
float OHT<Key, Value, Hash>::load_factor()const{
    return static_cast<float>(numElem) / tableSize;
}

template <typename Key, typename Value, typename Hash>
float OHT<Key, Value, Hash>::max_load_factor() const{
    return maxLoadFactor;
}

template <typename Key, typename Value, typename Hash>
void OHT<Key, Value, Hash>::set_max_load_factor(float lf){
    if(lf <= 0) {
        throw std::out_of_range("invalid load factor");
    }
    maxLoadFactor = lf;
    reserve(numElem);
}

template <typename Key, typename Value, typename Hash>
void OHT<Key, Value, Hash>::rehash(size_t m){
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

template <typename Key, typename Value, typename Hash>
void OHT<Key, Value, Hash>::reserve(size_t n){
    if(n > tableSize * maxLoadFactor){
        rehash( n / maxLoadFactor);
        count_rehash++;
    }
}

template <typename Key, typename Value, typename Hash>
Value& OHT<Key, Value, Hash>::operator[](const Key& k){
    if(load_factor() >= maxLoadFactor) {
        rehash(2 * tableSize);
        count_rehash++;
    }

    int aux = _contains(k);
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

template <typename Key, typename Value, typename Hash>
const Value& OHT<Key, Value, Hash>::operator[](const Key& k) const{
    return at(k);
}

template <typename Key, typename Value, typename Hash>
void OHT<Key, Value, Hash>::show(){
    if(empty()){
        std::cout << "'Hash sem elementos'";
    }else{
        bool first = true;
        for (int i = 0; i < tableSize; i++) {
            const auto& node = table[i];
            if(node.n_status == ACTIVE){
                if (!first) {
                std::cout << ", ";
                }
                std::cout << "slot " << i << ": (" << node.tuple.first << ": " << node.tuple.second << ")";
                    first = false;
            }
        }
        std::cout << std::endl;
    }
}

template <typename Key, typename Value, typename Hash>
int OHT<Key, Value, Hash>::getCountComparation(){
    return count_comp;
}

template <typename Key, typename Value, typename Hash>
int OHT<Key, Value, Hash>::getCountCollision(){
    return count_collisions;
}

template <typename Key, typename Value, typename Hash>
int OHT<Key, Value, Hash>::getCountRehash(){
    return count_rehash;
}