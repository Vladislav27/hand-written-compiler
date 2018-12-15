#pragma once

#include <abstr/tree/visitors/IVisitor.h>

#include <irt/common.h>
#include <irt/ISubtreeWrapper.h>
#include <irt/activation_records/IFrame.h>
#include <irt/activation_records/ClassStruct.h>

#include <abstr/StringInterner.h>
#include <table_of_symbols/SymbolTable.h>
#include <table_of_symbols/ScopeSwitcher.h>

#include <unordered_map>

namespace NIRTree {
    class IRBuilderVisitor: public NTree::IVisitor {
    public:
        IRBuilderVisitor(const IClassStructBuilder*, const IFrameBuilder*, const NSymbolTable::SymbolTable &);

        IRForest CreateForest(const NTree::Program &program);

        void Visit(const NTree::Program *) override;

        void Visit(const NTree::ClassDeclaration *) override;

        void Visit(const NTree::MainClass *) override;

        void Visit(const NTree::VarDeclaration *) override;

        void Visit(const NTree::MethodDeclaration *) override;

        void Visit(const NTree::Statements *) override;

        void Visit(const NTree::IfStatement *) override;

        void Visit(const NTree::WhileStatement *) override;

        void Visit(const NTree::PrintlnStatement *) override;

        void Visit(const NTree::AssignStatement *) override;

        void Visit(const NTree::ArrayElementAssignmentStatement *) override;

        void Visit(const NTree::BinaryExpression *) override;

        void Visit(const NTree::ArrayElementAccessExpression *) override;

        void Visit(const NTree::ArrayLengthExpression *) override;

        void Visit(const NTree::MethodCallExpression *) override;

        void Visit(const NTree::IntegerLiteralExpression *) override;

        void Visit(const NTree::BoolLiteralExpression *) override;

        void Visit(const NTree::IdentifierExpression *) override;

        void Visit(const NTree::ThisExpression *) override;

        void Visit(const NTree::NewIntArrayExpression *) override;

        void Visit(const NTree::NewExpression *) override;

        void Visit(const NTree::NegateExpression *) override;

    private:
        using SubtreePtr = std::unique_ptr<ISubtreeWrapper>;
        std::unique_ptr<ISubtreeWrapper> mainSubtree;
        std::unique_ptr<IFrame> frame;

        NSymbolTable::ScopeSwitcher switcher;

        const IClassStructBuilder* classStructBuilder;
        const IFrameBuilder* frameBuilder;
        const NSymbolTable::SymbolTable &symbolTable;

        std::unordered_map<const Symbol*, SubtreePtr> forest;
    };
}