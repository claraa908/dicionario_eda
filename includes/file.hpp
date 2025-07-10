#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <unicode/ustream.h>
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <unicode/brkiter.h>
#include <unicode/locid.h>
#include <unicode/normalizer2.h>
#include <unicode/ustdio.h>
#include "UnicodeComparator.hpp"

template <typename Key>
bool compare_t(std::pair<Key, int> t1, std::pair<Key, int> t2){ return t1.second >= t2.second; }

class File{

    public:
        File() = default;

        template <typename Map>
        void read(Map& map, const std::string file_name){
            std::fstream file(file_name);
            if(!file.is_open()){
                std::cerr << "Nao foi possivel abrir o arquivo";
                return;
            }

            std::string line;
            UErrorCode status = U_ZERO_ERROR;

            const icu::Normalizer2* norm2 = icu::Normalizer2::getNFCInstance(status);
            if(U_FAILURE(status)){
                std::cerr << "Erro ao obter Normalizer2 NFC: " << u_errorName(status) << std::endl;
                return;
            }

            while(std::getline(file, line)){
                icu::UnicodeString uline = icu::UnicodeString::fromUTF8(line);
                uline = norm2->normalize(uline, status);
                uline.toLower();

                icu::UnicodeString word;
                for(int32_t i = 0; i < uline.length(); ){
                    UChar32 ch = uline.char32At(i);
                    i += U16_LENGTH(ch);

                    //tratar isso
                    if(u_isalnum(ch) || !word.isEmpty() && ch == 0x002D ){ 
                        word.append(ch);
                    }else {
                        if(!word.isEmpty()){
                            ++map[uniStringKey(word)];
                            word.remove();
                        }
                    }
                }

                if(!word.isEmpty()){
                    ++map[uniStringKey(word)];
                }
            }

            file.close();
        }

        template <typename Map>
        void write(const Map& map, std::string& start, const std::string& output){
            std::ofstream out(output);
            if(!out.is_open()){
                std::cerr << "Nao foi possivel criar/abrir o arquivo";
            }

            std::vector<std::pair<uniStringKey, int>> tuple = map.toVector();
            std::sort(tuple.begin(), tuple.end(), uniStringPairLess());

            out << start;

            for(const auto& p : tuple){
                std::string str;
                p.first.getStr().toUTF8String(str);
                out << str << ": " << p.second << std::endl;
            }
            out.close();
            std::cout << "Conteudo do dicionario gravado em '" << output << "'" << std::endl;
        }
};

#endif