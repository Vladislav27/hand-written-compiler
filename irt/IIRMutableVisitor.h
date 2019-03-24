#pragma once

#include "NodeTypes.h"

#include <util/CommonDefs.h>

namespace NIRTree {
    interface IIRMutableVisitor {
        virtual void Visit(Binop*) = 0;
        virtual void Visit(Call*) = 0;
        virtual void Visit(Const*) = 0;
        virtual void Visit(ESeq*) = 0;
        virtual void Visit(Mem*) = 0;
        virtual void Visit(Name*) = 0;
        virtual void Visit(Temp*) = 0;
        virtual void Visit(Unop*) = 0;

        virtual void Visit(CJump*) = 0;
        virtual void Visit(Exp*) = 0;
        virtual void Visit(Jump*) = 0;
        virtual void Visit(LabelStm*) = 0;
        virtual void Visit(Move*) = 0;

        virtual void Visit(StmList*) = 0;
        virtual void Visit(ExpList*) = 0;

        virtual void Visit(ExprWrapper*) = 0;
        virtual void Visit(StmWrapper*) = 0;
    };
}