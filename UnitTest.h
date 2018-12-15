#pragma once

#include <abstr/Exceptions.h>
#include <table_of_symbols/SymbolTableBuilder.h>
#include <type_checker/DependencyChecker.h>
#include <type_checker/TypeCheckerVisitor.h>
#include <type_checker/Exceptions.h>

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

TEST(TestTypeCheckerGoodSamples, test_1) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../Samples/Factorial.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_FALSE(flag);
}

TEST(TestTypeCheckerGoodSamples, test_2) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../Samples/QuickSort.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_FALSE(flag);
}

TEST(TestTypeCheckerGoodSamples, test_3) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../Samples/LinearSearch.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_FALSE(flag);
}

TEST(TestTypeCheckerGoodSamples, test_4) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../Samples/BubbleSort.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
        EXPECT_FALSE(flag);
}

TEST(TestTypeCheckerGoodSamples, test_5) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../Samples/BinarySearch.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
            EXPECT_FALSE(flag);
}

TEST(TestTypeCheckerGoodSamples, test_6) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../Samples/TreeVisitor.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_FALSE(flag);
}

TEST(TestTypeCheckerGoodSamples, test_7) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../Samples/LinkedList.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_FALSE(flag);
}

TEST(TestTypeCheckerGoodSamples, test_8) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../Samples/BinaryTree.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_FALSE(flag);
}

TEST(TestTypeCheckerBadSamples, test_1) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_1a.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_2) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_2a.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(std::exception& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_3) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_3a.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_4) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_3b.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_5) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_4a.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_6) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_4b.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_7) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_5a.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_8) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_6a.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_9) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_7b.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_10) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_7c.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_11) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_8a.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_12) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_9a.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_13) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_9a_2.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_14) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_11a.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_15) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_12b.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_16) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_13a.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_17) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_13b.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_18) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_13c.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(NTree::SyntaxError& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_19) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_13d(optional).java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(std::exception& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TestTypeCheckerBadSamples, test_20) {
    bool flag = false;
    try {
        Comp::CDriver driver;
        driver.parse("../BadSamples/TC_bonus1.java");

        NSymbolTable::SymbolTable table = NSymbolTable::BuildSymbolTable(driver.program);

        NTypeChecker::CheckDependencies(table);

        NTypeChecker::TypeCheckerVisitor checker(table);
        checker.Visit(&driver.program);
    } catch(std::exception& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}
