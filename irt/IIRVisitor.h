#pragma once

#include "NodeTypes.h"

#include <irt/CommonDefs.h>

namespace NIRTree {
    interface IIRVisitor {
        virtual void Visit(const Binop*) = 0;
        virtual void Visit(const Call*) = 0;
        virtual void Visit(const Const*) = 0;
        virtual void Visit(const ESeq*) = 0;
        virtual void Visit(const Mem*) = 0;
        virtual void Visit(const Name*) = 0;
        virtual void Visit(const Temp*) = 0;
        virtual void Visit(const Unop*) = 0;

        virtual void Visit(const CJump*) = 0;
        virtual void Visit(const Exp*) = 0;
        virtual void Visit(const Jump*) = 0;
        virtual void Visit(const LabelStm*) = 0;
        virtual void Visit(const Move*) = 0;

        virtual void Visit(const StmList*) = 0;
        virtual void Visit(const ExpList*) = 0;

        virtual void Visit(const ExprWrapper*) = 0;
        virtual void Visit(const StmWrapper*) = 0;
    };
}