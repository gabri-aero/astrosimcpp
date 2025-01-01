#include <gtest/gtest.h>
#include <math/Interpolation.hpp>
#include <math/Matrix.hpp>

TEST(InterpolationTest, LinearTest) {
    math::vector x{0, 1, 3, 7, 10};
    math::vector y{2, 4, 5, -1, -3};
    LinearInterpolator interpolator{x, y};

    ASSERT_EQ(interpolator.interpolate(0.3), 2.6);
    ASSERT_EQ(interpolator.interpolate(8.5), -2.0);
    ASSERT_EQ(interpolator.interpolate(11), -3);
    ASSERT_EQ(interpolator.interpolate(-1), 2);
}

TEST(InterpolationTest, CubicSplineTest) {
    math::vector x{0,1,2,3};
    math::vector y{1,exp(1),exp(2),exp(3)};
    CubicSplineInterpolator interpolator{x,y};

    std::cout << interpolator.get_a() << std::endl;
    std::cout << interpolator.get_b() << std::endl;
    std::cout << interpolator.get_c() << std::endl;
    std::cout << interpolator.get_d() << std::endl;

    std::cout << interpolator.interpolate(2.5) << std::endl;
    std::cout << exp(2.5) << std::endl;
}


TEST(InterpolationTest, CubicSplineVectorInterpolationTest) {
    math::vector x{0,1,2,3};
    math::matrix y{
        {1,exp(1),exp(2),exp(3)},
        {0,1,4,9}
    };

    CubicSplineInterpolator interpolator{x,y.T()};

    std::cout << interpolator.get_a() << std::endl;
    std::cout << interpolator.get_b() << std::endl;
    std::cout << interpolator.get_c() << std::endl;
    std::cout << interpolator.get_d() << std::endl;

    std::cout << interpolator.interpolate(2.5) << std::endl;
    std::cout << exp(2.5) << ' ' << 2.5*2.5 << std::endl;
}

