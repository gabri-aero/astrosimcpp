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

TEST(FrameUtilsTest, GMST) {
    Epoch epoch{1992, 8, 20, 12, 14, 0, UTC}; 
    ASSERT_NEAR(gmst(epoch), 152.578787810, 1e-9); // from Vallado example 3.5
    std::cout << gmst<HMS>(epoch) << std::endl;
}

TEST(FrameUtilsTest, LST) {
    Epoch epoch{1992, 8, 20, 12, 14, 0, UTC}; 
    ASSERT_NEAR(lst(epoch, -104), 48.578787810, 1e-9); // from Vallado example 3.5
    std::cout << lst<HMS>(epoch, -104) << std::endl;
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

TEST(EOPTest, FundamentalArguments) {
    Epoch epoch{2004, 4, 6, 7, 51, 28.386009, UTC};
    Epoch j2000_TT{2000, 1, 1, 12, 0, 0, TT, JD}; 
    double t = (epoch.set_reference_epoch(JD).set_timescale(TT).get_days() - j2000_TT.get_days()) / 36525;
    
    // Luni-solar arguments
    ASSERT_NEAR(rad2deg(l(t)), 314.9122873, 1e-7);
    ASSERT_NEAR(rad2deg(lp(t)), 91.9393769, 1e-7);
    ASSERT_NEAR(rad2deg(F(t)), 169.0970043, 1e-7);
    ASSERT_NEAR(rad2deg(D(t)), 196.7516428, 1e-7);
    ASSERT_NEAR(rad2deg(Om(t)), 42.6046467, 1e-7);

    // Planetary nutation values
    ASSERT_NEAR(rad2deg(L_Me(t)), 143.319167, 1e-6);
    ASSERT_NEAR(rad2deg(L_Ve(t)), 156.221635, 1e-6);
    ASSERT_NEAR(rad2deg(L_E(t)), 194.890465, 1e-6);
    ASSERT_NEAR(rad2deg(L_Ma(t)), 91.262347, 1e-6);
    ASSERT_NEAR(rad2deg(L_J(t)), 163.710186, 1e-6);
    ASSERT_NEAR(rad2deg(L_Sa(t)), 102.168400, 1e-5);
    ASSERT_NEAR(rad2deg(L_U(t)), 332.317825, 1e-6);
    ASSERT_NEAR(rad2deg(L_Ne(t)), 313.661341, 1e-6);
    ASSERT_NEAR(rad2deg(p_A(t)), 0.059545, 1e-6);
}


