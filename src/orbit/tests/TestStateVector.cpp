#include <gtest/gtest.h>
#include <orbit/StateVector.hpp>
#include <bodies/Body.hpp>
#include <orbit/Orbit.hpp>

TEST(StateVectorTest, to_orbit) {
    StateVector sv{6e6, 0, 8e6, 0, 7e3, 0};
    StateVector sv2{-6045e3, -3490e3, 2500e3, -3.457e3, 6.618e3, 2.533e3};
    Body earth(5.9733e24, {0, 0, 0, 0, 0, 0});
    auto oe1 = sv.to_orbit(earth).get_oe();
    auto oe2 = sv2.to_orbit(earth).get_oe();

    // Assert first case
    ASSERT_NEAR(12975.347e3, oe1.at(0), 1);  
    ASSERT_NEAR(0.229, oe1.at(1), 0.001);  
    ASSERT_NEAR(3*M_PI/2, oe1.at(2), 1e-10);  
    ASSERT_NEAR(0.9273, oe1.at(3), 1e-4);  
    ASSERT_NEAR(M_PI/2, oe1.at(4), 1e-10);  
    ASSERT_EQ(0, oe1.at(5));  

    // Assert second case (taken from Curtis)
    ASSERT_NEAR(pow(58311.7e6, 2)/3.986e14/(1-pow(0.171212,2)), oe2.at(0), 100);
    ASSERT_NEAR(0.171212, oe2.at(1), 1e-5);
    ASSERT_NEAR(255.279 * M_PI/180, oe2.at(2), 1e-4);
    ASSERT_NEAR(153.249 * M_PI/180, oe2.at(3), 1e-4);
    ASSERT_NEAR(20.0683 * M_PI/180, oe2.at(4), 1e-4);
    ASSERT_NEAR(28.4456 * M_PI/180, oe2.at(5), 1e-4);
}