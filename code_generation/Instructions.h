#pragma once

#include <irt/NodeTypes.h>

#include <vector>

namespace NCodeGeneration {

    class IInstruction {
    public:
        virtual ~IInstruction() = default;

        std::string AsmCode() const { return asmCode; }

        const NIRTree::TempList &UsedVars() const { return src; }

        const NIRTree::TempList &DefinedVars() const { return dst; }

        const NIRTree::LabelList &JumpTargets() const { return labelList; }

        virtual std::string Format() const {
            std::string s = asmCode;
            std::string instructionString;
            unsigned int pos;
            while ((pos = s.find("%")) < s.size()) {
                instructionString += s.substr(0, pos);
                if (s[pos + 1] == 'l') {
                    instructionString += labelList.at(0)->String();
                } else if (s[pos + 1] - '0' < dst.size()) {
                    assert(dst.size() > 0);
                    instructionString += "r" + dst[0]->name + std::to_string(dst[0]->id);
                } else {
                    unsigned int srcPos = s[pos + 1] - '0' - dst.size();
                    assert(src.size() > srcPos);
                    instructionString += "r" + src[srcPos]->name + std::to_string(src[srcPos]->id);
                }
                s.erase(0, pos + 2);
            }
            instructionString += s;
            instructionString += "\tUsed:";
            for (auto &tmp: src) {
                instructionString += " r" + tmp->name + std::to_string(tmp->id) + ";";
            }
            instructionString += "\tDefined:";
            for (auto &tmp: dst) {
                instructionString += " r" + tmp->name + std::to_string(tmp->id) + ";";
            }
            return instructionString;
        }

    protected:
        NIRTree::TempList src;
        NIRTree::TempList dst;
        NIRTree::LabelList labelList;
        std::string asmCode;
    };

    class MoveInstruction : public IInstruction {
    public:
        MoveInstruction(const NIRTree::Temp *from, const NIRTree::Temp *to) : fromConst(0) {
            src.push_back(from);
            dst.push_back(to);
        }

        MoveInstruction(const NIRTree::TempList &&from) {
            src = from;
        }

        MoveInstruction(const NIRTree::Const *from, const NIRTree::Temp *to) : fromConst(from) { dst.push_back(to); }

    private:
        const NIRTree::Const *fromConst;
    };

    class LabelInstruction : public IInstruction {
    public:
        explicit LabelInstruction(const NIRTree::Label *l) { labelList.push_back(l); }

        virtual std::string Format() const override {
            return labelList[0]->String() + ":";
        }
    };

    struct InstructionList {
        std::vector<std::unique_ptr<const IInstruction>> instructions;
        std::vector<std::unique_ptr<const NIRTree::Temp>> registers;
    };

}
