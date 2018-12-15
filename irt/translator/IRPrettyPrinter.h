#pragma once

#include <irt/IIRVisitor.h>
#include <irt/DotPrinter.h>

#include <iostream>

namespace NIRTree {
    class IRPrettyPrinter : public IIRVisitor, public NIRTree::DotPrinter {
        std::ostream& outPut;
    public:
        inline explicit IRPrettyPrinter(std::ostream& _outPut = std::cout) : outPut(_outPut) {}

        void Visit(const IRForest &forest);

        ~IRPrettyPrinter() = default;

        void printVertex(const INode* node, const std::string& label);
        void printEdge(const INode* from, const INode * to);
        void printEdge(const INode* from, const INode * to, const std::string& label);

        void Visit(const Binop *) override;
        void Visit(const Call *) override;
        void Visit(const Const *) override;
        void Visit(const ESeq *) override;
        void Visit(const Mem *) override;
        void Visit(const Name *) override;
        void Visit(const Temp *) override;
        void Visit(const Unop *) override;

        void Visit(const CJump *) override;
        void Visit(const Exp *) override;
        void Visit(const Jump *) override;
        void Visit(const Move *) override;
        void Visit(const LabelStm*) override;

        void Visit(const ExprWrapper *) override;
        void Visit(const StmWrapper *) override;

        void Visit(const ExpList *) override;
        void Visit(const StmList *) override;
    };
}