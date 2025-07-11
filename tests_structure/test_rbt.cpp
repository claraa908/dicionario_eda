#include <iostream>
#include <string>
#include <stdexcept>
#include "..\includes\estruturas\RBT.hpp"

int main(){
    RBT<int, std::string> rbt;

    rbt.insert(10, "a");
    rbt.insert(20, "b");
    rbt.insert(30, "c");
    rbt.insert(25, "d");
    rbt.insert(5, "e");
    std::cout << "contador apos insercoes: " << rbt.getCountComparation() << std::endl;
    std::cout << "Recoloracoes apos insercoes: " << rbt.getCountRecolor() << std::endl;
    std::cout << "Rotacoes apos insercoes: " << rbt.getCountRotation() << std::endl;
    rbt.empty() ? std::cout << "arvore vazia" << std::endl : std::cout << "arvore nao vazia" << std::endl;
    std::cout << "tamanho da RBT: " << rbt.size() << std::endl;
    std::cout << "RBT apos insercoes:" << std::endl;
    rbt.show();

    rbt.erase(20);
    std::cout << "contador apos remocao do 20: " << rbt.getCountComparation() << std::endl;
    std::cout << "Recoloracoes apos remocao do 20: " << rbt.getCountRecolor() << std::endl;
    std::cout << "Rotacoes apos remocao do 20: " << rbt.getCountRotation() << std::endl;
    std::cout << "tamanho da RBT: " << rbt.size() << std::endl;
    std::cout << "RBT apos remocao de 20:" << std::endl;
    rbt.show();

    rbt.contains(30) ? std::cout << "contem 30" << std::endl : std::cout << "nao contem 30" << std::endl;
    rbt.contains(20) ? std::cout << "contem 20" << std::endl : std::cout << "nao contem 20" << std::endl;

    rbt.erase(25);
    std::cout << "contador apos remocao do 25: " << rbt.getCountComparation() << std::endl;
    std::cout << "Recoloracoes apos remocao do 25: " << rbt.getCountRecolor() << std::endl;
    std::cout << "Rotacoes apos remocao do 25: " << rbt.getCountRotation() << std::endl;
    std::cout << "tamanho da RBT: " << rbt.size() << std::endl;
    std::cout << "RBT apos remocao de 25:" << std::endl;
    rbt.show();

    std::cout << "insercao do 40 com []" << std::endl;
    rbt[40];
    rbt.show();

    std::cout << "insercao de valor no 40 usando []" << std::endl;
    rbt[40] = "claraaaa";
    rbt.show();

    rbt.clear();
    rbt.show();
    std::cout << "tamanho da RBT: " << rbt.size() << std::endl;
    rbt.empty() ? std::cout << "arvore vazia" << std::endl : std::cout << "arvore nao vazia" << std::endl;
}