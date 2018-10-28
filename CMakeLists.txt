cmake_minimum_required(VERSION 3.8)
project(hand_written_compiler)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register")
if (APPLE)
    set(BISON_EXECUTABLE "/usr/local/opt/bison/bin/bison")
endif (APPLE)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(parser
        lexer/parser.yy
        ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)
FLEX_TARGET(lexer
        lexer/lexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)


set(SOURCE_FILES lexer/CDriver.cpp lexer/LineHandler.cpp lexer/LineHandler.h)

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
        lexer)

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