#include "..\..\includes\estruturas\RBT.hpp"
//funções privadas

template<typename Key, typename Value, typename Compare, typename Equals>
typename RBT<Key, Value, Compare, Equals>::Node* RBT<Key, Value, Compare, Equals>::rightRotation(typename RBT<Key, Value, Compare, Equals>::Node* x){
    Node* y = x->left;
    x->left = y->right;
    y->right->parent = x;
    y->right = x;
    y->parent = x->parent;
    x->parent = y;

    if(y->parent == nil){
        root = y;
    }else if(less(y->tuple.first, y->parent->tuple.first)){
        y->parent->left = y;
    }else{
        y->parent->right = y;
    }
    return y;
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename RBT<Key, Value, Compare, Equals>::Node* RBT<Key, Value, Compare, Equals>::leftRotation(typename RBT<Key, Value, Compare, Equals>::Node* x){
    Node* y = x->right;
    x->right = y->left;
    y->left->parent = x;
    y->left = x;
    y->parent = x->parent;
    x->parent = y;

    if(y->parent == nil){
        root = y;
    }else if(less(y->tuple.first, y->parent->tuple.first)){
        y->parent->left = y;
    }else{
        y->parent->right = y;
    }
    return y;
}

template<typename Key, typename Value, typename Compare, typename Equals>
void RBT<Key, Value, Compare, Equals>::_insert(const Key& k, const Value& v){
    Node* pai = nil;
    Node* node = root;

    while(node != nil){
        pai = node;
        if(less(k, node->tuple.first)){
            count_comp++;
            node = node->left;
        }else if(!less(k, node->tuple.first)){
            count_comp += 2;
            node = node->right;
        }else{
            node->tuple.second = v;
            count_comp += 3;
            return;
        }
    }

    Node* novoNo = new Node(k, v, RED, nil, nil, nil);
    if(pai == nil){
        root = novoNo;
    }else{
        novoNo->parent = pai;
        if(less(k, pai->tuple.first)){
            count_comp++;
            pai->left = novoNo;
        }else{
            count_comp += 2;
            pai->right = novoNo;
        }
    }
    fixup_insertion(novoNo);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void RBT<Key, Value, Compare, Equals>::fixup_insertion(typename RBT<Key, Value, Compare, Equals>::Node* x){
    while(x->parent->color == RED){
        if(x->parent == x->parent->parent->left){
            Node* tio = x->parent->parent->right;
            if(tio->color == RED){
                x->parent->parent->color = RED;
                x->parent->color = BLACK;
                tio->color = BLACK;
                count_recolor += 3;
                x = x->parent->parent;
            }
            else{
                if(x == x->parent->right){
                    x = x->parent;
                    leftRotation(x);
                    count_rotation++;
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                count_recolor += 2;
                rightRotation(x->parent->parent);
                count_rotation++;
            }
        }else if(x->parent == x->parent->parent->right){
            Node* tio = x->parent->parent->left;
            if(tio->color == RED){
                x->parent->parent->color = RED;
                x->parent->color = BLACK;
                tio->color = BLACK;
                count_recolor += 3;
                x = x->parent->parent;
            }else{
                if(x == x->parent->left){
                    x = x->parent;
                    rightRotation(x);
                    count_rotation++;
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                count_recolor += 2;
                leftRotation(x->parent->parent);
                count_rotation++;
            }
        }
    }
    count_recolor++;
    root->color = BLACK;
}

template<typename Key, typename Value, typename Compare, typename Equals>
Value& RBT<Key, Value, Compare, Equals>::_at(typename RBT<Key, Value, Compare, Equals>::Node* p, const Key& k){
    if(p == nil){
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
const Value& RBT<Key, Value, Compare, Equals>::_at(typename RBT<Key, Value, Compare, Equals>::Node* p, const Key& k) const {
    if (p == nil) {
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
void RBT<Key, Value, Compare, Equals>::_erase(const Key& k){
    Node* p = root;
    while (p != nil) {
        if (equal(p->tuple.first, k)) {
            count_comp++;
            break;
        }

        if (!less(p->tuple.first, k)) {
            count_comp++;
            p = p->left;
        } else{
            count_comp += 2;
            p = p->right;
        }
    }

    if(p != nil){
        delete_RB(p);
    }
}

template<typename Key, typename Value, typename Compare, typename Equals>
void RBT<Key, Value, Compare, Equals>::delete_RB(typename RBT<Key, Value, Compare, Equals>::Node* p){
    Node* y = nil;
    if(p->left == nil || p->right == nil){
        y = p;
    }else{
        y = minimum(p->right);
    }

    Node* x = nil;
    if(y->right != nil){
        x = y->right;
    }else{
        x = y->left;
    }

    if(x != nil){
        x->parent = y->parent;
    }

    if(y->parent == nil){
        root = x;
    }else{
        if(y == y->parent->left){
            y->parent->left = x;
        }else{
            y->parent->right = x;
        }
    }

    if(y != p){
        p->tuple = y->tuple;
    }
    if(y->color == BLACK){
        fixup_erase(x);
    }
    delete y;
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename RBT<Key, Value, Compare, Equals>::Node* RBT<Key, Value, Compare, Equals>::minimum(typename RBT<Key, Value, Compare, Equals>::Node* p){
    while(p->left != nil){
        p = p->left;
    }
    return p;
}

template<typename Key, typename Value, typename Compare, typename Equals>
void RBT<Key, Value, Compare, Equals>::fixup_erase(typename RBT<Key, Value, Compare, Equals>::Node* x){
    while(x != root && x->color == BLACK){
        if(x == x->parent->left){
            Node* w = x->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                leftRotation(x->parent);
                count_rotation++;
                w = x->parent->right;
                count_recolor += 2;
            }
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
                count_recolor++;
            }
            else{
                if(w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotation(w);
                    count_rotation++;
                    w = x->parent->right;
                    count_recolor += 2;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotation(x->parent);
                count_rotation++;
                x = root;
                count_recolor += 3;
            }
        } else {
            Node* w = x->parent->left;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                rightRotation(x->parent);
                count_rotation++;
                w = x->parent->left;
                count_recolor += 2;
            }
            if(w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;
                x = x->parent;
                count_recolor++;
            }
            else{
                if(w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotation(w);
                    count_rotation++;
                    w = x->parent->left;
                    count_recolor += 2;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotation(x->parent);
                count_rotation++;;
                x = root;
                count_recolor += 3;
            }
        }
    }
    count_recolor++;
    x->color = BLACK;
}

template<typename Key, typename Value, typename Compare, typename Equals>
bool RBT<Key, Value, Compare, Equals>::_contains(const Key& k){
    if(root == nil){
        return false;
    }
    Node* p = root;
    while (p != nil) {
        if (equal(k, p->tuple.first)) {
            count_comp++;
            return true;
        }

        if (less(k, p->tuple.first)) {
            count_comp++;
            p = p->left;
        } else {
            count_comp += 2;
            p = p->right;
        }
    }
    return false;
}

template<typename Key, typename Value, typename Compare, typename Equals>
typename RBT<Key, Value, Compare, Equals>::Node* RBT<Key, Value, Compare, Equals>::_clear(typename RBT<Key, Value, Compare, Equals>::Node* p){
    if(p == nil) return nil;

    _clear(p->left);
    _clear(p->right);
    delete p;

    return nil;
}

template<typename Key, typename Value, typename Compare, typename Equals>
bool RBT<Key, Value, Compare, Equals>::_empty(typename RBT<Key, Value, Compare, Equals>::Node* p){
    return p == nil;
}

template<typename Key, typename Value, typename Compare, typename Equals>
int RBT<Key, Value, Compare, Equals>::_size(typename RBT<Key, Value, Compare, Equals>::Node* p) {
    if (p == nil) return 0;
    return 1 + _size(p->left) + _size(p->right);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void RBT<Key, Value, Compare, Equals>::bshow(typename RBT<Key, Value, Compare, Equals>::Node *node, std::string heranca) {
    if(node != nil && (node->left != nil || node->right != nil))
        bshow(node->right , heranca + "r");

    for(int i = 0; i < static_cast<int>(heranca.size()) - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "|   " : "    ");

    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "|-- " : "|-- ");
    
    if(node == nil){
        std::cout << "#" << std::endl;
        return;
    }

    if (node->color == RED)
        std::cout << "\033[1;31m" << node->tuple.first << ": " << node->tuple.second << "\033[0m" << std::endl ;
    else
        std::cout << "\033[1;30m" << node->tuple.first << ": " << node->tuple.second << "\033[0m" << std::endl;

    if(node != nil && (node->left != nil || node->right != nil))
        bshow(node->left, heranca + "l");
}

template<typename Key, typename Value, typename Compare, typename Equals>
void RBT<Key, Value, Compare, Equals>::_toVector(RBT<Key, Value, Compare, Equals>::Node* p, std::vector<std::pair<Key, Value>>& v) const{
    if(p != nil){
        _toVector(p->left, v);
        v.push_back({p->tuple.first, p->tuple.second});
        _toVector(p->right, v);
    }
}

//funções públicas

template<typename Key, typename Value, typename Compare, typename Equals>
RBT<Key, Value, Compare, Equals>::RBT(){
    nil = new Node(Key{}, Value{}, BLACK, nullptr, nullptr, nullptr);
    nil->left = nil->right = nil;
    root = nil;
    root->parent = nil;
    count_comp = 0;
    count_recolor = 0;
    count_rotation = 0;
    less = Compare();
    equal = Equals();
}
template<typename Key, typename Value, typename Compare, typename Equals>
RBT<Key, Value, Compare, Equals>::~RBT(){
    root = _clear(root);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void RBT<Key, Value, Compare, Equals>::insert(const Key& k, const Value& v){
    _insert(k, v);
}

template<typename Key, typename Value, typename Compare, typename Equals>
Value& RBT<Key, Value, Compare, Equals>::at(const Key& k){
    if(root == nil){
        throw std::invalid_argument("árvore vazia");
    }
    return _at(root, k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
const Value& RBT<Key, Value, Compare, Equals>::at(const Key& k) const{
    if(root == nil){
        throw std::invalid_argument("árvore vazia");
    }
    return _at(root, k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void RBT<Key, Value, Compare, Equals>::erase(const Key& k){
    if(!contains(k)){
        throw std::invalid_argument("esse valor nao existe na arvore para remocao");
    }
    _erase(k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
bool RBT<Key, Value, Compare, Equals>::contains(const Key& k){
    return _contains(k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void RBT<Key, Value, Compare, Equals>::clear(){
    if(_empty(root)){
        throw std::runtime_error("arvore vazia");
    }
    root = _clear(root);
}

template<typename Key, typename Value, typename Compare, typename Equals>
bool RBT<Key, Value, Compare, Equals>::empty(){
    return _empty(root);
}

template<typename Key, typename Value, typename Compare, typename Equals>
int RBT<Key, Value, Compare, Equals>::size(){
    return _empty(root) ? 0 : _size(root);
}

template<typename Key, typename Value, typename Compare, typename Equals>
Value& RBT<Key, Value, Compare, Equals>::operator[](const Key& k) {
    if (!contains(k)) {
        insert(k, Value{});
    }
    return at(k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
const Value& RBT<Key, Value, Compare, Equals>::operator[](const Key& k) const {
    return at(k);
}

template<typename Key, typename Value, typename Compare, typename Equals>
void RBT<Key, Value, Compare, Equals>::show(){
    bshow(root, "");
}

template<typename Key, typename Value, typename Compare, typename Equals>
std::vector<std::pair<Key, Value>> RBT<Key, Value, Compare, Equals>::toVector() const{
    std::vector<std::pair<Key, Value>> vetor;
    _toVector(root, vetor);
    return vetor; 
}

template<typename Key, typename Value, typename Compare, typename Equals>
int RBT<Key, Value, Compare, Equals>::getCountComparation() const{
    return count_comp;
}

template<typename Key, typename Value, typename Compare, typename Equals>
int RBT<Key, Value, Compare, Equals>::getCountRecolor() const{
    return count_recolor;
}

template<typename Key, typename Value, typename Compare, typename Equals>
int RBT<Key, Value, Compare, Equals>::getCountRotation() const{
    return count_rotation;
}