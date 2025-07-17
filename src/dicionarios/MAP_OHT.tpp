#include "..\..\includes\dicionarios\MAP_OHT.hpp"

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
MAP_OHT<Key, Value, Hash, Compare, Equals>::MAP_OHT(size_t table_size, float load_factor, Hash hasher, Compare comp, Equals eq)
: o_hash(table_size, load_factor, hasher, comp, eq) {};

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
MAP_OHT<Key, Value, Hash, Compare, Equals>::~MAP_OHT() = default;

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
void MAP_OHT<Key, Value, Hash, Compare, Equals>::insert(Key k, Value v){
    if (contains(k)) {
        throw std::invalid_argument("Chave ja existe no dicionario");
    }
    o_hash.insert(k, v);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
void MAP_OHT<Key, Value, Hash, Compare, Equals>::update(Key k, Value newValue){
    if(!contains(k)){
        throw std::invalid_argument("Chave nao encontrada para atualizacao");
    }
    o_hash[k] = newValue;
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
Value& MAP_OHT<Key, Value, Hash, Compare, Equals>::at(const Key& k){
    return o_hash.at(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
const Value& MAP_OHT<Key, Value, Hash, Compare, Equals>::at(const Key& k) const{
    return o_hash.at(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
void MAP_OHT<Key, Value, Hash, Compare, Equals>::erase(Key k){
    if(empty()){
        throw std::runtime_error("Dicionario vazio, nao ha o que remover");
    }
    if(!contains(k)){
        throw std::invalid_argument("Chave nao encontrada para remocao");
    }
    o_hash.erase(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
bool MAP_OHT<Key, Value, Hash, Compare, Equals>::contains(Key k){
    return o_hash.contains(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
int MAP_OHT<Key, Value, Hash, Compare, Equals>::size(){
    return o_hash.size();
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
void MAP_OHT<Key, Value, Hash, Compare, Equals>::clear(){
    if(empty()){
        throw std::runtime_error("Dicionario vazio, nao ha o que limpar");
    }
    o_hash.clear();
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
bool MAP_OHT<Key, Value, Hash, Compare, Equals>::empty(){
    return o_hash.empty();
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
void MAP_OHT<Key, Value, Hash, Compare, Equals>::show(){
    o_hash.show();
    std::cout << std::endl;
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
const Value& MAP_OHT<Key, Value, Hash, Compare, Equals>::operator[](const Key& k) const{
    if(!o_hash.contains(k)){
        throw std::invalid_argument("chave inexistente");
    }
    return o_hash.at(k);
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
Value& MAP_OHT<Key, Value, Hash, Compare, Equals>::operator[](const Key& k){
    if(!o_hash.contains(k)){
        o_hash.insert(k, Value());
    }
    return o_hash.at(k);
}


template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
std::vector<std::pair<Key, Value>> MAP_OHT<Key, Value, Hash, Compare, Equals>::toVector() const{

    return o_hash.toVector();
}

template <typename Key, typename Value, typename Hash, typename Compare, typename Equals>
std::string MAP_OHT<Key, Value, Hash, Compare, Equals>::metric() const{
    std::string value = "";
    value += "Contagem de comparacoes de chaves realizadas: ";
    value += std::to_string(o_hash.getCountComparation());
    value += "\nContagem de colisoes realizadas: ";
    value += std::to_string(o_hash.getCountCollision());
    value += "\nContagem de rehashes realizados: ";
    value += std::to_string(o_hash.getCountRehash());
    return value;
}