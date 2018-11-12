#pragma once

#include <gtest/gtest.h>
#include <fstream>
#include "lexer/CDriver.h"

TEST(UnitTest, test_1) {
    bool flag = false;
    Comp::CDriver driver;
    try {
        driver.parse("../lexer/good_test");
    } catch (std::exception& e) {
        flag = true;
    }
    EXPECT_FALSE(flag);
}

TEST(UnitTest, test_2) {
    bool flag = false;
    Comp::CDriver driver;
    try {
        driver.parse("../lexer/bad_test");
    } catch (std::exception& e) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}