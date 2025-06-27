#include <iostream>
#include <string>
#include <stdexcept>
#include "..\includes\estruturas\CHT.hpp"

int main(){
    CHT<int, std::string> hash(3);  // Tamanho pequeno para causar colisoes

    std::cout << "Inserindo 1:'a'" << std::endl;
    hash.insert(1, "a");
    std::cout << "Colisoes: " << hash.getCountCollision() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountComparation() << std::endl;

    std::cout << "Inserindo 4:'b'" << std::endl;
    hash.insert(4, "b");  // Deve colidir com 1
    std::cout << "Colisoes: " << hash.getCountCollision() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountComparation() << std::endl;

    std::cout << "Inserindo 7:'c'" << std::endl;
    hash.insert(7, "c");  // Mais uma colisao no mesmo slot
    std::cout << "Colisoes: " << hash.getCountCollision() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountComparation() << std::endl;

    std::cout << "Atualizando 4:'d'" << std::endl;
    hash.insert(4, "d");  // Atualizacao, sem colisao nova
    std::cout << "Colisoes: " << hash.getCountCollision() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountComparation() << std::endl;

    std::cout << "Valor da chave 7: " << hash.at(7) << std::endl;
    std::cout << "Comparacoes apos getValue: " << hash.getCountComparation() << std::endl;

    std::cout << "Contem chave 1? " << (hash.contains(1) ? "Sim" : "Nao") << std::endl;
    std::cout << "Comparacoes apos contains: " << hash.getCountComparation() << std::endl;

    std::cout << "Removendo chave 4" << std::endl;
    if(hash.erase(4)){
        std::cout << "Removido com sucesso" << std::endl;
    }else{
        std::cout << "Chave nao encontrada" << std::endl;
    }
    std::cout << "Comparacoes apos erase: " << hash.getCountComparation() << std::endl;
}