cmake_minimum_required(VERSION 3.8)
project(hand_written_compiler)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register")

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(parser
        lexer/parser.yy
        ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)
FLEX_TARGET(lexer
        lexer/lexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)


set(SOURCE_FILES main.cpp lexer/CDriver.cpp lexer/LineHandler.cpp lexer/LineHandler.h)

add_executable(hand_written_compiler
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
        lexer)

set_property(TARGET hand_written_compiler
        PROPERTY CXX_STANDARD 14)
