//
// Created by Jacob Pagan on 12/26/2024.
//


#include <gtest/gtest.h>


TEST(HelloTest, BasicAssertions) {
    EXPECT_STRNE("hello", "world");

    EXPECT_EQ(7 * 6, 42);
}