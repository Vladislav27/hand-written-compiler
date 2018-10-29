#include "GraphVizPrinterVisitor.h"

namespace NTree {

    void GraphVizPrinterVisitor::printVertex(const INode *node, const std::string &label) {
        outPut << "\tnode" << node << "[label=\"" << label << "\"]\n";
    }

    void GraphVizPrinterVisitor::printEdge(const INode *from, const INode *to) {
        outPut << "\tnode" << from << "->" << "node" << to << "\n";
    }

    void GraphVizPrinterVisitor::printEdge(const INode *from, const INode *to, const std::string &label) {
        outPut << "\tnode" << from << "->" << "node" << to << "[label=\"" << label << "\"]\n";
    }

    void GraphVizPrinterVisitor::printEdge(const std::string &from, const INode *to) {
        outPut << "\t" << from << "->" << "node" << to << "\n";
    }

    void GraphVizPrinterVisitor::printEdge(const INode *from, const std::string &to) {
        outPut << "\tnode" << from << "->" << to << "\n";
    }

    void GraphVizPrinterVisitor::Visit(const Program *node) {
        outPut << "digraph g {\n";  //  << "\n"

        this->printVertex(node, std::string("Program"));

        node->mainClass->Accept(this);

        printEdge(node, (node->mainClass).get());

        if (node->classes != nullptr) {
            for (const auto &cl : *(node->classes)) {
                cl->Accept(this);
                printEdge(node, cl.get());
            }
        }

        outPut << "}";
    }

    void GraphVizPrinterVisitor::Visit(const ClassDeclaration *node) {
        (node->id)->String();
        if ((node->extendsId) != nullptr) {
            printVertex(node, "Class " + (node->id)->String() + " extends " + (node->extendsId)->String());
        } else {
            printVertex(node, "Class " + (node->id)->String());
        }

        if (node->varDeclarations != nullptr) {
            for (const auto &var : *(node->varDeclarations)) {
                var->Accept(this);
                printEdge(node, var.get());
            }
        }

        if (node->methodDeclarations != nullptr) {
            for (const auto &method : *(node->methodDeclarations)) {
                method->Accept(this);
                printEdge(node, method.get());
            }
        }
    }

    void GraphVizPrinterVisitor::Visit(const MainClass *node) {
        printVertex(node, "Main " + (node->nameId)->String() + " mainArgsId " + (node->mainArgsId)->String());
        node->mainStatement->Accept(this);
        printEdge(node, (node->mainStatement).get());
    }

    void GraphVizPrinterVisitor::Visit(const VarDeclaration *node) {
        if ((node->type.id) != nullptr && (node->id) != nullptr) {
            printVertex(node, (node->type.id)->String() + " " + (node->id)->String());
        } else {
            if ((node->type.id) != nullptr) {
                printVertex(node, (node->type.id)->String());
            } else {
                printVertex(node, (node->id)->String());
            }
        }
    }

    void GraphVizPrinterVisitor::Visit(const MethodDeclaration *node) {
        std::string label;
        if ((node->id) != nullptr) {
            label = "method " + (node->id)->String();
        } else {
            label = "method";
        }
        switch ((node->returnType).type) {
            case CLASS:
                if ((node->returnType.id) != nullptr) {
                    label = label + " returnType: CLASS " + (node->returnType.id)->String();
                } else {
                    label = label + " returnType: CLASS";
                }
                break;
            case INT:
                label = label + " returnType: INT";
                break;
            case BOOL:
                label = label + " returnType: BOOL";
                break;
            case INT_ARRAY:
                label = label + " returnType: INT_ARRAY";
                break;
        }
        for (const auto& arg : *node->args) {
            switch (arg->type.type) {
                case CLASS:
                    if ((arg->type.id) != nullptr) {
                        label += " arg: CLASS " + (arg->type.id)->String() + " " + (arg->id)->String();
                    } else {
                        label += " arg: CLASS ";
                    }
                    break;
                case INT:
                    if ((arg->id) != nullptr) {
                        label += " arg: INT " + (arg->id)->String();
                    } else {
                        label += " arg: INT ";
                    }
                    break;
                case BOOL:
                    if ((arg->id) != nullptr) {
                        label += " arg: BOOL " + (arg->id)->String();
                    } else {
                        label += " arg: BOOL ";
                    }
                    break;
                case INT_ARRAY:
                    if ((arg->id) != nullptr) {
                        label += " arg INT_ARRAY " + (arg->id)->String();
                    } else {
                        label += " arg INT_ARRAY ";
                    }
                    break;
            }
        }
        printVertex(node, label);
        if (node->localVars != nullptr) {
            for (const auto &var : *(node->localVars)) {
                var->Accept(this);
                printEdge(node, var.get(), "local var");
            }
        }
        if (node->statements != nullptr) {
            for (const auto &statement : *(node->statements)) {
                statement->Accept(this);
                printEdge(node, statement.get());
            }
        }

        node->returnExpression->Accept(this);
        printEdge(node, (node->returnExpression).get(), "return");
    }

    void GraphVizPrinterVisitor::Visit(const Statements *node) {
        printVertex(node, "statements");
        if (node->statements != nullptr) {
            for (const auto &statement : *(node->statements)) {
                statement->Accept(this);
                printEdge(node, statement.get());
            }
        }
    }

    void GraphVizPrinterVisitor::Visit(const IfStatement *node) {
        printVertex(node, "If");
        node->condition->Accept(this);
        printEdge(node, (node->condition).get(), "condition");
        node->trueStatement->Accept(this);
        printEdge(node, (node->trueStatement).get(), "True");
        node->falseStatement->Accept(this);
        printEdge(node, (node->falseStatement).get(), "False");
    }

    void GraphVizPrinterVisitor::Visit(const WhileStatement *node) {
        printVertex(node, "while");
        node->condition->Accept(this);
        printEdge(node, (node->condition).get(), "condition");
        node->trueStatement->Accept(this);
        printEdge(node, (node->trueStatement).get(), "true statement");
    }

    void GraphVizPrinterVisitor::Visit(const PrintlnStatement *node) {
        printVertex(node, "println");
        node->toPrint->Accept(this);
        printEdge(node, (node->toPrint).get());
    }

    void GraphVizPrinterVisitor::Visit(const AssignStatement *node) {
        if ((node->lvalue) != nullptr) {
            printVertex(node, (node->lvalue)->String() + " :=");
        } else {
            printVertex(node, "=");
        }
        node->rvalue->Accept(this);
        printEdge(node, (node->rvalue).get(), "rvalue");
    }

    void GraphVizPrinterVisitor::Visit(const ArrayElementAssignmentStatement *node) {
        if ((node->arrayId) != nullptr) {
            printVertex(node, "array " + (node->arrayId)->String() + "elem assign");
        } else {
            printVertex(node, "array elem assign");
        }
        node->index->Accept(this);
        printEdge(node, (node->index).get(), "index");
        node->rvalue->Accept(this);
        printEdge(node, (node->rvalue).get());
    }

    void GraphVizPrinterVisitor::Visit(const BinaryExpression *node) {
        printVertex(node, "binary exp " + binaryTypeToString(node->type));
        node->left->Accept(this);
        node->right->Accept(this);
        printEdge(node, (node->left).get(), "left");
        printEdge(node, (node->right).get(), "right");
    }

    void GraphVizPrinterVisitor::Visit(const ArrayElementAccessExpression *node) {
        printVertex(node, "AccessToElement");
        node->array->Accept(this);
        printEdge(node, (node->array).get(), "array");
        node->index->Accept(this);
        printEdge(node, (node->index).get(), "index");
    }

    void GraphVizPrinterVisitor::Visit(const ArrayLengthExpression *node) {
        printVertex(node, "lengthExpression");
        node->array->Accept(this);
        printEdge(node, (node->array).get(), "array");
    }

    void GraphVizPrinterVisitor::Visit(const MethodCallExpression *node) {
        printVertex(node, "methodCall");
        node->object->Accept(this);
        if ((node->nameId) != nullptr) {
            printEdge(node, (node->object).get(), "method " + (node->nameId)->String());
        } else {
            printEdge(node, (node->object).get(), "method ");
        }

        if (node->args != nullptr) {
            for (const auto &arg : *(node->args)) {
                arg->Accept(this);
                printEdge(node, arg.get(), "arg");
            }
        }
    }

    void GraphVizPrinterVisitor::Visit(const IntegerLiteralExpression *node) {
        printVertex(node, "int " + std::to_string(node->value));
    }

    void GraphVizPrinterVisitor::Visit(const BoolLiteralExpression *node) {
        printVertex(node, "bool " + std::to_string(node->value));
    }

    void GraphVizPrinterVisitor::Visit(const IdentifierExpression *node) {
        if ((node->identifier) != nullptr) {
            printVertex(node, "identifier " + (node->identifier)->String());
        } else {
            printVertex(node, "identifier");
        }
    }

    void GraphVizPrinterVisitor::Visit(const ThisExpression *node) {
        printVertex(node, "this");
    }

    void GraphVizPrinterVisitor::Visit(const NewIntArrayExpression *node) {
        printVertex(node, "new int[]");
        node->size->Accept(this);
        printEdge(node, (node->size).get(), "size");
    }

    void GraphVizPrinterVisitor::Visit(const NewExpression *node) {
        if ((node->classId) != nullptr) {
            printVertex(node, "new " + (node->classId)->String());
        } else {
            printVertex(node, "new");
        }
    }

    void GraphVizPrinterVisitor::Visit(const NegateExpression *node) {
        printVertex(node, "negate");
        node->expression->Accept(this);
        printEdge(node, (node->expression).get());
    }
}