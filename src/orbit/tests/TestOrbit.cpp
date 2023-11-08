#include <gtest/gtest.h>
#include <orbit/Orbit.hpp>
#include <orbit/StateVector.hpp> // very important to avoid error: invalid uso of incomplete type 'class StateVector'
#include <math/Utils.hpp>

void assert_near_sv(math::vector v1, math::vector v2) {
    ASSERT_NEAR(norm(v1.subvec(0,3)-v2.subvec(0,3)), 0, 100);
    ASSERT_NEAR(norm(v1.subvec(3,6)-v2.subvec(3,6)), 0, 1);
}

TEST(TestOrbit, GeneralTest) {
    Body earth(5.9733e24, {0, 0, 0, 0, 0, 0});

    // First case
    Orbit oe1{
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

    assert_near_sv(sv1_expected, oe1.to_sv(earth).get_rv());

    // Second case
    Orbit oe2{
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

    assert_near_sv(sv2_expected, oe2.to_sv(earth).get_rv());

}

TEST(TestOrbit, Type) {
    Orbit orbit{1e6, 0, 0, 0, 0, 0};
    Orbit orbit2{-1e6, 0, 0, 0, 0, 0};
    ASSERT_EQ(orbit.get_type(), OrbitType::ELLIPTICAL);
    ASSERT_EQ(orbit2.get_type(), OrbitType::HYPERBOLIC);
}