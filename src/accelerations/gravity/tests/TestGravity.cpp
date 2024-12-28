#include <gtest/gtest.h>
#include <accelerations/gravity/Gravity.hpp>
#include <math/Vector.hpp>
#include <bodies/Body.hpp>

TEST(GravityTest, SinglePoint) {
    Body b1{1*G, {7.682, 0.845, 2.946, 4.512, 9.073, 1.234}};
    Body b2{3*G, {6.789, 3.421, 8.765, 5.678, 0.123, 9.231}};

    b2.get_mass();

    math::vector gi = b1.acceleration_from(b2);
    math::vector result = {-6.7369547315409664e-13, 1.9433813424915468e-12, 4.389959639735371e-12};

    ASSERT_EQ(gi, result);
}