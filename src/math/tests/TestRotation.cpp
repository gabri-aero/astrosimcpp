#include <gtest/gtest.h>
#include <math/Rotation.hpp>
#include <math/Vector.hpp>


void assert_near_vector(math::vector v1, math::vector v2, double tol) {
    ASSERT_NEAR(norm(v1-v2), 0, tol);
}

TEST(RotationTest, RotationMatrix2) {
    math::vector v{1, 0, 0};
    math::vector v2{0, 1, 0};

    math::vector v_rotz{cos(M_PI/6), -sin(M_PI/6), 0};
    math::vector v_roty{cos(M_PI/6), 0, sin(M_PI/6)};
    math::vector v2_rotx{0, cos(M_PI/6), -sin(M_PI/6)};

    ASSERT_EQ(R3(M_PI/6)*v, v_rotz);
    ASSERT_EQ(R2(M_PI/6)*v, v_roty);
    ASSERT_EQ(R1(M_PI/6)*v2, v2_rotx);
}