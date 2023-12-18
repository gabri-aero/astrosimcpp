#include <time/TimeSeries.hpp>
#include <orbit/Orbit.hpp>
#include <gtest/gtest.h>
#include <iostream>

TEST(TimeSeriesTest, Test) {
    Epoch epoch{0, TAI, J2000};
    TimeSeries<float> time_series;
    float value = 13.4;
    time_series.add(epoch, value);
    ASSERT_EQ(time_series.size(), 1);
    ASSERT_EQ(time_series.at(0).first, epoch);
    ASSERT_EQ(time_series.at(0).second, value);
}