#include <gtest/gtest.h>
#include <time/Epoch.hpp>
#include <frames/FrameUtils.hpp>
#include <math/Utils.hpp>
#include <cmath>

TEST(FrameUtilsTest, ERA) {
    double dut1 =  -0.439961;
    Epoch epoch(2004, 4, 6, 7, 51, 28.386009 + dut1, UTC, JD, DAY_COUNT); // TO DO: include UT1
    std::cout << epoch.with_timescale(TAI) << std::endl;
    std::cout << era(epoch) * 180 / M_PI << std::endl;
    ASSERT_NEAR(era(epoch) * 180/M_PI, 312.7552829, 1e-6);  // from Vallado example 3.14
}

TEST(FrameUtilsTest, Spherical) {
    double radius = 6371e3;
    double lon = deg2rad(-170);
    double lat = deg2rad(-45);
    auto cart = sph2cart(radius, lon, lat);
    auto sph = cart2sph(cart);
    
    EXPECT_DOUBLE_EQ(sph[0], radius);
    EXPECT_DOUBLE_EQ(sph[1], lon);
    EXPECT_DOUBLE_EQ(sph[2], lat);
}

