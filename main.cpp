#include <iostream>
#include <string>
#include "dicionarios/dict_avl.hpp"
#include "dicionarios/dict_cht.hpp"
#include "dicionarios/dict_oht.hpp"
#include "dicionarios/dict_rbt.hpp"

int main(){
    //teste da avl
    d_avl::Dictionary<std::string, int> testeAVL;
    int count = 0;
    for(char i = 65; i < 75; i++){
        testeAVL.insert(std::string(1, i), count);
        count++;
    }
    testeAVL.show();
    std::cout << "tamanho: " << testeAVL.size() << std::endl;

    testeAVL.insert("K", 99);
    testeAVL.update(std::string(1, 70), 20);
    testeAVL.show();
    std::cout << "tamanho: " << testeAVL.size() << std::endl;

    
    testeAVL.erase("A");
    testeAVL.show();

    testeAVL.insert("L", 38);
    testeAVL.show();

    std::cout << "valor da chave G: " << testeAVL.getValue("G") << std::endl;
    testeAVL.contains("B") ? std::cout << "Contem B" << std::endl : std::cout << "Nao contem B" << std::endl;
    testeAVL.contains("A") ? std::cout << "Contem A" << std::endl : std::cout << "Nao contem A" << std::endl;
    std::cout << "tamanho: " << testeAVL.size() << std::endl;

    testeAVL.clear();
    std::cout << "tamanho: " << testeAVL.size() << std::endl;
    testeAVL.show();



    //teste da rbt
    d_rbt::Dictionary<std::string, int> testeRBT;
    int count2 = 0;
    for(char i = 65; i < 75; i++){
        testeRBT.insert(std::string(1, i), count2);
        count2++;
    }
    testeRBT.show();
    std::cout << "tamanho: " << testeRBT.size() << std::endl;

    testeRBT.insert("K", 99);
    testeRBT.update(std::string(1, 70), 20);
    testeRBT.show();
    std::cout << "tamanho: " << testeRBT.size() << std::endl;

    
    testeRBT.erase("A");
    testeRBT.show();

    testeRBT.insert("L", 38);
    testeRBT.show();

    std::cout << "valor da chave G: " << testeRBT.getValue("G") << std::endl;
    testeRBT.contains("B") ? std::cout << "Contem B" << std::endl : std::cout << "Nao contem B" << std::endl;
    testeRBT.contains("A") ? std::cout << "Contem A" << std::endl : std::cout << "Nao contem A" << std::endl;
    std::cout << "tamanho: " << testeRBT.size() << std::endl;

    testeRBT.clear();
    std::cout << "tamanho: " << testeRBT.size() << std::endl;
    testeRBT.show();

    
    //teste da cht
    d_cht::Dictionary<std::string, int> testeCHT1;
    d_cht::Dictionary<std::string, int> testeCHT2;
    d_cht::Dictionary<std::string, int> testeCHT3;

    int count3 = 0;
    for(char i = 65; i < 75; i++){
        testeCHT1.insert(std::string(1, i), count3);
        count3++;
    }

    int count4 = 0;
    for(char i = 65; i < 75; i++){
        testeCHT2[std::string(1,i)] = count4++;
    }

    for(char i = 65; i < 75; i++){
        testeCHT3[std::string(1,i)]++;
    }

    testeCHT1.show();
    std::cout << "tamanho: " << testeCHT1.size() << std::endl;

    testeCHT1.insert("K", 99);
    testeCHT1.update(std::string(1, 70), 20);
    testeCHT1.show();
    std::cout << "tamanho: " << testeCHT1.size() << std::endl;

    
    testeCHT1.erase("A");
    testeCHT1.show();

    testeCHT1.insert("L", 38);
    testeCHT1.show();

    std::cout << "valor da chave G: " << testeCHT1.getValue("G") << std::endl;
    testeCHT1.contains("B") ? std::cout << "Contem B" << std::endl : std::cout << "Nao contem B" << std::endl;
    testeCHT1.contains("A") ? std::cout << "Contem A" << std::endl : std::cout << "Nao contem A" << std::endl;
    std::cout << "tamanho: " << testeCHT1.size() << std::endl;

    testeCHT1.clear();
    std::cout << "tamanho: " << testeCHT1.size() << std::endl;
    testeCHT1.show();
    
}