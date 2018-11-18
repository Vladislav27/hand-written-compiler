#pragma once

#include <abstr/tree/visitors/IVisitor.h>
#include <table_of_symbols/SymbolTable.h>
#include <table_of_symbols/ScopeSwitcher.h>

#include <memory>

namespace NTypeChecker {
    class TypeCheckerVisitor: public NSyntaxTree::IVisitor {
        const NSymbolTable::SymbolTable &symbolTable;

        NSymbolTable::ScopeSwitcher switcher;

        const NSymbolTable::MethodInfo& FindAndCheckMethod(const NSymbolTable::Symbol*
                , const NSymbolTable::Symbol*
                , const NSyntaxTree::Location&) const;
        const NSymbolTable::VariableInfo& FindAndCheckIdentifier(const NSymbolTable::ClassInfo&
                , const NSymbolTable::MethodInfo&
                , const NSymbolTable::Symbol*
                , const NSyntaxTree::Location&) const;

        bool IsSimilarTypes(const NSymbolTable::TypeInfo&, const NSymbolTable::TypeInfo&) const;

        void CheckExpressionType(const NSyntaxTree::IExpression*, const NSymbolTable::TypeInfo&);
    public:
        explicit TypeCheckerVisitor(const NSymbolTable::SymbolTable &symbolTable) : symbolTable(symbolTable) {
        }

        void Visit(const NSyntaxTree::Program *) override;

        void Visit(const NSyntaxTree::ClassDeclaration *) override;

        void Visit(const NSyntaxTree::MainClass *) override;

        void Visit(const NSyntaxTree::VarDeclaration *) override;

        void Visit(const NSyntaxTree::MethodDeclaration *) override;

        void Visit(const NSyntaxTree::Statements *) override;

        void Visit(const NSyntaxTree::IfStatement *) override;

        void Visit(const NSyntaxTree::WhileStatement *) override;

        void Visit(const NSyntaxTree::PrintlnStatement *) override;

        void Visit(const NSyntaxTree::AssignStatement *) override;

        void Visit(const NSyntaxTree::ArrayElementAssignmentStatement *) override;

        void Visit(const NSyntaxTree::BinaryExpression *) override;

        void Visit(const NSyntaxTree::ArrayElementAccessExpression *) override;

        void Visit(const NSyntaxTree::ArrayLengthExpression *) override;

        void Visit(const NSyntaxTree::MethodCallExpression *) override;

        void Visit(const NSyntaxTree::IntegerLiteralExpression *) override;

        void Visit(const NSyntaxTree::BoolLiteralExpression *) override;

        void Visit(const NSyntaxTree::IdentifierExpression *) override;

        void Visit(const NSyntaxTree::ThisExpression *) override;

        void Visit(const NSyntaxTree::NewIntArrayExpression *) override;

        void Visit(const NSyntaxTree::NewExpression *) override;

        void Visit(const NSyntaxTree::NegateExpression *) override;
    };
}
