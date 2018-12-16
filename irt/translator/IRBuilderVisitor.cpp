#include "IRBuilderVisitor.h"

#include "ExprWrapper.h"
#include "StmWrapper.h"
#include "NameConventions.h"

#include <irt/NodeTypes.h>
#include <irt/activation_records/ArrayStruct.h>

#include <vector>

namespace NIRTree {

    void IRBuilderVisitor::Visit(const NTree::Program *program) {
        program->mainClass->Accept(this);

        for (const auto &clazz: *program->classes) {
            clazz->Accept(this);
        }
    }

    void IRBuilderVisitor::Visit(const NTree::MainClass *clazz) {
        clazz->mainStatement->Accept(this);
        assert(mainSubtree != nullptr);

        const auto id = symbolTable.GetInterner()->GetIntern(clazz->nameId->String() + "@MAIN");
        auto subtree = SubtreePtr(mainSubtree.release());

        forest.insert(std::make_pair(id, std::move(subtree)));

    }

    void IRBuilderVisitor::Visit(const NTree::ClassDeclaration *clazz) {
        switcher.SwitchClass(new NSymbolTable::ClassInfo(symbolTable.GetClassInfo(clazz->id)));
        for (const auto &method: *clazz->methodDeclarations) {
            method->Accept(this);
            assert(mainSubtree != nullptr);

            const auto id = symbolTable.GetInterner()->GetIntern(clazz->id->String()
                                                                 + "@" + method->id->String());
            auto subtree = SubtreePtr(mainSubtree.release());
            forest.insert(std::make_pair(id, std::move(subtree)));
        }
    }

    void IRBuilderVisitor::Visit(const NTree::IntegerLiteralExpression *expr) {
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::INT));
        mainSubtree.reset(new ExprWrapper(new Const(expr->value, expr->location)));
    }

    void IRBuilderVisitor::Visit(const NTree::BoolLiteralExpression *expr) {
        // TODO: Here we loose information about type. Maybe, it is bad
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::BOOL));
        mainSubtree.reset(new ExprWrapper(new Const(expr->value, expr->location)));
    }

    void IRBuilderVisitor::Visit(const NTree::NewIntArrayExpression *expr) {
        expr->size->Accept(this);
        assert(mainSubtree != nullptr);
        auto size = mainSubtree->ToExp();

        auto args = new ExpList(
                new Binop(Binop::MULTIPLY, size,
                          new Const(frame->TypeSize(NSymbolTable::IntType), expr->location), expr->location),
                nullptr, expr->location);

        mainSubtree.reset(new ExprWrapper(
                new Call(new Name(NNameConventions::MallocName, expr->location), args, expr->location)));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::INT_ARRAY));
    }

    void IRBuilderVisitor::Visit(const NTree::NewExpression *expr) {
        const auto &classInfo = symbolTable.GetClassInfo(expr->classId);
        std::unique_ptr<IClassStruct> classStruct(classStructBuilder->GetClassStruct(classInfo, symbolTable));
        IExp *allocActions = classStruct->AllocateNew(expr->location);
        mainSubtree.reset(new ExprWrapper(allocActions));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::CLASS, expr->classId));
    }

    void IRBuilderVisitor::Visit(const NTree::NegateExpression *expr) {
        expr->expression->Accept(this);
        mainSubtree.reset(new ExprWrapper(new Unop(Unop::NOT, mainSubtree->ToExp(), expr->location)));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::BOOL));
    }

    void IRBuilderVisitor::Visit(const NTree::IdentifierExpression *expr) {
        auto varAccess = frame->GetFormalOrLocal(expr->identifier);
        IExp *varExp = nullptr;

        if (varAccess != nullptr) {
            varExp = varAccess->GetExp(new Temp("fp", expr->location), expr->location);
        } else {
            assert(switcher.CurrentClass() != nullptr);
            std::unique_ptr<IClassStruct> scopedClassStruct(
                    classStructBuilder->GetClassStruct(*switcher.CurrentClass(), symbolTable));
            auto access = frame->GetFormalOrLocal(
                    symbolTable.GetInterner()->GetIntern("this"));
            varExp = scopedClassStruct->GetFieldFrom(
                    expr->identifier,
                    access->GetExp(
                            new Temp("fp", expr->location), expr->location),
                    expr->location);
        }

        auto info = symbolTable.FindIdentifier(switcher.CurrentClass(), expr->identifier, switcher.CurrentMethod());
        if (info->GetTypeInfo().GetType() != NSymbolTable::CLASS) {
            switcher.SwitchExprType(new NSymbolTable::TypeInfo(info->GetTypeInfo().GetType(), nullptr));
        }
        else {
            switcher.SwitchExprType(
                    new NSymbolTable::TypeInfo(NSymbolTable::CLASS, info->GetTypeInfo().GetClassId()));
        }
        mainSubtree.reset(new ExprWrapper(varExp));
    }

    void IRBuilderVisitor::Visit(const NTree::ThisExpression *expr) {
        mainSubtree.reset(new ExprWrapper(
                new Mem(frame->GetFormalOrLocal(symbolTable.GetInterner()->GetIntern("this"))->GetExp(
                        new Temp("fp", expr->location), expr->location),
                        expr->location)));
        assert(switcher.CurrentClass() != nullptr);
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::CLASS, switcher.CurrentClass()->GetId()));
    }

    void IRBuilderVisitor::Visit(const NTree::ArrayLengthExpression *expr) {
        expr->array->Accept(this);
        IExp *arrayBase = mainSubtree->ToExp();
        mainSubtree.reset(new ExprWrapper(ArrayStruct::GetLength(arrayBase, expr->location)));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::INT));
    }

    void IRBuilderVisitor::Visit(const NTree::ArrayElementAccessExpression *expr) {
        expr->array->Accept(this);
        IExp *arrayBase = mainSubtree->ToExp();
        expr->index->Accept(this);
        IExp *elementNumber = mainSubtree->ToExp();
        mainSubtree.reset(new ExprWrapper(ArrayStruct::GetElement(arrayBase, elementNumber, expr->location)));
        switcher.SwitchExprType(new NSymbolTable::TypeInfo(NSymbolTable::INT));
    }

    void IRBuilderVisitor::Visit(const NTree::MethodCallExpression *expr) {
        expr->object->Accept(this);
        Temp* baseAddress = new Temp(0, expr->location);
        IExp *baseExp = new ESeq(new Move(baseAddress, mainSubtree->ToExp(), expr->location),
                                 new Mem(new Temp(*baseAddress), expr->location), expr->location);

        assert(switcher.CurrentExprType() != nullptr);
        NSymbolTable::TypeInfo info = *switcher.CurrentExprType();
        assert(info.GetType() == NSymbolTable::CLASS);

        auto arguments = new ExpList(baseExp, nullptr, expr->location);
        for (const auto &arg: *expr->args) {
            arg->Accept(this);
            arguments = new ExpList(mainSubtree->ToExp(), arguments, expr->location);
        }

        auto classInfo = symbolTable.GetClassInfo(info.GetClassId());
        std::unique_ptr<IClassStruct> classStruct(classStructBuilder->GetClassStruct(classInfo, symbolTable));
        IExp *methodAddress = classStruct->GetVirtualMethodAddress(
                expr->nameId, new Temp(*baseAddress), expr->location);
        mainSubtree.reset(new ExprWrapper(new Call(methodAddress, arguments, expr->location)));
    }

    void IRBuilderVisitor::Visit(const NTree::PrintlnStatement *stm) {
        stm->toPrint->Accept(this);
        mainSubtree.reset(new ExprWrapper(new Call(new Name("println", stm->location),
                                                   new ExpList(mainSubtree->ToExp(), nullptr, stm->location),
                                                   stm->location)));
    }

    void IRBuilderVisitor::Visit(const NTree::WhileStatement *stm) {
        stm->condition->Accept(this);

        Label *conditionLabel = LabelHolder::GetNextLabel();
        Label *exitLabel = LabelHolder::GetNextLabel();

        IStm *condition = mainSubtree->ToConditional(CJump::NEQ, exitLabel);
        IStm *conditionPart = new Seq(new LabelStm(conditionLabel, stm->location),
                                      condition, stm->location);
        stm->trueStatement->Accept(this);
        IStm *bodyPart = new Seq(mainSubtree->ToStm(), new Jump(conditionLabel, stm->location),
                                 stm->location);
        mainSubtree.reset(new StmWrapper(new Seq(new Seq(conditionPart, bodyPart, stm->location),
                                                 new LabelStm(exitLabel, stm->location),
                                                 stm->location)));
    }

    void IRBuilderVisitor::Visit(const NTree::Statements *node) {
        std::vector<IStm *> statements;
        for (auto &statement: *node->statements) {
            statement->Accept(this);
            statements.push_back(mainSubtree->ToStm());
        }
        assert(!statements.empty());
        if (statements.size() == 1) {
            mainSubtree.reset(new StmWrapper(statements[0]));
        } else {
            IStm *seq = new Seq(statements[0], statements[1], node->location);
            for (size_t i = 2; i < statements.size(); ++i) {
                seq = new Seq(seq, statements[i], node->location);
            }
            mainSubtree.reset(new StmWrapper(seq));
        }
    }

    void IRBuilderVisitor::Visit(const NTree::AssignStatement *stm) {
        stm->rvalue->Accept(this);
        auto identifierName = stm->lvalue;
        std::shared_ptr<const IAccess> access = frame->GetFormalOrLocal(identifierName);
        IExp *baseAddresss = nullptr;

        if (access != nullptr) {
            baseAddresss = access->GetExp(new Temp("fp", stm->location), stm->location);
        } else {
            auto classInfo = *switcher.CurrentClass();
            std::unique_ptr<IClassStruct> classStruct(classStructBuilder->GetClassStruct(classInfo, symbolTable));
            baseAddresss = classStruct->GetFieldFrom(
                    identifierName,
                    frame->GetFormalOrLocal(
                            symbolTable.GetInterner()->GetIntern("this")
                    )->GetExp(new Temp("fp", stm->location), stm->location),
                    stm->location);
        }
        mainSubtree.reset(new StmWrapper(new Move(baseAddresss, mainSubtree->ToExp(), stm->location)));
    }

    void IRBuilderVisitor::Visit(const NTree::ArrayElementAssignmentStatement *stm) {
        stm->index->Accept(this);
        std::unique_ptr<ISubtreeWrapper> elementNumberExp(mainSubtree.release());
        stm->rvalue->Accept(this);

        auto identifierName = stm->arrayId;
        std::shared_ptr<const IAccess> access = frame->GetFormalOrLocal(identifierName);
        IExp *baseAddresss = nullptr;

        if (access != nullptr) {
            baseAddresss = access->GetExp(new Temp("fp", stm->location), stm->location);
        } else {
            auto classInfo = *switcher.CurrentClass();
            std::unique_ptr<IClassStruct> classStruct(classStructBuilder->GetClassStruct(classInfo, symbolTable));
            baseAddresss = classStruct->GetFieldFrom(
                    identifierName,
                    frame->GetFormalOrLocal(
                            symbolTable.GetInterner()->GetIntern("this")
                    )->GetExp(new Temp("fp", stm->location), stm->location), stm->location);
        }
        // TODO: тут должен быть WordType, а не IntType. Но увы
        IExp* address = new Mem(new Binop(Binop::PLUS, baseAddresss,
                                          new Binop(Binop::MULTIPLY,
                                                    new Const(frame->TypeSize(NSymbolTable::IntType),
                                                              stm->location),
                                                    elementNumberExp->ToExp(), stm->location),
                                          stm->location),
                                stm->location);
        mainSubtree.reset(new StmWrapper(new Move(address, mainSubtree->ToExp(), stm->location)));
    }

    void IRBuilderVisitor::Visit(const NTree::IfStatement *stm) {
        stm->condition->Accept(this);
        Label* elseBranchLabel = LabelHolder::GetNextLabel();
        Label* exitLabel = LabelHolder::GetNextLabel();

        IStm* condition = mainSubtree->ToConditional(CJump::NEQ, elseBranchLabel);

        stm->trueStatement->Accept(this);
        IStm* ifPart = new Seq(mainSubtree->ToStm(),
                               new Jump(exitLabel, stm->location),
                               stm->location);

        stm->falseStatement->Accept(this);
        IStm* elsePart = new Seq(new Seq(new LabelStm(elseBranchLabel, stm->location),
                                         mainSubtree->ToStm(), stm->location),
                                 new Jump(exitLabel, stm->location),
                                 stm->location);
        mainSubtree.reset(new StmWrapper(new Seq(new Seq(condition, new Seq(ifPart, elsePart, stm->location),
                                                         stm->location), new LabelStm(exitLabel, stm->location),
                                                 stm->location)));
    }

    void IRBuilderVisitor::Visit(const NTree::MethodDeclaration *node) {
        const auto &methodInfo = switcher.CurrentClass()->GetMethodsInfo().at(node->id);
        switcher.SwitchMethod(new NSymbolTable::MethodInfo(methodInfo));

        frame.reset(frameBuilder->GetFrame(*switcher.CurrentClass(), methodInfo, symbolTable));
        IStm* stm = nullptr;
        if( !node->statements->empty() ) {

            for (const auto &statement: *node->statements) {
                statement->Accept(this);
            }
            stm = new StmList(mainSubtree->ToStm(), nullptr, node->location);
        }
        node->returnExpression->Accept(this);
        if(stm != nullptr) {
            stm = new StmList(stm, mainSubtree->ToStm(), node->location);
        } else {
            stm = mainSubtree->ToStm();
        }
        auto name = switcher.CurrentClass()->GetId()->String() + "@" + methodInfo.GetId()->String();
        forest.insert(std::make_pair(symbolTable.GetInterner()->GetIntern(name), std::unique_ptr<ISubtreeWrapper>(new StmWrapper(stm))));
    }

    void IRBuilderVisitor::Visit(const NTree::BinaryExpression *expr) {
        // for "less" case
        Label* trueLabel;
        Label* falseLabel;
        Label* returnLabel;
        IStm* condition;
        Temp* expValue;
        IStm* trueBranch;
        IStm* falseBranch;
        // for all cases
        IExp* result;
        expr->left->Accept(this);
        IExp* left = mainSubtree->ToExp();
        expr->right->Accept(this);
        IExp* right = mainSubtree->ToExp();

        switch (expr->type) {
            case NTree::MINUS:
                result = new Binop(Binop::MINUS, left, right, expr->location);
                break;
            case NTree::MULTIPLY:
                result = new Binop(Binop::MULTIPLY, left, right, expr->location);
                break;
            case NTree::PLUS:
                result = new Binop(Binop::PLUS, left, right, expr->location);
                break;
            case NTree::LESS:
                trueLabel = LabelHolder::GetNextLabel();
                falseLabel = LabelHolder::GetNextLabel();
                returnLabel = LabelHolder::GetNextLabel();
                condition = new CJump(CJump::LT, left, right, trueLabel,
                                      expr->location);
                expValue = new Temp("expValue", expr->location);
                trueBranch = new Seq(new Seq(new LabelStm(trueLabel, expr->location),
                                             new Move(expValue, new Const(1, expr->location), expr->location),
                                             expr->location),
                                     new Jump(returnLabel, expr->location), expr->location);
                falseBranch = new Seq(new Seq(new LabelStm(falseLabel, expr->location),
                                              new Move(new Temp(*expValue),
                                                       new Const(0, expr->location),
                                                       expr->location), expr->location),
                                      new Jump(returnLabel, expr->location),
                                      expr->location);
                result = new ESeq(new Seq(new Seq(new Seq(condition, falseBranch, expr->location),
                                                  trueBranch, expr->location),
                                          new LabelStm(returnLabel, expr->location), expr->location),
                                  new Mem(new Temp(*expValue), expr->location), expr->location);
                break;
            case NTree::AND:
                falseLabel = LabelHolder::GetNextLabel();
                returnLabel = LabelHolder::GetNextLabel();
                expValue = new Temp("expValue", expr->location);
                condition = new CJump(CJump::NEQ, left, new Const(1, expr->location), falseLabel, expr->location);
                trueBranch = new Seq(new CJump(CJump::NEQ, right, new Const(1, expr->location), falseLabel, expr->location),
                                     new Seq(
                                             new Move(expValue, new Const(1, expr->location), expr->location),
                                             new Jump(returnLabel, expr->location),
                                             expr->location
                                     ),
                                     expr->location
                );
                falseBranch = new Seq(
                        new LabelStm(falseLabel, expr->location),
                        new Seq(
                                new Move(new Temp(*expValue), new Const(0, expr->location), expr->location),
                                new Jump(returnLabel, expr->location),
                                expr->location
                        ),
                        expr->location
                );
                result = new ESeq(
                        new Seq(
                                new Seq(
                                        new Seq(
                                                condition,
                                                trueBranch,
                                                expr->location
                                        ),
                                        falseBranch,
                                        expr->location
                                ),
                                new LabelStm(returnLabel, expr->location)),
                        new Mem(new Temp(*expValue), expr->location),
                        expr->location
                );
                break;
            case NTree::OR:
                trueLabel = LabelHolder::GetNextLabel();
                falseLabel = LabelHolder::GetNextLabel();
                returnLabel = LabelHolder::GetNextLabel();
                expValue = new Temp("expValue", expr->location);
                condition = new CJump(CJump::EQ, left, new Const(1, expr->location), trueLabel, expr->location);
                trueBranch = new Seq(new CJump(CJump::NEQ, right, new Const(1, expr->location), falseLabel, expr->location),
                                     new Seq(
                                             new LabelStm(trueLabel, expr->location),
                                             new Seq(
                                                     new Move(expValue, new Const(1, expr->location), expr->location),
                                                     new Jump(returnLabel, expr->location),
                                                     expr->location
                                             ),
                                             expr->location
                                     ),
                                     expr->location
                );
                falseBranch = new Seq(
                        new LabelStm(falseLabel, expr->location),
                        new Seq(
                                new Move(new Temp(*expValue), new Const(0, expr->location), expr->location),
                                new Jump(returnLabel, expr->location),
                                expr->location
                        ),
                        expr->location
                );
                result = new ESeq(
                        new Seq(
                                new Seq(
                                        new Seq(
                                                condition,
                                                trueBranch,
                                                expr->location
                                        ),
                                        falseBranch,
                                        expr->location
                                ),
                                new LabelStm(returnLabel, expr->location),
                                expr->location
                        ),
                        new Mem(new Temp(*expValue), expr->location),
                        expr->location
                );
                break;
            default:
                assert(0);
        }
        mainSubtree.reset(new ExprWrapper(result));

    }

    IRBuilderVisitor::IRBuilderVisitor(const IClassStructBuilder *classStructBuilder, const IFrameBuilder *frameBuilder,
                                       const NSymbolTable::SymbolTable &symbolTable)
            : classStructBuilder(classStructBuilder), frameBuilder(frameBuilder), symbolTable(symbolTable) {

    }

    IRForest IRBuilderVisitor::CreateForest(const NTree::Program &program) {
        Visit(&program);
        return std::move(forest);
    }

    void IRBuilderVisitor::Visit(const NTree::VarDeclaration *) {
    }
}
