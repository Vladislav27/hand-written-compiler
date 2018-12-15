#pragma once

#include <unordered_map>
#include <string>

namespace NTree {
    class Symbol;

    class StringInterner {
        std::unordered_map<std::string, Symbol*> allStrings;
    public:
        Symbol* GetIntern(const std::string& src);
        ~StringInterner();
    };
}