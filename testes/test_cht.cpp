#include <iostream>
#include <string>
#include <stdexcept>
#include "..\includes\estruturas\CHT.hpp"

int main(){
    CHT<int, std::string> hash(3, 0.75);

    std::cout << "Inserindo 1:'a'" << std::endl;
    hash.insert(1, "a");
    std::cout << "Colisoes: " << hash.getCountCollision() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountComparation() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountRehash() << std::endl;
    hash.show();
    std::cout << std::endl;

    std::cout << "Inserindo 4:'b'" << std::endl;
    hash.insert(4, "b");
    std::cout << "Colisoes: " << hash.getCountCollision() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountComparation() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountRehash() << std::endl;
    hash.show();
    std::cout << std::endl;

    std::cout << "Inserindo 7:'c'" << std::endl;
    hash.insert(7, "c");
    std::cout << "Colisoes: " << hash.getCountCollision() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountComparation() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountRehash() << std::endl;
    hash.show();
    std::cout << std::endl;

    std::cout << "Atualizando 4:'d'" << std::endl;
    hash.insert(4, "d");
    std::cout << "Colisoes: " << hash.getCountCollision() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountComparation() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountRehash() << std::endl;
    hash.show();
    std::cout << std::endl;

    std::cout << "Valor da chave 7: " << hash.at(7) << std::endl;
    std::cout << "Comparacoes apos at(7): " << hash.getCountComparation() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountRehash() << std::endl;

    std::cout << "Contem chave 1? " << (hash.contains(1) ? "Sim" : "Nao") << std::endl;
    std::cout << "Comparacoes apos contains(1): " << hash.getCountComparation() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountRehash() << std::endl;
    hash.show();
    std::cout << std::endl;

    std::cout << "Removendo chave 4" << std::endl;
    if(hash.erase(4)){
        std::cout << "Removido com sucesso" << std::endl;
    } else {
        std::cout << "Chave nao encontrada" << std::endl;
    }
    std::cout << "Comparacoes apos erase(4): " << hash.getCountComparation() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountRehash() << std::endl;
    hash.show();
    std::cout << std::endl;

    std::cout << "\nConteudo da tabela:\n";
    hash.show();
    std::cout << std::endl;

    hash.clear();
    hash.show();
    std::cout << hash.empty() << std::endl;
    std::cout << std::endl;
    

    std::cout << "atualizacao da chave 1: " << std::endl;
    hash[1] = "clara";
    std::cout << "insercao da chave 9: " << std::endl;
    hash[9] = "o";

    std::cout << "insercao da chave 8 vazia: " << std::endl;
    hash[8];

    std::cout << "Colisoes: " << hash.getCountCollision() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountComparation() << std::endl;
    std::cout << "Comparacoes: " << hash.getCountRehash() << std::endl;
    hash.show();

    std::cout << "Quantidade de elementos: " << hash.size() << std::endl;
    hash.empty() ? std::cout << "vazio" << std::endl : std::cout << "nao vazio" << std::endl;
    std::cout << "Quantidade de slots da tabela: " << hash.num_slot() << std::endl;
    std::cout << "Tamanho do slot 1: " << hash.slot_size(1) << std::endl;
    std::cout << "Fator de carga atual da tabela: "<< hash.load_factor() << std::endl;
    std::cout << "Fator de carga máximo da tabela: " << hash.max_load_factor() << std::endl;
}