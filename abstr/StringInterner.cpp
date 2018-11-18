#include "StringInterner.h"
#include "Symbol.h"

namespace NTree {
    Symbol* StringInterner::GetIntern(const std::string &src) {
        auto cached = allStrings.find(src);
        if (cached != allStrings.end()) {
            return cached->second;
        }

        auto* newVal = new Symbol(src);
        allStrings.insert({src, newVal});
        return newVal;
    }

    StringInterner::~StringInterner() {
        for (const auto& item: allStrings) {
            delete item.second;
        }
    }
}