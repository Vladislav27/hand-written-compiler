#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace NTree {
    class Symbol {
    public:
        const std::string& String() const { return string; }


        Symbol(const Symbol&) = delete;
        void operator=(const Symbol&) = delete;

        friend class StringInterner;
    private:
        explicit Symbol(const std::string&);

        std::string string;
    };
}