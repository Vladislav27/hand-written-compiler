#include "InstructionSet.h"

namespace NCodeGeneration {

    RegMove::RegMove(const std::string code, const NIRTree::Temp *from, const NIRTree::Temp *to) :
            MoveInstruction(from, to) {
        asmCode = code;
    }

    RegMove::RegMove(const std::string code, const NIRTree::TempList &&from) :
            MoveInstruction(std::move(from)) {
        asmCode = code;
    }

    RegMove::RegMove(const std::string code, const NIRTree::Const *from, const NIRTree::Temp *to) :
            MoveInstruction(from, to) {
        asmCode = code;
    }

}
