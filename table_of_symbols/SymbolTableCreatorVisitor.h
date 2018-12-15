#pragma once

#include "Common.h"

#include "IdentifierInfo.h"
#include "SymbolTable.h"

#include <abstr/tree/visitors/IVisitor.h>
#include <abstr/StringInterner.h>

#include <cassert>

namespace NSymbolTable {
    class SymbolTableCreatorVisitor : public NTree::IVisitor {
        SymbolTable &symbolTable;

        std::unique_ptr<IdentifierInfo> returnValue;

        template<class TNodeInfo, class TIdentifierInfo, class TVector>
        void InsertAll(TIdentifierInfo *info
                , void (TIdentifierInfo::* insertFunction)(const TNodeInfo&)
                , const std::unordered_map<const NTree::Symbol *, TNodeInfo>& existedIds
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
        explicit SymbolTableCreatorVisitor(SymbolTable &table)
                : symbolTable(table) {
        }

        SymbolTableCreatorVisitor() = delete;

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