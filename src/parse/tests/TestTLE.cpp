#include <gtest/gtest.h>
#include <parse/TLE.hpp>
#include <states/Cartesian.hpp>

TEST(TestTLE, GetData) {
    TLE tle(25544);
    Cartesian sv = tle.get_keplerian().to_cartesian(Body(5.972e24));
    std::cout << sv << std::endl;
    std::cout << tle.get_epoch() << std::endl;
}