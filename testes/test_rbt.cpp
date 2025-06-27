#include <iostream>
#include <string>
#include <stdexcept>
#include "..\includes\estruturas\RBT.hpp"

int main(){
    RBT<int, std::string> rbt;

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
        std::cout << "Valor da chave 25: " << rbt.at(25) << std::endl;
    } catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }
}