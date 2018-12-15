#pragma once

#include "CommonDefs.h"

#include <iostream>

namespace NIRTree {
    class DotPrinter {
    private:
        std::ostream& outPut;
    public:
        explicit DotPrinter(std::ostream& _outPut = std::cout) : outPut(_outPut) {}
        ~DotPrinter() = default;

        void printVertex(const std::string& node, const std::string& label);
        void printEdge(const std::string& from, const std::string& to);
    };
}