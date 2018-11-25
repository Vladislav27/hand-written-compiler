#pragma once

#include <table_of_symbols/SymbolTable.h>
#include <table_of_symbols/ClassInfo.h>
#include <table_of_symbols/Exceptions.h>

namespace NTypeChecker {
    void CheckDependencies(const NSymbolTable::SymbolTable& symbolTable);

    void CheckInClass(const NSymbolTable::SymbolTable& symbolTable,
        const NTree::Symbol* superClassId,
        const NSymbolTable::ClassInfo& childClassInfo);
}