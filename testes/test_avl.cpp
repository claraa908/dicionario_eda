#include <iostream>
#include <string>
#include <stdexcept>
#include "..\includes\estruturas\AVL.hpp"

int main(){
    AVL<int, std::string> avl;

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
        std::cout << "Valor da chave 25: " << avl.at(25) << std::endl;
    } catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }
}