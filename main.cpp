#include <iostream>
#include <string>
#include "dicionarios/dict_avl.hpp"
#include "dicionarios/dict_cht.hpp"
#include "dicionarios/dict_oht.hpp"
#include "dicionarios/dict_rbt.hpp"

int main(){
    d_avl::Dictionary<int, int> testedefault;
    d_avl::Dictionary<std::string, int> teste("Oii", 5);
    d_rbt::Dictionary<int, int> testeRBT;
    for(int i = 0; i < 11; i++){
        testedefault.insert(i,i);
    }

    for(int i = 0; i < 11; i++){
        testeRBT.insert(i,i);
    }

    teste.show();
    testedefault.show();
    testeRBT.show();
}