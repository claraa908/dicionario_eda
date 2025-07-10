#ifndef UNICODE_COMPARATORS_HPP
#define UNICODE_COMPARATORS_HPP

#include <unicode/unistr.h>
#include <unicode/coll.h>
#include <unicode/locid.h>
#include <mutex>
#include <functional>
#include <iostream>
#include <utility>

class uniStringKey{
    private:
        icu::UnicodeString str;
    public:
        uniStringKey() = default;

        uniStringKey(const icu::UnicodeString& k){
            str = k;
        }

        uniStringKey(const std::string k){
            str = icu::UnicodeString::fromUTF8(k);
        }

        const icu::UnicodeString& getStr() const { return str; }

        friend std::ostream& operator<<(std::ostream& os, const uniStringKey& key) {
            std::string utf8_result;
            key.str.toUTF8String(utf8_result);
            os << utf8_result;
            return os;
        }
};

struct uniStringEquals{
    static icu::Collator* get_collator(){
        static icu::Collator* collator = nullptr;
        static std::once_flag once_flag;

        std::call_once(once_flag, []() {
            UErrorCode status = U_ZERO_ERROR;
            collator = icu::Collator::createInstance(icu::Locale::getDefault(), status);
            if (U_FAILURE(status)) {
                std::cerr << "Erro fatal ao criar Collator: " << u_errorName(status) << std::endl;
                collator = nullptr;
            } else {
                collator->setStrength(icu::Collator::SECONDARY);
            }
        });
        return collator;
    }

    bool operator()(const uniStringKey& a, const uniStringKey& b) const {
        icu::Collator* collator = get_collator();
        if (!collator) {
            return a.getStr() < b.getStr();
        }
        return collator->compare(a.getStr(), b.getStr()) == icu::Collator::EComparisonResult::EQUAL;
    }
};

struct uniStringLess{
    static icu::Collator* get_collator(){
        static icu::Collator* collator = nullptr;
        static std::once_flag once_flag;

        std::call_once(once_flag, []() {
            UErrorCode status = U_ZERO_ERROR;
            collator = icu::Collator::createInstance(icu::Locale::getDefault(), status);
            if (U_FAILURE(status)) {
                std::cerr << "Erro fatal ao criar Collator: " << u_errorName(status) << std::endl;
                collator = nullptr;
            } else {
                collator->setStrength(icu::Collator::SECONDARY);
            }
        });
        return collator;
    }

    bool operator()(const uniStringKey& a, const uniStringKey& b) const {
        icu::Collator* collator = get_collator();
        if (!collator) {
            return a.getStr() < b.getStr();
        }
        return collator->compare(a.getStr(), b.getStr()) == icu::Collator::EComparisonResult::LESS;
    }
};

struct uniStringHasher {
    size_t operator()(const uniStringKey& key) const {
        icu::UnicodeString ustr = key.getStr();

        std::string str;
        ustr.toUTF8String(str);
        return std::hash<std::string>{}(str);
    }
};

struct uniStringPairLess {
    bool operator()(const std::pair<uniStringKey, int>& a, const std::pair<uniStringKey, int>& b) const {
        return uniStringLess()(a.first, b.first);
    }
};

#endif