#include <gtest/gtest.h>
#include <parse/TLE.hpp>
#include <orbit/StateVector.hpp>

TEST(TestTLE, GetData) {
    TLE tle(25544);
    StateVector sv = tle.get_orbit().to_sv(Body(5.972e24));
    std::cout << sv << std::endl;
}