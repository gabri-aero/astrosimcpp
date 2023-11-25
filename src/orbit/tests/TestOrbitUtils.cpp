#include<gtest/gtest.h>
#include<orbit/OrbitUtils.hpp>
#include<math.h>

TEST(TestOrbitUtils, KeplerSolver) {
    double e = 0.4;
    double M = 235.4 * M_PI/180;
    double E = kepSolver(M, e);
    double E_expected = 220.512074767522 * M_PI/180;
    ASSERT_NEAR(E_expected, E, 1e-10);  // from Vallado
}

TEST(TestOrbitUtils, TrueAnomaly) {
    double M = 3.6029;
    double e = 0.37255;
    double ta = M_to_ta(M, e);
    ASSERT_NEAR(ta, 3.371, 1e-3);  // from Curtis Example 3.2
}

TEST(TestOrbitUtils, MeanAnomaly) {
    double e = 0.37255;  // convert back above case
    double ta = 3.37119;
    double M = ta_to_M(ta, e);
    ASSERT_NEAR(M, 3.6029, 1e-3);
}