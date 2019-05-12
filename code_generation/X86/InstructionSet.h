#pragma once

#include <code_generation/Instructions.h>

#include <utility>

namespace NCodeGeneration {

    enum ERegs {
        EAX,
        EBX,
        ECX,
        EDX
    };

    class CISCOperation: public IInstruction {
    public:
        CISCOperation(std::string code, const NIRTree::TempList&& srcList,
                      const NIRTree::TempList&& dstList, const NIRTree::LabelList&& targetLabels)
        {
            src = srcList;
            dst = dstList;
            labelList = targetLabels;
            asmCode = std::move(code);
        }

        CISCOperation(std::string code, const NIRTree::TempList&& srcList,
                      const NIRTree::TempList&& dstList)
        {
            src = srcList;
            dst = dstList;
            asmCode = std::move(code);
        }
    };

    class RegMove: public MoveInstruction {
    public:
        RegMove(const std::string code, const NIRTree::Temp* from, const NIRTree::Temp* to);
        RegMove(const std::string code, const NIRTree::TempList&& from);
        RegMove(const std::string code, const NIRTree::Const* from, const NIRTree::Temp* to);
    };

}
