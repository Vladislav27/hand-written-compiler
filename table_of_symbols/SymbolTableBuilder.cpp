#include "SymbolTableBuilder.h"

#include "SymbolTableCreatorVisitor.h"

namespace NSymbolTable {
    SymbolTable BuildSymbolTable(const NSyntaxTree::Program &program) {
        SymbolTable table(program.interner);

        SymbolTableCreatorVisitor visitor(table);
        visitor.Visit(&program);

        return table;
    }
}