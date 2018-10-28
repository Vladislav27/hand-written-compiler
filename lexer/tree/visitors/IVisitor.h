#pragma once

#include <lexer/tree/Common.h>
#include <lexer/tree/Class.h>
#include <lexer/tree/Program.h>
#include <lexer/tree/Expression.h>
#include <lexer/tree/Statement.h>
#include <lexer/tree/VarDeclaration.h>

namespace NTree {
    class IVisitor {
    public:
        virtual void Visit(const Program *) = 0;

        virtual void Visit(const MainClass *) = 0;

        virtual void Visit(const VarDeclaration *) = 0;


        virtual void Visit(const Statements *) = 0;
        virtual void Visit(const AssignStatement *) = 0;

        virtual void Visit(const BinaryExpression *) = 0;
        virtual void Visit(const IntegerLiteralExpression *) = 0;
        virtual void Visit(const BoolLiteralExpression *) = 0;
        virtual void Visit(const IdentifierExpression *) = 0;
        virtual void Visit(const NegateExpression *) = 0;
    };
}