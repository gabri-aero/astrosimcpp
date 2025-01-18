#include <gtest/gtest.h>
#include <states/Keplerian.hpp>
#include <states/Cartesian.hpp> // very important to avoid error: invalid uso of incomplete type 'class Cartesian'
#include <math/Utils.hpp>

void assert_near_sv(math::vector v1, math::vector v2) {
    ASSERT_NEAR(norm(v1.subvec(0,3)-v2.subvec(0,3)), 0, 100);
    ASSERT_NEAR(norm(v1.subvec(3,6)-v2.subvec(3,6)), 0, 1);
}

TEST(TestKeplerian, GeneralTest) {
    Body earth(3.986004418e14, {0, 0, 0, 0, 0, 0});

    // First case
    Keplerian oe1{
        8.788e6,
        0.171212,
        deg2rad(255.279),
        deg2rad(153.249),
        deg2rad(20.0683),
        deg2rad(28.4456)
    };
    math::vector sv1_expected{
        -6045e3, -3490e3, 2500e3, 
        -3.457e3, 6.618e3, 2.533e3
    };
    assert_near_sv(sv1_expected, oe1.to_cartesian(earth));

    // Second case
    Keplerian oe2{
        -16725e3,
        1.4,
        deg2rad(40),
        deg2rad(30),
        deg2rad(60),
        deg2rad(30)
    };
    math::vector sv2_expected{
        -4039.9e3, 4814.56e3, 3628.62e3,
        -10.386e3, -4.77192e3, 1.74388e3
    };

    assert_near_sv(sv2_expected, oe2.to_cartesian(earth));

}