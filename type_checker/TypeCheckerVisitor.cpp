#include "TypeCheckerVisitor.h"

#include "Exceptions.h"

namespace NTypeChecker {
    using uint32 = unsigned int;

    using namespace NSymbolTable;

    void TypeCheckerVisitor::Visit(const NTree::Program *program) {
        program->mainClass->Accept(this);

        for (const auto &clazz: *program->classes) {
            clazz->Accept(this);
        }
    }

    void TypeCheckerVisitor::Visit(const NTree::ClassDeclaration *clazz) {
        switcher.SwitchClass(new ClassInfo(symbolTable.GetClassInfo(clazz->id)));

        if (switcher.CurrentClass()->GetSuperClassId() != nullptr) {
            for (const auto &method: *clazz->methodDeclarations) {
                if (auto methodInfo = symbolTable.FindMethod(method->id, clazz->extendsId)) {
                    if (methodInfo->GetArgsInfo().size() != method->args->size()) {
                        throw RedefinitionException(method->location, method->id, methodInfo->GetLocation());
                    }

                    for (uint32 i = 0; i < method->args->size(); ++i) {
                        if (methodInfo->GetArgsInfo().at(i).GetTypeInfo() != method->args->at(i)->type) {
                            throw RedefinitionException(method->location, method->id, methodInfo->GetLocation());
                        }
                    }
                }
            }

            for (const auto &var: *clazz->varDeclarations) {
                if (auto varInfo = symbolTable.FindIdentifier(&symbolTable.GetClassInfo(clazz->extendsId), var->id)) {
                    throw RedefinitionException(var->location, var->id, varInfo->GetLocation());
                }
            }
        }

        for (const auto &method: *clazz->methodDeclarations) {
            method->Accept(this);
        }
    }

    void TypeCheckerVisitor::Visit(const NTree::MainClass *mainClass) {
        mainClass->mainStatement->Accept(this);
    }

    void TypeCheckerVisitor::Visit(const NTree::VarDeclaration *) {
    }

    void TypeCheckerVisitor::Visit(const NTree::MethodDeclaration *method) {
        switcher.SwitchMethod(new MethodInfo(switcher.CurrentClass()->GetMethodsInfo().at(method->id)));

        CheckExpressionType(method->returnExpression.get(), method->returnType);

        for (const auto &arg: *method->args) {
            if (auto varInfo = symbolTable.FindIdentifier(switcher.CurrentClass(), arg->id)) {
                throw RedefinitionException(arg->location, arg->id, varInfo->GetLocation());
            }

            TypeInfo type = arg->type;
            if (type.GetType() == CLASS && !symbolTable.HasClass(type.GetClassId())) {
                throw NonDeclaredSymbolException(arg->location, type.GetClassId());
            }
        }

        for (const auto &var: *method->localVars) {
            if (auto varInfo = symbolTable.FindIdentifier(switcher.CurrentClass(), var->id)) {
                throw RedefinitionException(var->location, var->id, varInfo->GetLocation());
            }

            if (switcher.CurrentMethod()->GetArgsMap().find(var->id) != switcher.CurrentMethod()->GetArgsMap().end()) {
                throw RedefinitionException(var->location, var->id, switcher.CurrentMethod()->GetArgsMap().at(var->id).GetLocation());
            }
        }

        for (const auto &statement: *method->statements) {
            statement->Accept(this);
        }
    }

    void TypeCheckerVisitor::Visit(const NTree::Statements *statements) {
        for (const auto &statement: *statements->statements) {
            statement->Accept(this);
        }
    }

    void TypeCheckerVisitor::Visit(const NTree::IfStatement *statement) {
        CheckExpressionType(statement->condition.get(), BooleanType);

        statement->trueStatement->Accept(this);
        statement->falseStatement->Accept(this);
    }

    void TypeCheckerVisitor::Visit(const NTree::WhileStatement *statement) {
        CheckExpressionType(statement->condition.get(), BooleanType);

        statement->trueStatement->Accept(this);
    }

    void TypeCheckerVisitor::Visit(const NTree::PrintlnStatement *statement) {
        CheckExpressionType(statement->toPrint.get(), IntType);
    }

    void TypeCheckerVisitor::Visit(const NTree::AssignStatement *statement) {
        statement->rvalue->Accept(this);

        const auto &variable = FindAndCheckIdentifier(*switcher.CurrentClass(), *switcher.CurrentMethod(), statement->lvalue, statement->location);

        if (*switcher.CurrentExprType() != variable.GetTypeInfo()) {
            throw IllegalTypeException(statement->rvalue->location, *switcher.CurrentExprType(), variable.GetTypeInfo());
        }
    }

    void TypeCheckerVisitor::Visit(const NTree::ArrayElementAssignmentStatement *statement) {
        CheckExpressionType(statement->index.get(), IntType);
        CheckExpressionType(statement->rvalue.get(), IntType);

        const auto &variable = FindAndCheckIdentifier(*switcher.CurrentClass(), *switcher.CurrentMethod(), statement->arrayId, statement->location);

        if (variable.GetTypeInfo() != IntArrayType) {
            throw IllegalTypeException(statement->location, variable.GetTypeInfo(), IntArrayType);
        }
    }

    void TypeCheckerVisitor::Visit(const NTree::BinaryExpression *expression) {
        if (expression->type == NTree::AND || expression->type == NTree::OR) {
            CheckExpressionType(expression->left.get(), BooleanType);
            CheckExpressionType(expression->right.get(), BooleanType);
            switcher.SwitchExprType(new TypeInfo(BOOL));
        }
        else {
            CheckExpressionType(expression->left.get(), IntType);
            CheckExpressionType(expression->right.get(), IntType);
            if (expression->type == NTree::LESS)
                switcher.SwitchExprType(new TypeInfo(BOOL));
            else
                switcher.SwitchExprType(new TypeInfo(INT));
        }
    }

    void TypeCheckerVisitor::Visit(const NTree::ArrayElementAccessExpression *expression) {
        CheckExpressionType(expression->array.get(), IntArrayType);
        CheckExpressionType(expression->index.get(), IntType);

        switcher.SwitchExprType(new TypeInfo(INT));
    }

    void TypeCheckerVisitor::Visit(const NTree::ArrayLengthExpression *expression) {
        CheckExpressionType(expression->array.get(), IntArrayType);

        switcher.SwitchExprType(new TypeInfo(INT));
    }

    void TypeCheckerVisitor::Visit(const NTree::MethodCallExpression *expression) {
        // check object type
        expression->object->Accept(this);
        TypeInfo objectType = *switcher.CurrentExprType();

        if (objectType.GetType() != NSymbolTable::CLASS) {
            throw IllegalTypeException(expression->object->location, objectType);
        }

        // check call (including public/private access)
        auto method = FindAndCheckMethod(expression->nameId, objectType.GetClassId(), expression->location);

        if (method.GetArgsInfo().size() != expression->args->size()) {
            throw BadArgumentsException(expression->location);
        }

        for (uint32 i = 0; i < expression->args->size(); ++i) {
            expression->args->at(i)->Accept(this);
            if (!IsSimilarTypes(*switcher.CurrentExprType(), method.GetArgsInfo().at(i).GetTypeInfo())) {
                throw IllegalTypeException(expression->args->at(i)->location, *switcher.CurrentExprType(), method.GetArgsInfo().at(i).GetTypeInfo());
            }
        }

        switcher.SwitchExprType(new TypeInfo(method.GetReturnType()));
    }

    void TypeCheckerVisitor::Visit(const NTree::IntegerLiteralExpression *) {
        switcher.SwitchExprType(new TypeInfo(INT));
    }

    void TypeCheckerVisitor::Visit(const NTree::BoolLiteralExpression *) {
        switcher.SwitchExprType(new TypeInfo(BOOL));
    }

    void TypeCheckerVisitor::Visit(const NTree::IdentifierExpression *expression) {
        const auto &type = FindAndCheckIdentifier(*switcher.CurrentClass(), *switcher.CurrentMethod(), expression->identifier, expression->location);
        switcher.SwitchExprType(new TypeInfo(type.GetTypeInfo()));
    }

    void TypeCheckerVisitor::Visit(const NTree::ThisExpression *) {
        switcher.SwitchExprType(new TypeInfo(CLASS, switcher.CurrentClass()->GetId()));
    }

    void TypeCheckerVisitor::Visit(const NTree::NewIntArrayExpression *expression) {
        CheckExpressionType(expression->size.get(), IntType);

        switcher.SwitchExprType(new TypeInfo(INT_ARRAY));
    }

    void TypeCheckerVisitor::Visit(const NTree::NewExpression *expression) {
        if (!symbolTable.HasClass(expression->classId)) {
            throw NSymbolTable::NonDeclaredSymbolException(expression->location, expression->classId);
        }

        switcher.SwitchExprType(new TypeInfo(CLASS, expression->classId));
    }

    void TypeCheckerVisitor::Visit(const NTree::NegateExpression *expression) {
        CheckExpressionType(expression->expression.get(), BooleanType);

        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::BOOL));
    }



    const MethodInfo& TypeCheckerVisitor::FindAndCheckMethod(const Symbol *methodId
            , const Symbol *classId
            , const Location &location) const {
        auto classInfo = symbolTable.GetClassInfo(classId);

        while (!classInfo.HasMethod(methodId) && classInfo.GetSuperClassId() != nullptr) {
            classInfo = symbolTable.GetClassInfo(classInfo.GetSuperClassId());
        }

        auto method = symbolTable.FindMethod(methodId, classId);

        if (!method) {
            throw NonDeclaredSymbolException(location, methodId);
        }

        if (method->GetModifier() == NTree::PRIVATE && classInfo.GetId() != switcher.CurrentClass()->GetId()) {
            throw PrivateAccessException(location, methodId, classInfo.GetId());
        }

        return *method;
    }

    void TypeCheckerVisitor::CheckExpressionType(const NTree::IExpression *expression, const TypeInfo &expected) {
        expression->Accept(this);
        if (*switcher.CurrentExprType() != expected) {
            throw IllegalTypeException(expression->location, *switcher.CurrentExprType(), expected);
        }
    }

    const NSymbolTable::VariableInfo &TypeCheckerVisitor::FindAndCheckIdentifier(const ClassInfo &clazzInfo
            , const MethodInfo &methodInfo
            , const NSymbolTable::Symbol *id
            , const Location &location) const {
        auto idInfo = symbolTable.FindIdentifier(&clazzInfo, id, &methodInfo);

        if (idInfo != nullptr) {
            return *idInfo;
        }

        throw NonDeclaredSymbolException(location, id);
    }

    bool TypeCheckerVisitor::IsSimilarTypes(const TypeInfo &first, const TypeInfo &second) const {
        if (first.GetType() != CLASS || second.GetType() != CLASS)
            return first == second;

        auto clazz = symbolTable.GetClassInfo(first.GetClassId());
        while (clazz.GetId() != second.GetClassId() && clazz.GetSuperClassId()) {
            clazz = symbolTable.GetClassInfo(clazz.GetSuperClassId());
        }

        return clazz.GetId() == second.GetClassId();
    }
}