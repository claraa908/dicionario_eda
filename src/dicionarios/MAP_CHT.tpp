#include "..\..\includes\dicionarios\MAP_CHT.hpp"

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
MAP_CHT<Key, Value, Hash, Compare, Equals>::MAP_CHT(size_t table_size, float load_factor, Hash hasher, Compare comp, Equals eq)
: c_hash(table_size, load_factor, hasher, comp, eq) {};

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
MAP_CHT<Key, Value, Hash, Compare, Equals>::~MAP_CHT() = default;

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
void MAP_CHT<Key, Value, Hash, Compare, Equals>::insert(Key k, Value v){
    if (contains(k)) {
        throw std::invalid_argument("Chave ja existe no dicionario");
    }
    c_hash.insert(k, v);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
void MAP_CHT<Key, Value, Hash, Compare, Equals>::update(Key k, Value newValue){
    if(!contains(k)){
        throw std::invalid_argument("Chave nao encontrada para atualizacao");
    }
    c_hash[k] = newValue;
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
Value& MAP_CHT<Key, Value, Hash, Compare, Equals>::at(const Key& k){
    return c_hash.at(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
const Value& MAP_CHT<Key, Value, Hash, Compare, Equals>::at(const Key& k) const{
    return c_hash.at(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
void MAP_CHT<Key, Value, Hash, Compare, Equals>::erase(Key k){
    c_hash.erase(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
bool MAP_CHT<Key, Value, Hash, Compare, Equals>::contains(Key k){
    return c_hash.contains(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
int MAP_CHT<Key, Value, Hash, Compare, Equals>::size(){
    return c_hash.size();
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
void MAP_CHT<Key, Value, Hash, Compare, Equals>::clear(){
    c_hash.clear();
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
void MAP_CHT<Key, Value, Hash, Compare, Equals>::show(){
    c_hash.show();
    std::cout << std::endl;
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
const Value& MAP_CHT<Key, Value, Hash, Compare, Equals>::operator[](const Key& k) const{
    if(!c_hash.contains(k)){
        throw std::invalid_argument("chave inexistente");
    }
    return c_hash.at(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
Value& MAP_CHT<Key, Value, Hash, Compare, Equals>::operator[](const Key& k){
    if(!c_hash.contains(k)){
        c_hash.insert(k, Value());
    }
    return c_hash.at(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
std::vector<std::pair<Key, Value>> MAP_CHT<Key, Value, Hash, Compare, Equals>::toVector() const{ 
    return c_hash.toVector();
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
std::string MAP_CHT<Key, Value, Hash, Compare, Equals>::metric(){
    std::string value = "";
    value += "Contagem de comparacoes de chaves realizadas: ";
    value += std::to_string(c_hash.getCountComparation());
    value += "\nContagem de colisoes realizadas: ";
    value += std::to_string(c_hash.getCountCollision());
    value += "\nContagem de rehashes realizados: ";
    value += std::to_string(c_hash.getCountRehash());
    return value;
}