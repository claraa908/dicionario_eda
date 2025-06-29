#include "..\..\includes\estruturas\CHT.hpp"
//TODO: DESTRUTOR!!!!!!!!

//funções privadas
template <typename Key, typename Value, typename Hash>
size_t CHT<Key, Value, Hash>::get_next_prime(size_t x) {
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
size_t CHT<Key, Value, Hash>::compress(const Key& k) const {
    return hashing(k) % tableSize;
}



//funções públicas
template <typename Key, typename Value, typename Hash>
CHT<Key, Value, Hash>::CHT(size_t table_size, float load_factor){
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
CHT<Key, Value, Hash>::~CHT() = default;

template <typename Key, typename Value, typename Hash>
bool CHT<Key, Value, Hash>::insert(const Key& k, const Value& v){
    if(load_factor() >= max_load_factor()){
        rehash(2 * tableSize);
        count_rehash++;
    }

    size_t slot  = compress(k);
    bool colision = !table[slot].empty();
    for(auto& p : table[slot]){
        if(p.first == k){
            count_comp++;
            p.second = v;
            return false;
        }
    }

    if(colision){
        count_collisions++;
    }

    table[slot].push_back(std::make_pair(k, v));
    numElem++;
    return true;
}

template <typename Key, typename Value, typename Hash>
Value& CHT<Key, Value, Hash>::at(const Key& k){
    size_t slot = compress(k);

    for(auto& p : table[slot]){
        if(p.first == k){
            count_comp++;
            return p.second;
        }
    }
    throw std::invalid_argument("chave nao encontrada");
}

template <typename Key, typename Value, typename Hash>
const Value& CHT<Key, Value, Hash>::at(const Key& k) const{
    size_t slot = compress(k);

    for(const auto& p : table[slot]){
        if(p.first == k){
            count_comp++;
            return p.second;
        }
    }
    throw std::invalid_argument("chave nao encontrada");
}

template <typename Key, typename Value, typename Hash>
bool CHT<Key, Value, Hash>::erase(const Key& k){
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

template <typename Key, typename Value, typename Hash>
bool CHT<Key, Value, Hash>::contains(const Key& k){
    size_t slot = compress(k);
    for(auto p : table[slot]){
        if(p.first == k){
            count_comp++;
            return true;
        }
    }
    return false;
}

template <typename Key, typename Value, typename Hash>
void CHT<Key, Value, Hash>::clear(){
    for(size_t i = 0; i < tableSize; i++){
        table[i].clear();
    }
    numElem = 0;
}

template <typename Key, typename Value, typename Hash>
bool CHT<Key, Value, Hash>::empty() const{
    return numElem == 0;
}

template <typename Key, typename Value, typename Hash>
size_t CHT<Key, Value, Hash>::size() const{
    return numElem;
}

template <typename Key, typename Value, typename Hash>
size_t CHT<Key, Value, Hash>::num_slot() const{
    return tableSize;
}

template <typename Key, typename Value, typename Hash>
size_t CHT<Key, Value, Hash>::slot_size(size_t n) const{
    if(n >= tableSize){
        throw std::out_of_range("invalid index");
    }
    return table[n].size();
}

template <typename Key, typename Value, typename Hash>
size_t CHT<Key, Value, Hash>::getSlot(const Key& k) const{
    return compress(k);
}

template <typename Key, typename Value, typename Hash>
float CHT<Key, Value, Hash>::load_factor() const{
    return static_cast<float>(numElem) / tableSize;
}

template <typename Key, typename Value, typename Hash>
float CHT<Key, Value, Hash>::max_load_factor() const{
    return maxLoadFactor;
}

template <typename Key, typename Value, typename Hash>
void CHT<Key, Value, Hash>::set_max_load_factor(float lf){
    if(lf <= 0) {
        throw std::out_of_range("invalid load factor");
    }
    maxLoadFactor = lf;
    reserve(numElem);
}

template <typename Key, typename Value, typename Hash>
void CHT<Key, Value, Hash>::rehash(size_t m) {
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

template <typename Key, typename Value, typename Hash>
void CHT<Key, Value, Hash>::reserve(size_t n){
    if(n > tableSize * maxLoadFactor){
        rehash( n / maxLoadFactor);
        count_rehash++;
    }
}

template <typename Key, typename Value, typename Hash>
Value& CHT<Key, Value, Hash>::operator[](const Key& k){
    if(load_factor() >= maxLoadFactor) {
        rehash(2 * tableSize);
        count_rehash++;
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

template <typename Key, typename Value, typename Hash>
const Value& CHT<Key, Value, Hash>::operator[](const Key& k) const{
    return at(k);
}

template <typename Key, typename Value, typename Hash>
void CHT<Key, Value, Hash>::show(){
    if (empty()) {
        std::cout << "Hash sem elementos\n";
        return;
    }

    for (size_t i = 0; i < tableSize; i++) {
        std::cout << "slot " << i << ": ";
        if (table[i].empty()) {
            std::cout << "[]\n";
            continue;
        }

        bool first = true;
        for (const auto& p : table[i]) {
            if (!first) std::cout << " -> ";
            std::cout << "(" << p.first << ": " << p.second << ")";
            first = false;
        }
        std::cout << '\n';
    }
}

template <typename Key, typename Value, typename Hash>
int CHT<Key, Value, Hash>::getCountComparation(){
    return count_comp;
}

template <typename Key, typename Value, typename Hash>
int CHT<Key, Value, Hash>::getCountCollision(){
    return count_collisions;
}

template <typename Key, typename Value, typename Hash>
int CHT<Key, Value, Hash>::getCountRehash(){
    return count_rehash;
}