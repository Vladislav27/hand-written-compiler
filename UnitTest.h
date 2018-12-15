#pragma once

#include <abstr/Exceptions.h>
#include <table_of_symbols/SymbolTableBuilder.h>
#include <type_checker/DependencyChecker.h>
#include <type_checker/TypeCheckerVisitor.h>

#include <fstream>
#include <iostream>
#include <irt/translator/IRPrettyPrinter.h>
#include <irt/translator/X86IRBuilder.h>
#include <gtest/gtest.h>
#include "abstr/CDriver.h"

TEST(TestParse, test_1) {
    bool flag = false;
    Comp::CDriver driver;
    try {
        driver.parse("../abstr/good_test");
    } catch (std::exception& e) {
        flag = true;
    }
    EXPECT_FALSE(flag);
}

TEST(TestParse, test_2) {
    bool flag = false;
    Comp::CDriver driver;
    try {
        driver.parse("../abstr/bad_test");
    } catch (std::exception& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestAST, test_1) {
    Comp::CDriver driver;
    driver.parse("../Samples/BinarySearch.java");
    // ast

    std::ofstream outPut("./graph_ast.gv");

    NTree::GraphVizPrinterVisitor printer(outPut);
    printer.Visit(&driver.program);

    outPut.close();
}

TEST(TestAST, test_2) {
    Comp::CDriver driver;
    driver.parse("../Samples/BubbleSort.java");
    // ast

    std::ofstream outPut("./graph_ast.gv");

    NTree::GraphVizPrinterVisitor printer(outPut);
    printer.Visit(&driver.program);

    outPut.close();
}

TEST(TestAST, test_3) {
    Comp::CDriver driver;
    driver.parse("../Samples/Factorial.java");
    // ast

    std::ofstream outPut("./graph_ast.gv");

    NTree::GraphVizPrinterVisitor printer(outPut);
    printer.Visit(&driver.program);

    outPut.close();
}

TEST(TestAST, test_4) {
    Comp::CDriver driver;
    driver.parse("../Samples/LinearSearch.java");
    // ast

    std::ofstream outPut("./graph_ast.gv");

    NTree::GraphVizPrinterVisitor printer(outPut);
    printer.Visit(&driver.program);

    outPut.close();
}

TEST(TestAST, test_5) {
    Comp::CDriver driver;
    driver.parse("../Samples/QuickSort.java");
    // ast

    std::ofstream outPut("./graph_ast.gv");

    NTree::GraphVizPrinterVisitor printer(outPut);
    printer.Visit(&driver.program);

    outPut.close();
}

TEST(TestIRT, test_1) {
    Comp::CDriver driver;
    driver.parse("../Samples/BinarySearch.java");
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
}

TEST(TestIRT, test_2) {
    Comp::CDriver driver;
    driver.parse("../Samples/BubbleSort.java");
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
}

TEST(TestIRT, test_3) {
    Comp::CDriver driver;
    driver.parse("../Samples/Factorial.java");
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
}

TEST(TestIRT, test_4) {
    Comp::CDriver driver;
    driver.parse("../Samples/LinearSearch.java");
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
}

TEST(TestIRT, test_5) {
    Comp::CDriver driver;
    driver.parse("../Samples/QuickSort.java");
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
}

TEST(TestTypeChecker, test_1) {
    Comp::CDriver driver;
    driver.parse("../Samples/Factorial.java");

    NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

    NTypeChecker::CheckDependencies(table);

    NTypeChecker::TypeCheckerVisitor checker(table);
    checker.Visit(&driver.program);
}

TEST(TestTypeChecker, test_2) {
    Comp::CDriver driver;
    driver.parse("../Samples/QuickSort.java");

    NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

    NTypeChecker::CheckDependencies(table);

    NTypeChecker::TypeCheckerVisitor checker(table);
    checker.Visit(&driver.program);
}

TEST(TestTypeChecker, test_3) {
    Comp::CDriver driver;
    driver.parse("../Samples/LinearSearch.java");

    NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

    NTypeChecker::CheckDependencies(table);

    NTypeChecker::TypeCheckerVisitor checker(table);
    checker.Visit(&driver.program);
}

TEST(TestTypeChecker, test_4) {
    Comp::CDriver driver;
    driver.parse("../Samples/BubbleSort.java");

    NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

    NTypeChecker::CheckDependencies(table);

    NTypeChecker::TypeCheckerVisitor checker(table);
    checker.Visit(&driver.program);
}

TEST(TestTypeChecker, test_5) {
    Comp::CDriver driver;
    driver.parse("../Samples/BinarySearch.java");

    NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

    NTypeChecker::CheckDependencies(table);

    NTypeChecker::TypeCheckerVisitor checker(table);
    checker.Visit(&driver.program);
}

TEST(TestTypeChecker, test_6) {
    Comp::CDriver driver;
    driver.parse("../Samples/TreeVisitor.java");

    NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

    NTypeChecker::CheckDependencies(table);

    NTypeChecker::TypeCheckerVisitor checker(table);
    checker.Visit(&driver.program);
}

TEST(TestTypeChecker, test_7) {
    Comp::CDriver driver;
    driver.parse("../Samples/LinkedList.java");

    NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

    NTypeChecker::CheckDependencies(table);

    NTypeChecker::TypeCheckerVisitor checker(table);
    checker.Visit(&driver.program);
}

TEST(TestTypeChecker, test_8) {
    Comp::CDriver driver;
    driver.parse("../Samples/BinaryTree.java");

    NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

    NTypeChecker::CheckDependencies(table);

    NTypeChecker::TypeCheckerVisitor checker(table);
    checker.Visit(&driver.program);
}