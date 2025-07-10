#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <unicode/brkiter.h>
#include <unicode/normalizer2.h>
#include <unicode/locid.h>
#include "includes/dicionarios/MAP_AVL.hpp"
#include "includes/dicionarios/MAP_CHT.hpp"
#include "includes/dicionarios/MAP_OHT.hpp"
#include "includes/dicionarios/MAP_RBT.hpp"
#include "includes/UnicodeComparator.hpp"
#include "includes/file.hpp"

int main(int argc, char* argv[]){
    File arq;
    std::string option = argv[1];
    std::string arq_in = argv[2];
    std::string arq_out = argv[3];

    if(argc != 4){
        std::cout << "Comando errado" << std::endl;
    }

    if(argc == 4){
        if(option == "map_avl")
        {
            MAP_AVL<uniStringKey, int, uniStringLess, uniStringEquals> map_avl;
            arq.read(map_avl, "texts/"+arq_in);
            arq.write(map_avl, "tables_texts/"+arq_out);
        }


        else if(option == "map_rbt")
        {
            MAP_RBT<uniStringKey, int, uniStringLess, uniStringEquals> map_rbt;
            arq.read(map_rbt, "texts/"+arq_in);
            arq.write(map_rbt, "tables_texts/"+arq_out);
        }


        else if(option == "map_cht")
        {
            MAP_CHT<uniStringKey, int, uniStringHasher,uniStringLess, uniStringEquals> map_cht;
            arq.read(map_cht, "texts/"+arq_in);
            arq.write(map_cht, "tables_texts/"+arq_out);
        }


        else if(option == "map_oht")
        {
            MAP_OHT<uniStringKey, int, uniStringHasher,uniStringLess, uniStringEquals> map_oht;
            arq.read(map_oht, "texts/"+arq_in);
            arq.write(map_oht, "tables_texts/"+arq_out);
        }
    }
}