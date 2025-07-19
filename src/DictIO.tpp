#include "../includes/DictIO.hpp"

int DictIO::visualWidth(const icu::UnicodeString& str) {
    int width = 0;
    for (int32_t i = 0; i < str.length(); ++i) {
        UChar32 c = str.char32At(i);
        if (u_charType(c) == U_NON_SPACING_MARK) continue;
        width += 1;
    }
    return width;
}

template <typename Map>
void DictIO::read(Map& map, const std::string input){
    std::cerr << "Tentando abrir arquivo: " << input << std::endl;
    std::fstream in(input);

    if(!in.is_open()){
        std::cerr << "Nao foi possivel abrir o arquivo" << std::endl;
        return;
    }

    std::string line;
    UErrorCode status = U_ZERO_ERROR;
    const icu::Normalizer2* norm2 = icu::Normalizer2::getNFCInstance(status);
    if(U_FAILURE(status)){
        std::cerr << "Erro ao obter Normalizer2 NFC: " << u_errorName(status) << std::endl;
        return;
    }

    while(std::getline(in, line)){
        icu::UnicodeString uline = icu::UnicodeString::fromUTF8(line);
        uline = norm2->normalize(uline, status);
        uline.toLower();

        icu::UnicodeString word;
        for(int32_t i = 0; i < uline.length(); ){
            UChar32 ch = uline.char32At(i);
            i += U16_LENGTH(ch);

            if(u_isalnum(ch) || (!word.isEmpty() && ch == 0x002D)){ 
                word.append(ch);
            }else{
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

    in.close();
}

template <typename Map>
void DictIO::write(const Map& map, std::string& time, const std::string& output){
    std::ofstream out(output);
    if(!out.is_open()){
        std::cerr << "Nao foi possivel criar/abrir o arquivo";
    }

    std::vector<std::pair<uniStringKey, int>> tuple = map.toVector();
    std::sort(tuple.begin(), tuple.end(), uniStringPairLess());

    int max_word = std::string("PALAVRA").size();
    for(const auto& p : tuple){
        int width = visualWidth(p.first.getStr());
        if (width > max_word) {
            max_word = width;
        }
    }

    const int word_padd = 35;
    const int word_width = std::max(40, max_word + word_padd);

    const int freq_width = 15;
    const int total = 1 + word_width + 1 + freq_width + 1;;

    std::string stat = " ESTATÍSTICAS ";
    int stat_lenght = stat.length();
    int padd_side = ((total - stat_lenght) / 2)+1;
    out << std::string(padd_side, '=') << stat << std::string(total - padd_side - stat_lenght, '=') << std::endl;

    out << map.metric() << std::endl;
    out << time;
    out << std::string(total, '=') << std::endl;

    out << std::endl;

    out << std::string(total, '=') << std::endl;
    out << "|" << std::setw(word_width) << std::left << "PALAVRA" << "|"
    << std::setw(freq_width) << std::right << "FREQUENCIA" << "|" << std::endl;
    out << std::string(total, '-') << std::endl;

    for(const auto& p : tuple){
        icu::UnicodeString us = p.first.getStr();
        std::string utf8;
        us.toUTF8String(utf8);
        int vis_width = visualWidth(us);
        int pad = std::max(0, word_width - vis_width);
        
        out << "|" << utf8 << std::string(pad, ' ')
            << "|" << std::setw(freq_width) << std::right << p.second << "|"
            << std::endl;
    }

    out << std::string(total, '-') << std::endl;
    out << std::string(total, '=') << std::endl;
    out.close();
    std::cout << "Conteudo do dicionario gravado em '" << output << "'" << std::endl;
}