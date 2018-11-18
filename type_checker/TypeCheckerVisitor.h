#pragma once

#include <abstr/tree/visitors/IVisitor.h>
#include <table_of_symbols/SymbolTable.h>
#include <table_of_symbols/ScopeSwitcher.h>

#include <memory>

namespace NTypeChecker {
    class TypeCheckerVisitor: public NTree::IVisitor {
        const NSymbolTable::SymbolTable &symbolTable;

        NSymbolTable::ScopeSwitcher switcher;

        const NSymbolTable::MethodInfo& FindAndCheckMethod(const NTree::Symbol*
                , const NTree::Symbol*
                , const NTree::Location&) const;
        const NSymbolTable::VariableInfo& FindAndCheckIdentifier(const NSymbolTable::ClassInfo&
                , const NSymbolTable::MethodInfo&
                , const NTree::Symbol*
                , const NTree::Location&) const;

        bool IsSimilarTypes(const NSymbolTable::TypeInfo&, const NSymbolTable::TypeInfo&) const;

        void CheckExpressionType(const NTree::IExpression*, const NSymbolTable::TypeInfo&);
    public:
        explicit TypeCheckerVisitor(const NSymbolTable::SymbolTable &symbolTable) : symbolTable(symbolTable) {
        }

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
    };
}
