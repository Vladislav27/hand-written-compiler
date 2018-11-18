#include <abstr/Exceptions.h>
#include <table_of_symbols/SymbolTableBuilder.h>
#include <type_checker/DependencyChecker.h>
#include <type_checker/TypeCheckerVisitor.h>

#include <fstream>
#include <iostream>
#include "abstr/CDriver.h"

int main(int argc, char** argv) {
    try {
        Comp::CDriver driver;
        driver.parse(argv[1]);

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch (NSyntaxTree::SyntaxError &error) {
        std::cerr << error.what() << std::endl;
        return 0;
    }

    std::cout << "OK" << std::endl;

    return 0;
}