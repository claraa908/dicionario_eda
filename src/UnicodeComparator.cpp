#include "../includes/UnicodeComparator.hpp"

uniStringKey::uniStringKey() = default;

uniStringKey::uniStringKey(const icu::UnicodeString& k) : str(k) {}

uniStringKey::uniStringKey(const std::string k) {
    str = icu::UnicodeString::fromUTF8(k);
}

const icu::UnicodeString& uniStringKey::getStr() const {
    return str;
}

std::ostream& operator<<(std::ostream& os, const uniStringKey& key) {
    std::string utf8_result;
    key.str.toUTF8String(utf8_result);
    os << utf8_result;
    return os;
}

icu::Collator* getGlobalCollator() {
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

bool uniStringEquals::operator()(const uniStringKey& a, const uniStringKey& b) const {
    icu::Collator* collator = getGlobalCollator();
    if (!collator) return a.getStr() == b.getStr();
    return collator->compare(a.getStr(), b.getStr()) == icu::Collator::EComparisonResult::EQUAL;
}

bool uniStringLess::operator()(const uniStringKey& a, const uniStringKey& b) const {
    icu::Collator* collator = getGlobalCollator();
    if (!collator) return a.getStr() < b.getStr();
    return collator->compare(a.getStr(), b.getStr()) == icu::Collator::EComparisonResult::LESS;
}

size_t uniStringHasher::operator()(const uniStringKey& key) const {
    std::string str;
    key.getStr().toUTF8String(str);
    return std::hash<std::string>{}(str);
}

bool uniStringPairLess::operator()(const std::pair<uniStringKey, int>& a, const std::pair<uniStringKey, int>& b) const {
    return uniStringLess()(a.first, b.first);
}
