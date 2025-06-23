#include <iostream>
#include <string>
#include <stdexcept>
#include "estruturas/AVL.hpp"
#include "estruturas/CHT.hpp"
#include "estruturas/OHT.hpp"
#include "estruturas/RBT.hpp"

int main(){
    /*AVL<int, std::string> avl;

    avl.insert(10, "a");
    avl.insert(20, "b");
    avl.insert(30, "c"); // Deve causar rotacoes
    avl.insert(25, "d");
    avl.insert(5, "e");

    std::cout << "AVL apos insercoes:" << std::endl;
    avl.show();

    std::cout << "Rotacoes apos insercoes: " << avl.getCountRotation() << std::endl;
    std::cout << "Comparacoes apos insercoes: " << avl.getCountComparation() << std::endl;

    try {
    avl.erase(20);
    avl.show();
    std::cout << "Rotacoes apos remocao: " << avl.getCountRotation() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Erro: " << e.what() << std::endl;
    }

    std::cout << "Rotacoes apos remocao: " << avl.getCountRotation() << std::endl;
    std::cout << "Comparacoes apos remocao: " << avl.getCountComparation() << std::endl;

    try {
        std::cout << "Valor da chave 25: " << avl.getValue(25) << std::endl;
    } catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }*/

    /*RBT<int, std::string> rbt;

    rbt.insert(10, "a");
    rbt.insert(20, "b");
    rbt.insert(30, "c"); // Deve causar recoloracoes e rotacoes
    rbt.insert(25, "d");
    rbt.insert(5, "e");

    std::cout << "RBT apos insercoes:" << std::endl;
    rbt.show();

    std::cout << "Recoloracoes apos insercoes: " << rbt.getCountRecolor() << std::endl; // Seu contador atual de recoloracao
    std::cout << "Comparacoes apos insercoes: " << rbt.getCountComparation() << std::endl;

    rbt.erase(30);
    rbt.erase(25);
    std::cout << "RBT apos remocao de 30:" << std::endl;
    rbt.show();

    std::cout << "Recoloracoes apos remocao: " << rbt.getCountRecolor() << std::endl;
    std::cout << "Comparacoes apos remocao: " << rbt.getCountComparation() << std::endl;

    try {
        std::cout << "Valor da chave 25: " << rbt.getValue(25) << std::endl;
    } catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }*/

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

    std::cout << "Valor da chave 7: " << hash.getValue(7) << std::endl;
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