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

TEST(TestUtils, WrapTo2Pi) {
    ASSERT_EQ(wrapTo2Pi(10), 10 - (2*M_PI));
    ASSERT_EQ(wrapTo2Pi(-1), -1 + (2*M_PI));
    ASSERT_EQ(wrapTo2Pi(5), 5);
}

TEST(TestUtils, CartToSph) {
    math::vector sph{3, -M_PI/2, -2*M_PI/6};
    math::vector cart{0, -3/2., -3*sqrt(3)/2};
    ASSERT_NEAR(sph.at(0), cart_to_sph(cart).at(0), 1e-3);
    ASSERT_NEAR(sph.at(1), cart_to_sph(cart).at(1), 1e-3);
    ASSERT_NEAR(sph.at(2), cart_to_sph(cart).at(2), 1e-3);
    ASSERT_NEAR(cart.at(0), sph_to_cart(sph).at(0), 1e-3);
    ASSERT_NEAR(cart.at(1), sph_to_cart(sph).at(1), 1e-3);
    ASSERT_NEAR(cart.at(2), sph_to_cart(sph).at(2), 1e-3);
}