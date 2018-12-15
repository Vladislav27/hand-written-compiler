#pragma once

#include <abstr/StringInterner.h>

namespace NIRTree {
    using Label = NTree::Symbol;

    class LabelHolder {
    public:
        static Label * GetLabel(const std::string &name);
        static Label * GetNextLabel();

    private:
        static int nextId;
        static std::string labelPrefix;

        static NTree::StringInterner interner;
    };
}