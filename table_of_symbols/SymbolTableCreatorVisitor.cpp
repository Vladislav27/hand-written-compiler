#include "SymbolTableCreatorVisitor.h"

namespace NSymbolTable {
    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::Program *program) {
        InsertAll(&symbolTable, &SymbolTable::InsertClassInfo, symbolTable.GetClasses(), *program->classes);

        program->mainClass->Accept(this);

        if (symbolTable.HasClass(program->mainClass->nameId)) {
            throw RedefinitionException(symbolTable.GetClasses().at(program->mainClass->nameId).GetLocation()
                    , program->mainClass->nameId
                    , symbolTable.GetMainClassLocation());
        }
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::ClassDeclaration *classDeclaration) {
        auto classInfo = new ClassInfo(classDeclaration->id
            , classDeclaration->location
            , classDeclaration->extendsId);

        InsertAll(classInfo, &ClassInfo::InsertVarInfo, classInfo->GetVarsInfo(), *classDeclaration->varDeclarations);
        InsertAll(classInfo, &ClassInfo::InsertMethodInfo, classInfo->GetMethodsInfo(), *classDeclaration->methodDeclarations);

        returnValue.reset(classInfo);
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::MainClass *mainClass) {
        symbolTable.SetMainClass(mainClass->nameId);
        symbolTable.SetMainClassLocation(mainClass->location);
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::VarDeclaration *var) {
        auto varInfo = new VariableInfo(var->id, var->location, var->type);

        returnValue.reset(varInfo);
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::MethodDeclaration *method) {
        auto methodInfo = new MethodInfo(method->id, method->location, method->returnType, method->modifier);

        InsertAll(methodInfo, &MethodInfo::InsertArgumentInfo, methodInfo->GetArgsMap(), *method->args);
        InsertAll(methodInfo, &MethodInfo::InsertVariableInfo, methodInfo->GetVarsInfo(), *method->localVars);

        returnValue.reset(methodInfo);
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::Statements *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::IfStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::WhileStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::PrintlnStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::AssignStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::ArrayElementAssignmentStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::BinaryExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::ArrayElementAccessExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::ArrayLengthExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::MethodCallExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::IntegerLiteralExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::BoolLiteralExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::IdentifierExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::ThisExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::NewIntArrayExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::NewExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NSyntaxTree::NegateExpression *) {
    }
}