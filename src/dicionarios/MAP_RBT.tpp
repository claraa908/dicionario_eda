#include "..\..\includes\dicionarios\MAP_RBT.hpp"

template <typename Key, typename Value, typename Compare, typename Equals>
MAP_RBT<Key, Value, Compare, Equals>::MAP_RBT() : rbt_tree(){};

template <typename Key, typename Value, typename Compare, typename Equals>
MAP_RBT<Key, Value, Compare, Equals>::MAP_RBT(Compare comp, Equals eq_comp) : rbt_tree(comp, eq_comp){};

template <typename Key, typename Value, typename Compare, typename Equals>
MAP_RBT<Key, Value, Compare, Equals>::~MAP_RBT() = default;

template <typename Key, typename Value, typename Compare, typename Equals>
void MAP_RBT<Key, Value, Compare, Equals>::insert(Key k, Value v){
    if (contains(k)) {
        throw std::invalid_argument("Chave ja existe no dicionario");
    }
    rbt_tree.insert(k, v); 
}

template <typename Key, typename Value, typename Compare, typename Equals>
void MAP_RBT<Key, Value, Compare, Equals>::update(Key k, Value newValue){
    if(!contains(k)){
        throw std::invalid_argument("Chave nao encontrada para atualizacao");
    }
    rbt_tree[k] = newValue;
}

template <typename Key, typename Value, typename Compare, typename Equals>
Value& MAP_RBT<Key, Value, Compare, Equals>::at(const Key& k){
    return rbt_tree.at(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
const Value& MAP_RBT<Key, Value, Compare, Equals>::at(const Key& k) const{
    return rbt_tree.at(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
void MAP_RBT<Key, Value, Compare, Equals>::erase(const Key& k){
    if(empty()){
        throw std::runtime_error("Dicionario vazio, nao ha o que remover");
    }
    if(!contains(k)){
        throw std::invalid_argument("Chave nao encontrada para remocao");
    }
    rbt_tree.erase(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
bool MAP_RBT<Key, Value, Compare, Equals>::contains(const Key& k){
    return rbt_tree.contains(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
int MAP_RBT<Key, Value, Compare, Equals>::size(){
    return rbt_tree.size();
}

template <typename Key, typename Value, typename Compare, typename Equals>
void MAP_RBT<Key, Value, Compare, Equals>::clear(){
    if(empty()){
        throw std::runtime_error("Dicionario vazio, nao ha o que limpar");
    }
    rbt_tree.clear();
}

template <typename Key, typename Value, typename Compare, typename Equals>
bool MAP_AVL<Key, Value, Compare, Equals>::empty(){
    return rbt_tree.empty();
}

template <typename Key, typename Value, typename Compare, typename Equals>
void MAP_RBT<Key, Value, Compare, Equals>::show(){
    rbt_tree.show();
    std::cout << std::endl;
}

template <typename Key, typename Value, typename Compare, typename Equals>
const Value& MAP_RBT<Key, Value, Compare, Equals>::operator[](const Key& k) const{
    if(!rbt_tree.contains(k)){
        throw std::invalid_argument("chave inexistente");
    }
    return rbt_tree.at(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
Value& MAP_RBT<Key, Value, Compare, Equals>::operator[](const Key& k){
    if(!rbt_tree.contains(k)){
        rbt_tree.insert(k, Value());
    }
    return rbt_tree.at(k);
}

template <typename Key, typename Value, typename Compare, typename Equals>
std::vector<std::pair<Key, Value>> MAP_RBT<Key, Value, Compare, Equals>::toVector() const{ 
    return rbt_tree.inOrder();
}

template <typename Key, typename Value, typename Compare, typename Equals>
std::string MAP_RBT<Key, Value, Compare, Equals>::metric() {
    std::string value = "";
    value += "Contagem de comparacoes de chaves realizadas: ";
    value += std::to_string(rbt_tree.getCountComparation());
    value += "\nContagem de rotacoes realizadas: ";
    value += std::to_string(rbt_tree.getCountRotation());
    value += "\nContagem de recoloracoes realizadas: ";
    value += std::to_string(rbt_tree.getCountRecolor());
    return value;
}