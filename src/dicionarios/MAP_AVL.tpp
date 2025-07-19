#include "../../includes/dicionarios/MAP_AVL.hpp"

template <typename Key, typename Value, typename Compare, typename Equals>
MAP_AVL<Key, Value, Compare, Equals>::MAP_AVL() : avl_tree(){};

template <typename Key, typename Value, typename Compare, typename Equals>
MAP_AVL<Key, Value, Compare, Equals>::~MAP_AVL() = default;

template <typename Key, typename Value, typename Compare, typename Equals>
void MAP_AVL<Key, Value, Compare, Equals>::insert(Key k, Value v){
    if (contains(k)) {
        throw std::invalid_argument("Chave ja existe no dicionario");
    }
    avl_tree.insert(k, v);
}

template <typename Key, typename Value, typename Compare, typename Equals>
void MAP_AVL<Key, Value, Compare, Equals>::update(Key k, Value newValue){
    if(!contains(k)){
        throw std::invalid_argument("Chave nao encontrada para atualizacao");
    }
    avl_tree[k] = newValue;
}

template <typename Key, typename Value, typename Compare, typename Equals>
Value& MAP_AVL<Key, Value, Compare, Equals>::at(const Key& k){
    return avl_tree.at(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
const Value& MAP_AVL<Key, Value, Compare, Equals>::at(const Key& k) const{
    return avl_tree.at(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
void MAP_AVL<Key, Value, Compare, Equals>::erase(const Key& k){
    if(empty()){
        throw std::runtime_error("Dicionario vazio, nao ha o que remover");
    }
    if(!contains(k)){
        throw std::invalid_argument("Chave nao encontrada para remocao");
    }

    avl_tree.erase(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
bool MAP_AVL<Key, Value, Compare, Equals>::contains(const Key& k){
    return avl_tree.contains(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
int MAP_AVL<Key, Value, Compare, Equals>::size(){
    return avl_tree.size();
}

template <typename Key, typename Value, typename Compare, typename Equals>
void MAP_AVL<Key, Value, Compare, Equals>::clear(){
    if(empty()){
        throw std::runtime_error("Dicionario vazio, nao ha o que limpar");
    }
    avl_tree.clear();
}

template <typename Key, typename Value, typename Compare, typename Equals>
bool MAP_AVL<Key, Value, Compare, Equals>::empty(){
    return avl_tree.empty();
}

template <typename Key, typename Value, typename Compare, typename Equals>
void MAP_AVL<Key, Value, Compare, Equals>::show(){
    avl_tree.show();
}

template <typename Key, typename Value, typename Compare, typename Equals>
const Value& MAP_AVL<Key, Value, Compare, Equals>::operator[](const Key& k) const{
    if(!avl_tree.contains(k)){
        throw std::invalid_argument("chave inexistente");
    }
    return avl_tree.at(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
Value& MAP_AVL<Key, Value, Compare, Equals>::operator[](const Key& k){
    if(!avl_tree.contains(k)){
        avl_tree.insert(k, Value());
    }
    return avl_tree.at(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
std::vector<std::pair<Key, Value>> MAP_AVL<Key, Value, Compare, Equals>::toVector() const{ 
    return avl_tree.toVector();
}

template <typename Key, typename Value, typename Compare, typename Equals>
std::string MAP_AVL<Key, Value, Compare, Equals>::metric() const{
    std::string value = "";
    value += "Contagem de comparacoes de chaves realizadas: ";
    value += std::to_string(avl_tree.getCountComparation());
    value += "\nContagem de rotacoes realizadas: ";
    value += std::to_string(avl_tree.getCountRotation());
    return value;
}