#include <abstr/Exceptions.h>
#include <table_of_symbols/SymbolTableBuilder.h>
#include <type_checker/DependencyChecker.h>
#include <type_checker/TypeCheckerVisitor.h>

#include <fstream>
#include <iostream>
#include <irt/translator/Canoniser.h>
#include <irt/translator/IRPrettyPrinter.h>
#include <irt/translator/X86IRBuilder.h>
#include "abstr/CDriver.h"

int main(int argc, char** argv) {

    Comp::CDriver driver;
    driver.parse(argv[1]);
    
    // ast
    std::ofstream outPut("./graph_ast.gv");

    NTree::GraphVizPrinterVisitor printer(outPut);
    printer.Visit(&driver.program);

    outPut.close();

    // irt
    std::ofstream outIrt("./graph_irt.gv");

    NSymbolTable::SymbolTable symbolTable = NSymbolTable::BuildSymbolTable(driver.program);

    NIRTree::IRPrettyPrinter irPrinter(outIrt);
    NIRTree::IRForest forest = NIRTree::BuildTree(driver.program, symbolTable);

    irPrinter.Visit(forest);

    outIrt.close();

    // linearized irt
    std::ofstream outLinearIrt("./graph_irt_canon.gv");
    NIRTree::IRLinearForest linearForest;
    NIRTree::IRPrettyPrinter linearIRPrinter(outLinearIrt);

    for (auto &tree: forest) {
        linearForest.insert({tree.first, NIRTree::Canoniser::Canonise(tree.second.release())});
    }

    linearIRPrinter.Visit(linearForest);
    outLinearIrt.close();
    return 0;
}