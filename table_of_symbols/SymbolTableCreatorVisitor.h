#pragma once

#include "Common.h"

#include "IdentifierInfo.h"
#include "SymbolTable.h"

#include <abstr/tree/visitors/IVisitor.h>
#include <abstr/StringInterner.h>

#include <cassert>

namespace NSymbolTable {
    class SymbolTableCreatorVisitor : public NSyntaxTree::IVisitor {
        SymbolTable &symbolTable;

        std::unique_ptr<IdentifierInfo> returnValue;

        template<class TNodeInfo, class TIdentifierInfo, class TVector>
        void InsertAll(TIdentifierInfo *info
                , void (TIdentifierInfo::* insertFunction)(const TNodeInfo&)
                , const std::unordered_map<const Symbol *, TNodeInfo>& existedIds
                , const TVector& nodes) {
            for (const auto &node: nodes) {
                CheckIdentifier(existedIds, node->id, node->location);

                node->Accept(this);
                assert(returnValue);

                auto value = dynamic_cast<TNodeInfo *>(returnValue.get());
                assert(value);
                (info->*insertFunction)(*value);
            }
        }
    public:
        inline explicit SymbolTableCreatorVisitor(SymbolTable &table)
                : symbolTable(table) {
        }

        SymbolTableCreatorVisitor() = delete;

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