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

TEST(TimeSeriesTest, Interpolation) {
    Epoch epoch{0, TAI, J2000};
    TimeSeries<double> time_series;
    double value = 13.4;
    double value2 = 15.7;
    time_series.add(epoch, value);
    time_series.add(epoch.add_days(1), value2);
    ASSERT_EQ(time_series.get(epoch.add_days(0.3)), 14.09);
}