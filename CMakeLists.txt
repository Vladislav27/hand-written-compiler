cmake_minimum_required(VERSION 3.8)
project(hand_written_compiler)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
if (APPLE)
    set(BISON_EXECUTABLE "/usr/local/opt/bison/bin/bison")
endif (APPLE)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(parser
        abstr/parser.yy
        ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)
FLEX_TARGET(lexer
        abstr/lexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)


set(SOURCE_FILES
        abstr/CDriver.cpp
        abstr/Symbol.cpp
        abstr/StringInterner.cpp
        abstr/Location.cpp
        abstr/tree/Class.cpp
        abstr/tree/Expression.cpp
        abstr/tree/Program.cpp
        abstr/tree/Statement.cpp
        abstr/tree/VarDeclaration.cpp
        abstr/tree/MethodDeclaration.cpp
        abstr/tree/visitors/GraphVizPrinterVisitor.cpp
        table_of_symbols/TypeInfo.cpp
        table_of_symbols/VariableInfo.cpp
        table_of_symbols/MethodInfo.cpp
        table_of_symbols/ClassInfo.cpp
        table_of_symbols/SymbolTable.cpp
        table_of_symbols/SymbolTableCreatorVisitor.cpp
        table_of_symbols/ScopeSwitcher.cpp
        table_of_symbols/SymbolTableBuilder.cpp
        table_of_symbols/SymbolTableBuilder.h
        type_checker/DependencyChecker.cpp
        type_checker/TypeCheckerVisitor.cpp
        type_checker/Exceptions.cpp
        irt/activation_records/X86/X86MiniJavaClassStruct.cpp
        irt/activation_records/X86/X86MiniJavaFrame.cpp
        irt/activation_records/ArrayStruct.cpp
        irt/activation_records/InFrameAccess.cpp
        irt/activation_records/InRegAccess.cpp
        irt/Accept.cpp
        irt/DotPrinter.cpp
        irt/Label.cpp
        irt/expressions/Temp.cpp
        irt/translator/IRBuilderVisitor.cpp
        irt/translator/IRPrettyPrinter.cpp
        irt/translator/X86IRBuilder.cpp
        )

add_executable(hand_written_compiler
        main.cpp
        ${SOURCE_FILES}
        ${FLEX_lexer_OUTPUTS}
        ${BISON_parser_OUTPUTS}
        )

target_include_directories(hand_written_compiler
        PRIVATE
        .
        ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(hand_written_compiler
        PRIVATE
        .
        abstr)

set_property(TARGET hand_written_compiler
        PROPERTY CXX_STANDARD 14)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
    set(GLOBAL_CMAKE_CCACHE_RULES -DCMAKE_C_COMPILER=/usr/lib/ccache/cc -DCMAKE_CXX_COMPILER=/usr/lib/ccache/c++)
    set(GLOBAL_CCACHE_ENV -DCMAKE_C_COMPILER=/usr/lib/ccache/cc -DCMAKE_CXX_COMPILER=/usr/lib/ccache/c++)
endif(CCACHE_PROGRAM)

include(CTest)
set(SOURCE_FILES_TEST ${SOURCE_FILES} UnitTest.cpp)

add_subdirectory(googletest-master/googletest)
include_directories(googletest-master/googletest/include/ . ${CMAKE_CURRENT_BINARY_DIR} . lexer)

add_executable(exe UnitTest.cpp ${SOURCE_FILES} ${FLEX_lexer_OUTPUTS} ${BISON_parser_OUTPUTS})
target_link_libraries(exe ${GTEST_LIBRARIES} gtest gtest_main)
target_link_libraries(exe ${GTEST_BOTH_LIBRARIES})