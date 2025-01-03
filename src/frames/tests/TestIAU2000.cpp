#include <gtest/gtest.h>
#include <frames/IAU2000.hpp>
#include <bodies/EphemerisBody.hpp>
#include <frames/BodyFixed.hpp>
#include <frames/InertialFrame.hpp>

TEST(IAUTest, XYs) {
    Epoch epoch{2003, 8, 26, 0, 37, 38.973810, UTC};    
    auto XYs = ITRF.get_XYs(epoch);
    double X, Y, s;
    X = XYs.at(0);
    Y = XYs.at(1);
    s = XYs.at(2);
    ASSERT_NEAR(X, 3.29956644592e-4, 1e-7);
    ASSERT_NEAR(Y, 2.7325684592e-5, 1e-7);
    ASSERT_NEAR(s, as2rad(-2.900355*1e-3), 1e-11);
}

TEST(IAUTest, PN) {
    Epoch epoch{2003, 8, 26, 0, 37, 38.973810, UTC};    
    std::cout << ITRF.PN(epoch) << std::endl;
}

TEST(IAUTest, W) {
    Epoch epoch{2003, 8, 26, 0, 37, 38.973810, UTC};    
    std::cout << ITRF.W(epoch) << std::endl;
}

TEST(IAUTest, B) {
    Epoch epoch{2003, 8, 26, 0, 37, 38.973810, UTC};    
    std::cout << B() << std::endl;
}

TEST(IAUTest, Conversion) {
    // Example 3-14 from Vallado
    Epoch epoch{2004, 4, 6, 7, 51, 28.386009, UTC};

    // Set eop_data interpolator to floor (not interpolate)
    FloorInterpolator<double, EOP> floor_interpolator;
    eop_data.set_interpolator(floor_interpolator);
    eop_data.update_interpolator_data();

    math::vector r_itrs{-1033479.3830, 7901295.2754, 6380356.5958};
    math::vector r_pef{-1033475.0313, 7901305.5856, 6380344.5328};
    math::vector r_tirs{-1033475.0312, 7901305.5856, 6380344.5327};
    math::vector r_cirs{5100018.4047, 6122786.3648, 6380344.5327};
    math::vector r_gcrs{5102508.959, 6123011.403, 6378136.925};

    ASSERT_NEAR(norm(ITRF.to(PEF, epoch)*r_itrs - r_pef), 0, 0.01);
    ASSERT_NEAR(norm(PEF.to(TIRF, epoch)*r_pef - r_tirs), 0, 2e-4);
    ASSERT_NEAR(norm(TIRF.to(CIRF, epoch)*r_tirs - r_cirs), 0, 1e-4);
    ASSERT_NEAR(norm(CIRF.to(GCRF, epoch)*r_cirs - r_gcrs), 0, 0.10);
    
    ASSERT_NEAR(norm(PEF.from(ITRF, epoch)*r_itrs - r_pef), 0, 0.01);
    ASSERT_NEAR(norm(TIRF.from(PEF, epoch)*r_pef - r_tirs), 0, 2e-4);
    ASSERT_NEAR(norm(CIRF.from(TIRF, epoch)*r_tirs - r_cirs), 0, 1e-4);
    ASSERT_NEAR(norm(GCRF.from(CIRF, epoch)*r_cirs - r_gcrs), 0, 0.10);

    // All conversions achieve sub-cm accuracy
}