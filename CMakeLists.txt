cmake_minimum_required(VERSION 3.8)
project(hand_written_compiler)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register")

#find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

#BISON_TARGET(mc_parser
#        mc_parser.yy
#        ${CMAKE_CURRENT_BINARY_DIR}/mc_parser.tab.cc)
FLEX_TARGET(lexer
        lexer/lexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)
#ADD_FLEX_BISON_DEPENDENCY(mc_lexer mc_parser)


set(SOURCE_FILES main.cpp)

#add_executable(hand_written_compiler
#        SOURCE_FILES
#        ${FLEX_lexer_OUTPUTS}
#        ${BISON_mc_parser_OUTPUTS}
#        )
add_executable(hand_written_compiler
        ${SOURCE_FILES}
        ${FLEX_lexer_OUTPUTS}
        )

set_property(TARGET hand_written_compiler
        PROPERTY CXX_STANDARD 14)
