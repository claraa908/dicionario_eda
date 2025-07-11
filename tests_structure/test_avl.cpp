#include <iostream>
#include <string>
#include <stdexcept>
#include "..\includes\estruturas\AVL.hpp"

int main(){
    AVL<int, std::string> avl;
    avl.insert(10, "a");
    avl.insert(20, "b");
    avl.insert(30, "c");
    avl.insert(25, "d");
    avl.insert(5, "e");

    std::cout << "AVL apos insercoes:" << std::endl;
    avl.show();

    std::cout << "Rotacoes apos insercoes: " << avl.getCountRotation() << std::endl;
    std::cout << "Comparacoes apos insercoes: " << avl.getCountComparation() << std::endl;

    avl.erase(20);
    avl.show();
    std::cout << "Rotacoes apos remocao: " << avl.getCountRotation() << "\n";
    std::cout << "Comparacoes apos remocao: " << avl.getCountComparation() << std::endl;
    avl[87] = "clarita";
    avl.show();

    avl.contains(87) ? std::cout << "contem 87" << std::endl  : std::cout << "nao contem 87" << std::endl;
    avl.contains(99) ? std::cout << "contem 99" << std::endl : std::cout << "nao contem 99" << std::endl;
    std::cout << avl.size() << std::endl;
    std::cout << avl[87] << std::endl;
    avl.empty() ? std::cout << "vazia" << std::endl  : std::cout << "nao vazia" << std::endl;
    avl.erase(87);
    avl.contains(87) ? std::cout << "contem 87" << std::endl  : std::cout << "nao contem 87" << std::endl;
    std::cout << avl.at(30) << std::endl;
    
    avl.clear();
    avl.show();
    avl.empty() ? std::cout << "vazia" << std::endl  : std::cout << "nao vazia" << std::endl;
    std::cout << avl.size() << std::endl;
}