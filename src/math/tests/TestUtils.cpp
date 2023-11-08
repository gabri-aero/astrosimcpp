#include <gtest/gtest.h>
#include <math/Utils.hpp>

TEST(TestUtils, Factorial) {
    ASSERT_EQ(factorial(5), 120);
    ASSERT_EQ(factorial(10), 3628800);
}

TEST(TestUtils, BinomialNumbers) {
    ASSERT_EQ(C(15, 12), 455);
}

TEST(TestUtils, DegRad) {
    ASSERT_EQ(deg2rad(15), 15*M_PI/180);
    ASSERT_EQ(rad2deg(1), 180/M_PI);
}