#include <iostream>
#include <string>
#include "estruturas/AVL.hpp"
#include "estruturas/CHT.hpp"
#include "estruturas/OHT.hpp"
#include "estruturas/RBT.hpp"

int main(){
    AVL<int, int> teste;
    for(int i = 0; i < 10; i++){
        teste.insert(i, i+3);
    }

    RBT<int, int> teste2;
    for(int i = 0; i < 10; i++){
        teste2.insert(i, i+3);
    }

    //teste RBT
    std::cout << teste2.getContador() << std::endl;
    std::cout << teste.getContador() << std::endl;
    teste2.show();
    teste2.contains(10) ? std::cout << "tem sim, vei" << std::endl : std::cout << "tem nao" << std::endl;
    teste2.erase(3);
    teste2.show();

    teste2.clear();
    teste2.show();

    teste2.contains(2) ? std::cout << "tem sim, vei" << std::endl : std::cout << "tem nao" << std::endl;

    //teste AVL
    teste.show();
    teste.empty() ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
    teste.contains(4) ? std::cout << "Possui" << std::endl : std::cout << "Nao possui" << std::endl;
    teste.contains(42) ? std::cout << "Possui" << std::endl : std::cout << "Nao possui" << std::endl;
    std::cout << teste.size() << std::endl;
    std::cout << teste.getContador() << std::endl;
    teste.clear();
    
    teste.show();
    teste.empty() ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
    std::cout << teste.size() << std::endl;

    //teste CHT
    CHT<std::string, int> hash(10);
    hash.insert("a", 1);
    hash.insert("b", 2);
    std::cout << std::endl;
    std::cout << hash["a"] << "\n";
    std::cout << hash.getValue("b") << "\n";
    hash["c"] = 3;
    std::cout << hash.getValue("c") << "\n";
}