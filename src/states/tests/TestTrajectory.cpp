#include <gtest/gtest.h>
#include <states/Trajectory.hpp>
#include <states/Cartesian.hpp>
#include <states/Keplerian.hpp>
#include <bodies/Body.hpp>

TEST(TestTrajectory, Test) {
    // Define state vectors and associated epochs
    Cartesian sv1{42e6, 0, 0, 0, 3e3, 0};
    Cartesian sv2{42.1e6, 0, 0, 0, 3e3, 0};
    Epoch epoch1{0, TAI, J2000};
    Epoch epoch2 = epoch1.add_secs(10);
    // Create trajectory object
    Trajectory trajectory;
    // Add elements
    trajectory.add(epoch1, sv1);
    trajectory.add(epoch2, sv2);
    // Create central body
    Body earth{5.97e24};
    // Convert to keplerian orbit time series
    TimeSeries<Keplerian> orbit_series = trajectory.to_keplerian(earth);
    // Assert
    ASSERT_EQ(orbit_series.at(0).first, epoch1.with_reference_epoch(J2000).with_timescale(TAI).get_days());
    ASSERT_EQ(orbit_series.at(0).second, sv1.to_keplerian(earth));
    ASSERT_EQ(orbit_series.at(1).first, epoch2.with_reference_epoch(J2000).with_timescale(TAI).get_days());
    ASSERT_EQ(orbit_series.at(1).second, sv2.to_keplerian(earth));
}