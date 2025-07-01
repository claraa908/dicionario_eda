#include "..\..\includes\estruturas\AVL.hpp"
//funções privadas

template<typename Key, typename Value>
int AVL<Key, Value>::height (typename AVL<Key, Value>::Node* node){
    return (_empty(node)) ? 0 : node->height;
}

template<typename Key, typename Value>
int AVL<Key, Value>::balance (typename AVL<Key, Value>::Node* node){
    return height(node->right) - height(node->left);
}

template<typename Key, typename Value>
typename AVL<Key, Value>::Node* AVL<Key, Value>::rightRotation (typename AVL<Key, Value>::Node* p){
    Node* u = p->left;
    p->left = u->right;
    u->right = p;

    p->height = 1 +  std::max(height(p->left), height(p->right));
    u->height = 1 +  std::max(height(u->left), height(u->right));
    return u;
}

template<typename Key, typename Value>
typename AVL<Key, Value>::Node* AVL<Key, Value>::leftRotation (typename AVL<Key, Value>::Node* p){
    Node* u = p->right;
    p->right = u->left;
    u->left = p;

    p->height = 1 +  std::max(height(p->left), height(p->right));
    u->height = 1 +  std::max(height(u->left), height(u->right));
    return u;
}

template<typename Key, typename Value>
typename AVL<Key, Value>::Node* AVL<Key, Value>::_insert(typename AVL<Key, Value>::Node* p , const Key& k, const Value& v){
    if(_empty(p)){
        return new Node{k, v, 1, nullptr, nullptr};
    }
    
    if(k == p->tuple.first){
        count_comp++;
        p->tuple.second = v;
        return p;
    }
    if(k < p->tuple.first){
        count_comp += 2;
        p->left = _insert(p->left, k, v);
    }
    else if(k > p->tuple.first){
        count_comp += 3;
        p->right = _insert(p->right, k, v);
    }
    p = fixup_insertion(p, k);
    return p;
}

template<typename Key, typename Value>
typename AVL<Key, Value>::Node* AVL<Key, Value>::fixup_insertion(typename AVL<Key, Value>::Node* p, const Key& k){
    int bal = balance(p);
    if(bal < -1){
        if(k < p->left->tuple.first){
            count_comp++;
            count_rotation++;
            return rightRotation(p);
        }
        if(k > p->left->tuple.first){
            count_comp += 2;
            count_rotation += 2;
            p->left = leftRotation(p->left);
            return rightRotation(p);
        }
    }
    if(bal > 1){
        if(k > p->right->tuple.first){
        count_comp++;
        count_rotation++;
        return leftRotation(p);
        }
        if(k < p->right->tuple.first){
            count_comp += 2;
            count_rotation += 2;
            p->right = rightRotation(p->right);
            return leftRotation(p);
        }
    }
    p->height = 1 + std::max(height(p->left), height(p->right));
    return p;
}

template<typename Key, typename Value>
Value& AVL<Key, Value>::_at(typename AVL<Key, Value>::Node* p, const Key& k){
    if(p == nullptr){
        throw std::invalid_argument("chave nao encontrada na arvore");
    }
    if(k == p->tuple.first){
        count_comp++;
        return p->tuple.second;
    }else if(k < p->tuple.first){
        count_comp += 2;
        return _at(p->left, k);
    }else{
        count_comp += 3;
        return _at(p->right, k);
    }
}

template<typename Key, typename Value>
const Value& AVL<Key, Value>::_at(typename AVL<Key, Value>::Node* p, const Key& k) const {
    if (p == nullptr) {
        throw std::invalid_argument("chave nao encontrada na arvore");
    }

    if (k == p->tuple.first) {
        count_comp++;
        return p->tuple.second;
    } else if (k < p->tuple.first) {
        count_comp += 2;
        return _at(p->left, k);
    } else {
        count_comp += 3;
        return _at(p->right, k);
    }
}

template<typename Key, typename Value>
typename AVL<Key, Value>::Node* AVL<Key, Value>::_erase(typename AVL<Key, Value>::Node* p, const Key& k){
    if(_empty(p)){
        return nullptr;
    }
    if(k < p->tuple.first){
        count_comp++;
        p->left = _erase(p->left, k);
    } else if(k > p->tuple.first){
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

template<typename Key, typename Value>
typename AVL<Key, Value>::Node* AVL<Key, Value>::minimum(typename AVL<Key, Value>::Node* p){
    while(p->left != nullptr){
        p = p->left;
    }
    return p;
}

template<typename Key, typename Value>
typename AVL<Key, Value>::Node* AVL<Key, Value>::fixup_erase(typename AVL<Key, Value>::Node* p){
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

template<typename Key, typename Value>
bool AVL<Key, Value>::_contains(typename AVL<Key, Value>::Node* p, const Key& k){
    if(_empty(p)){
        return false;
    }
    if(k == p->tuple.first){
        count_comp++;
        return true;
    }

    if(k < p->tuple.first){
        count_comp += 2;
        return _contains(p->left, k);
    }else{
        count_comp += 3;
        return _contains(p->right, k);
    }
}

template<typename Key, typename Value>
typename AVL<Key, Value>::Node* AVL<Key, Value>::_clear(typename AVL<Key, Value>::Node* p){
    if(p != nullptr){
        p->left = _clear(p->left);
        p->right = _clear(p->right);
        delete p;
    }
    return nullptr;
}

template<typename Key, typename Value>
bool AVL<Key, Value>::_empty(AVL<Key, Value>::Node* p){
    return p == nullptr;
}

template<typename Key, typename Value>
int AVL<Key, Value>::_size(AVL<Key, Value>::Node* p){
    if(_empty(p)){
        return 0;
    }

    return 1 + _size(p->left) + _size(p->right);
}

template<typename Key, typename Value>
void AVL<Key, Value>::bshow(AVL<Key, Value>::Node* node, std::string heranca) const {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
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


//funções públicas
template<typename Key, typename Value>
AVL<Key, Value>::AVL() {
    root = nullptr;
    count_comp = 0;
    count_rotation = 0;
}

template<typename Key, typename Value>
AVL<Key, Value>::~AVL(){
    root = _clear(root);
}

template<typename Key, typename Value>
void AVL<Key, Value>::insert(const Key& k, const Value& v){
    root = _insert(root, k, v);
}

template<typename Key, typename Value>
Value& AVL<Key, Value>::at(const Key& k){
    if(root == nullptr){
        throw std::runtime_error("árvore vazia");
    }
    return _at(root, k);
}

template<typename Key, typename Value>
const Value& AVL<Key, Value>::at(const Key& k) const{
    if(root == nullptr){
        throw std::runtime_error("árvore vazia");
    }
    return _at(root, k);
}

template<typename Key, typename Value>
void AVL<Key, Value>::erase(const Key& k){
    if(!contains(k)){
        throw std::invalid_argument("esse valor nao existe na arvore para remocao");
    }
    root = _erase(root, k);
}

template<typename Key, typename Value>
bool AVL<Key, Value>::contains(const Key& k){
    return _contains(root, k);
}

template<typename Key, typename Value>
void AVL<Key, Value>::clear(){
    if(_empty(root)){
        throw std::runtime_error("arvore vazia");
    }
    root = _clear(root);
}

template<typename Key, typename Value>
bool AVL<Key, Value>::empty(){
    return _empty(root);
}

template<typename Key, typename Value>
int AVL<Key, Value>::size(){
        return _empty(root) ? 0 : _size(root);
}

template<typename Key, typename Value>
Value& AVL<Key, Value>::operator[](const Key& k) {
    if (!contains(k)) {
        insert(k, Value{});
    }
    return at(k);
}

template<typename Key, typename Value>
const Value& AVL<Key, Value>::operator[](const Key& k) const {
        return at(k);
}

template<typename Key, typename Value>
void AVL<Key, Value>::show(){
    bshow(root, "");
}

template<typename Key, typename Value>
int AVL<Key, Value>::getCountComparation(){
    return count_comp;
}

template<typename Key, typename Value>
int AVL<Key, Value>::getCountRotation(){
    return count_rotation;
}