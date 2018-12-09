#include "Label.h"

namespace NIRTree {
    NTree::StringInterner LabelHolder::interner;

    int LabelHolder::nextId = 0;

    std::string LabelHolder::labelPrefix = "label_";

    Label * LabelHolder::GetLabel(const std::string &name) {
        return LabelHolder::interner.GetIntern(name);
    }

    Label * LabelHolder::GetNextLabel() {
        return LabelHolder::interner.GetIntern(LabelHolder::labelPrefix + std::to_string(LabelHolder::nextId++));
    }
}
