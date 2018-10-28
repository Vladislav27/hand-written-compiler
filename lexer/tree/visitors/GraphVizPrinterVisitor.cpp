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
        outPut << "digraph g {\n" << "\n";

        this->printVertex(node, std::string("Program"));

        node->mainClass->Accept(this);

        printEdge(node, (node->mainClass).get());

        outPut << "}";
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

    void GraphVizPrinterVisitor::Visit(const Statements *node) {
        printVertex(node, "statements");
        if (node->statements != nullptr) {
            for (const auto &statement : *(node->statements)) {
                statement->Accept(this);
                printEdge(node, statement.get());
            }
        }
    }

    void GraphVizPrinterVisitor::Visit(const AssignStatement *node) {
        if ((node->lvalue) != nullptr) {
            printVertex(node, (node->lvalue)->String() + "=");
        } else {
            printVertex(node, "=");
        }
        node->rvalue->Accept(this);
        printEdge(node, (node->rvalue).get(), "rvalue");
    }

    void GraphVizPrinterVisitor::Visit(const BinaryExpression *node) {
        printVertex(node, "binary exp " + node->type);
        node->left->Accept(this);
        node->right->Accept(this);
        printEdge(node, (node->left).get(), "left");
        printEdge(node, (node->right).get(), "right");
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

    void GraphVizPrinterVisitor::Visit(const NegateExpression *node) {
        printVertex(node, "negate");
        node->expression->Accept(this);
        printEdge(node, (node->expression).get());
    }
}