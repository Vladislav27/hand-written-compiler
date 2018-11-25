#include <abstr/Exceptions.h>
#include <table_of_symbols/SymbolTableBuilder.h>
#include <type_checker/DependencyChecker.h>
#include <type_checker/TypeCheckerVisitor.h>

#include <fstream>
#include <iostream>
#include "abstr/CDriver.h"

int main(int argc, char** argv) {
    Comp::CDriver driver;
    driver.parse(argv[1]);

    NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

    NTypeChecker::CheckDependencies(table);

    NTypeChecker::TypeCheckerVisitor checker(table);
    checker.Visit(&driver.program);

    return 0;
}