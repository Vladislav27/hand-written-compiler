#pragma once

#include <iostream>
#include <memory>

namespace NTree {
    class Symbol {
    public:
        const std::string& String() const { return string; }

        Symbol(const Symbol&) = delete;
        void operator=(const Symbol&) = delete;

//        friend class StringInterner;
    private:
        explicit Symbol(const std::string&);

        std::string string;
    };
}