#include "SymbolTableCreatorVisitor.h"

namespace NSymbolTable {
    void SymbolTableCreatorVisitor::Visit(const NTree::Program *program) {
        InsertAll(&symbolTable, &SymbolTable::InsertClassInfo, symbolTable.GetClasses(), *program->classes);

        program->mainClass->Accept(this);

        if (symbolTable.HasClass(program->mainClass->nameId)) {
            auto e = new RedefinitionException(symbolTable.GetClasses().at(program->mainClass->nameId).GetLocation()
                    , program->mainClass->nameId
                    , symbolTable.GetMainClassLocation());
            std::cerr << e->what() << std::endl;
        }
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::ClassDeclaration *classDeclaration) {
        auto classInfo = new ClassInfo(classDeclaration->id
            , classDeclaration->location
            , classDeclaration->extendsId);

        InsertAll(classInfo, &ClassInfo::InsertVarInfo, classInfo->GetVarsInfo(), *classDeclaration->varDeclarations);
        InsertAll(classInfo, &ClassInfo::InsertMethodInfo, classInfo->GetMethodsInfo(), *classDeclaration->methodDeclarations);

        returnValue.reset(classInfo);
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::MainClass *mainClass) {
        symbolTable.SetMainClass(mainClass->nameId);
        symbolTable.SetMainClassLocation(mainClass->location);
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::VarDeclaration *var) {
        auto varInfo = new VariableInfo(var->id, var->location, var->type);

        returnValue.reset(varInfo);
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::MethodDeclaration *method) {
        auto methodInfo = new MethodInfo(method->id, method->location, method->returnType, method->modifier);

        InsertAll(methodInfo, &MethodInfo::InsertArgumentInfo, methodInfo->GetArgsMap(), *method->args);
        InsertAll(methodInfo, &MethodInfo::InsertVariableInfo, methodInfo->GetVarsInfo(), *method->localVars);

        returnValue.reset(methodInfo);
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::Statements *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::IfStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::WhileStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::PrintlnStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::AssignStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::ArrayElementAssignmentStatement *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::BinaryExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::ArrayElementAccessExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::ArrayLengthExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::MethodCallExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::IntegerLiteralExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::BoolLiteralExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::IdentifierExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::ThisExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::NewIntArrayExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::NewExpression *) {
    }

    void SymbolTableCreatorVisitor::Visit(const NTree::NegateExpression *) {
    }
}