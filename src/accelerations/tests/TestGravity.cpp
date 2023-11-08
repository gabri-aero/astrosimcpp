#include <gtest/gtest.h>
#include <accelerations/Gravity.hpp>
#include <math/Vector.hpp>
#include <bodies/Body.hpp>

TEST(GravityTest, SinglePoint) {
    Body b1{1, {7.682, 0.845, 2.946, 4.512, 9.073, 1.234}};
    Body b2{3, {6.789, 3.421, 8.765, 5.678, 0.123, 9.231}};

    math::vector gi = gravity(b1, b2);
    math::vector result = {-6.7369550815993487e-13, 1.943381443471434e-12, 4.3899598678417227e-12};

    ASSERT_EQ(gi, result);
}