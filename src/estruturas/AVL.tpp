#include "..\..\includes\estruturas\AVL.hpp"
//funções privadas

template<typename Key, typename Value, typename Compare, typename Equals>
int AVL<Key, Value, Compare, Equals>::height (typename AVL<Key, Value, Compare, Equals>::Node* node){
    return (_empty(node)) ? 0 : node->height;
}

template<typename Key, typename Value, typename Compare, typename Equals>
int AVL<Key, Value, Compare, Equals>::balance (typename AVL<Key, Value, Compare, Equals>::Node* node){
    return height(node->right) - height(node->left);
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename AVL<Key, Value, Compare, Equals>::Node* AVL<Key, Value, Compare, Equals>::rightRotation (typename AVL<Key, Value, Compare, Equals>::Node* p){
    Node* u = p->left;
    p->left = u->right;
    u->right = p;

    p->height = 1 +  std::max(height(p->left), height(p->right));
    u->height = 1 +  std::max(height(u->left), height(u->right));
    return u;
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename AVL<Key, Value, Compare, Equals>::Node* AVL<Key, Value, Compare, Equals>::leftRotation (typename AVL<Key, Value, Compare, Equals>::Node* p){
    Node* u = p->right;
    p->right = u->left;
    u->left = p;

    p->height = 1 +  std::max(height(p->left), height(p->right));
    u->height = 1 +  std::max(height(u->left), height(u->right));
    return u;
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename AVL<Key, Value, Compare, Equals>::Node* AVL<Key, Value, Compare, Equals>::_insert(typename AVL<Key, Value, Compare, Equals>::Node* p , const Key& k, const Value& v){
    if(_empty(p)){
        return new Node{k, v, 1, nullptr, nullptr};
    }
    
    if(equal(k, p->tuple.first)){
        count_comp++;
        p->tuple.second = v;
        return p;
    }
    if(less(k, p->tuple.first)){
        count_comp += 2;
        p->left = _insert(p->left, k, v);
    }
    else if(!less(k, p->tuple.first)){
        count_comp += 3;
        p->right = _insert(p->right, k, v);
    }
    p = fixup_insertion(p, k);
    return p;
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename AVL<Key, Value, Compare, Equals>::Node* AVL<Key, Value, Compare, Equals>::fixup_insertion(typename AVL<Key, Value, Compare, Equals>::Node* p, const Key& k){
    int bal = balance(p);
    if(bal < -1){
        if(less(k, p->left->tuple.first)){
            count_comp++;
            count_rotation++;
            return rightRotation(p);
        }
        if(!less(k, p->left->tuple.first)){
            count_comp += 2;
            count_rotation += 2;
            p->left = leftRotation(p->left);
            return rightRotation(p);
        }
    }
    if(bal > 1){
        if(!less(k, p->right->tuple.first)){
            count_comp++;
            count_rotation++;
            return leftRotation(p);
        }
        if(less(k, p->right->tuple.first)){
            count_comp += 2;
            count_rotation += 2;
            p->right = rightRotation(p->right);
            return leftRotation(p);
        }
    }
    p->height = 1 + std::max(height(p->left), height(p->right));
    return p;
}

template<typename Key, typename Value, typename Compare, typename Equals>
Value& AVL<Key, Value, Compare, Equals>::_at(typename AVL<Key, Value, Compare, Equals>::Node* p, const Key& k){
    if(p == nullptr){
        throw std::invalid_argument("chave nao encontrada na arvore");
    }
    if(equal(k, p->tuple.first)){
        count_comp++;
        return p->tuple.second;
    }else if(less(k, p->tuple.first)){
        count_comp += 2;
        return _at(p->left, k);
    }else{
        count_comp += 3;
        return _at(p->right, k);
    }
}

template<typename Key, typename Value, typename Compare, typename Equals>
const Value& AVL<Key, Value, Compare, Equals>::_at(typename AVL<Key, Value, Compare, Equals>::Node* p, const Key& k) const {
    if (p == nullptr) {
        throw std::invalid_argument("chave nao encontrada na arvore");
    }

    if (equal(k, p->tuple.first)) {
        count_comp++;
        return p->tuple.second;
    } else if (less(k, p->tuple.first)) {
        count_comp += 2;
        return _at(p->left, k);
    } else {
        count_comp += 3;
        return _at(p->right, k);
    }
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename AVL<Key, Value, Compare, Equals>::Node* AVL<Key, Value, Compare, Equals>::_erase(typename AVL<Key, Value, Compare, Equals>::Node* p, const Key& k){
    if(_empty(p)){
        return nullptr;
    }
    if(less(k, p->tuple.first)){
        count_comp++;
        p->left = _erase(p->left, k);
    } else if(!less(k, p->tuple.first)){
        count_comp += 2;
        p->right = _erase(p->right, k);
    } else {
        if(p->left == nullptr){
            Node* aux = p->right;
            delete p;
            return aux;
        } else if(p->right == nullptr){
            Node* aux = p->left;
            delete p;
            return aux;
        } else {
            Node* suc = minimum(p->right);
            p->tuple = suc->tuple;
            p->right = _erase(p->right, suc->tuple.first);
        }
    }

    p->height = 1 + std::max(height(p->left), height(p->right));
    return fixup_erase(p);
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename AVL<Key, Value, Compare, Equals>::Node* AVL<Key, Value, Compare, Equals>::minimum(typename AVL<Key, Value, Compare, Equals>::Node* p){
    while(p->left != nullptr){
        p = p->left;
    }
    return p;
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename AVL<Key, Value, Compare, Equals>::Node* AVL<Key, Value, Compare, Equals>::fixup_erase(typename AVL<Key, Value, Compare, Equals>::Node* p){
    int bal = balance(p);
    if(bal < -1 && balance(p->left) <= 0){
        count_rotation++;
        return rightRotation(p);
    }
    if(bal < -1 && balance(p->left) > 0){
        count_rotation += 2;
        p->left = leftRotation(p->left);
        return rightRotation(p);
    }
    if(bal > 1 && balance(p->right) >= 0){
        count_rotation++;
        return leftRotation(p);
    }
    if(bal > 1 && balance(p->right) < 0){
        count_rotation += 2;
        p->right = rightRotation(p->right);
        return leftRotation(p);
    }
    p->height = 1 + std::max(height(p->left), height(p->right));
    return p;
}

template<typename Key, typename Value, typename Compare, typename Equals>
bool AVL<Key, Value, Compare, Equals>::_contains(typename AVL<Key, Value, Compare, Equals>::Node* p, const Key& k){
    if(_empty(p)){
        return false;
    }
    if(equal(k, p->tuple.first)){
        count_comp++;
        return true;
    }

    if(less(k, p->tuple.first)){
        count_comp += 2;
        return _contains(p->left, k);
    }else{
        count_comp += 3;
        return _contains(p->right, k);
    }
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename AVL<Key, Value, Compare, Equals>::Node* AVL<Key, Value, Compare, Equals>::_clear(typename AVL<Key, Value, Compare, Equals>::Node* p){
    if(p != nullptr){
        p->left = _clear(p->left);
        p->right = _clear(p->right);
        delete p;
    }
    return nullptr;
}

template<typename Key, typename Value, typename Compare, typename Equals>
bool AVL<Key, Value, Compare, Equals>::_empty(AVL<Key, Value, Compare, Equals>::Node* p){
    return p == nullptr;
}

template<typename Key, typename Value, typename Compare, typename Equals>
int AVL<Key, Value, Compare, Equals>::_size(AVL<Key, Value, Compare, Equals>::Node* p){
    if(_empty(p)){
        return 0;
    }

    return 1 + _size(p->left) + _size(p->right);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void AVL<Key, Value, Compare, Equals>::bshow(AVL<Key, Value, Compare, Equals>::Node* node, std::string heranca) const {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < static_cast<int>(heranca.size()) - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "|   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "|--" : "|--");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->tuple.first << ": " << node->tuple.second<< std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}

template<typename Key, typename Value, typename Compare, typename Equals>
void AVL<Key, Value, Compare, Equals>::_toVector(AVL<Key, Value, Compare, Equals>::Node* p, std::vector<std::pair<Key, Value>>& v) const{
    if(p != nullptr){
        _toVector(p->left, v);
        v.push_back({p->tuple.first, p->tuple.second});
        _toVector(p->right, v);
    }
}


//funções públicas
template<typename Key, typename Value, typename Compare, typename Equals>
AVL<Key, Value, Compare, Equals>::AVL() {
    root = nullptr;
    count_comp = 0;
    count_rotation = 0;
    less = Compare();
    equal = Equals();
}

template<typename Key, typename Value, typename Compare, typename Equals>
AVL<Key, Value, Compare, Equals>::~AVL(){
    root = _clear(root);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void AVL<Key, Value, Compare, Equals>::insert(const Key& k, const Value& v){
    root = _insert(root, k, v);
}

template<typename Key, typename Value, typename Compare, typename Equals>
Value& AVL<Key, Value, Compare, Equals>::at(const Key& k){
    if(root == nullptr){
        throw std::runtime_error("árvore vazia");
    }
    return _at(root, k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
const Value& AVL<Key, Value, Compare, Equals>::at(const Key& k) const{
    if(root == nullptr){
        throw std::runtime_error("árvore vazia");
    }
    return _at(root, k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void AVL<Key, Value, Compare, Equals>::erase(const Key& k){
    if(!contains(k)){
        throw std::invalid_argument("esse valor nao existe na arvore para remocao");
    }
    root = _erase(root, k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
bool AVL<Key, Value, Compare, Equals>::contains(const Key& k){
    return _contains(root, k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void AVL<Key, Value, Compare, Equals>::clear(){
    if(_empty(root)){
        throw std::runtime_error("arvore vazia");
    }
    root = _clear(root);
}

template<typename Key, typename Value, typename Compare, typename Equals>
bool AVL<Key, Value, Compare, Equals>::empty(){
    return _empty(root);
}

template<typename Key, typename Value, typename Compare, typename Equals>
int AVL<Key, Value, Compare, Equals>::size(){
        return _empty(root) ? 0 : _size(root);
}

template<typename Key, typename Value, typename Compare, typename Equals>
Value& AVL<Key, Value, Compare, Equals>::operator[](const Key& k) {
    if (!contains(k)) {
        insert(k, Value{});
    }
    return at(k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
const Value& AVL<Key, Value, Compare, Equals>::operator[](const Key& k) const {
        return at(k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void AVL<Key, Value, Compare, Equals>::show(){
    bshow(root, "");
}

template<typename Key, typename Value, typename Compare, typename Equals>
std::vector<std::pair<Key, Value>> AVL<Key, Value, Compare, Equals>::toVector() const{
    std::vector<std::pair<Key, Value>> vetor;
    _toVector(root, vetor);
    return vetor; 
}

template<typename Key, typename Value, typename Compare, typename Equals>
int AVL<Key, Value, Compare, Equals>::getCountComparation(){
    return count_comp;
}

template<typename Key, typename Value, typename Compare, typename Equals>
int AVL<Key, Value, Compare, Equals>::getCountRotation(){
    return count_rotation;
}