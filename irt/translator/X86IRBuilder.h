#pragma once

#include <abstr/tree/Program.h>
#include <table_of_symbols/SymbolTable.h>
#include <irt/NodeTypes.h>

namespace NIRTree {
    IRForest BuildTree(const NTree::Program &program, const NSymbolTable::SymbolTable &symbolTable);
}