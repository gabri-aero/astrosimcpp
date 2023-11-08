#include <gtest/gtest.h>
#include <math/Vector.hpp>

TEST(MathTest, Sum) {
    math::vector v1{-1., 1., 2.};
    math::vector v2{0., 1., -2.};

    math::vector result{-1., 2., 0.};

    ASSERT_EQ(v1+ v2, result);
}

TEST(MathTest, Difference) {
    math::vector v1{-1., 1., 2.};
    math::vector v2{0., 1., -2.};

    math::vector result{-1., 0., 4.};

    ASSERT_EQ(v1-v2, result);
}

TEST(MathTest, AddAssignment) {
    math::vector v1{-1., 1., 2.};
    math::vector v2{0., 1., -2.};

    v1 += v2;

    math::vector result{-1., 2., 0.};

    ASSERT_EQ(v1, result);
}

TEST(MathTest, ScalarProduct) {
    math::vector v{-1., 1., 2.};

    math::vector result{4., -4., -8.};

    ASSERT_EQ(-4*v, result);
    ASSERT_EQ(v*(-4), result);
}

TEST(MathTest, Division) {
    math::vector v{-1., 1., 2.};

    math::vector result{-0.5, 0.5, 1.};

    ASSERT_EQ(v/2, result);
}

TEST(MathTest, Norm) {
    math::vector v{3, 4, 5};
    ASSERT_EQ(norm(v), sqrt(9 + 16 + 25));
}

TEST(MathTest, Dot) {
    math::vector v1{3, 4, 5};
    math::vector v2{-1, 3, 4};
    ASSERT_EQ(dot(v1, v2), 29);
}

TEST(MathTest, Cross) {
    math::vector v1{3, 4, 5};
    math::vector v2{-1, 3, 4};

    math::vector result{1, -17, 13};

    ASSERT_EQ(cross(v1, v2), result);
}

TEST(MathTest, Ostream) {
    math::vector v1{3, 4, 5};
    std::cout << v1 << std::endl;
}

TEST(MathTest, PushBack) {
    math::vector v{3, 4};
    v.push_back(5);
    ASSERT_EQ(v.at(2), 5);
}

TEST(MathTest, Subvec) {
    math::vector v{3, 4, 5, 6, 7};
    math::vector subvector{4, 5, 6};
    ASSERT_EQ(v.subvec(1, 4), subvector);
}
