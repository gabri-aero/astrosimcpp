#include "Trajectory.hpp"

TimeSeries<Orbit> Trajectory::to_orbit(const Body& central) {
    TimeSeries<Orbit> orbit_series; // create orbit time series
    double t; StateVector sv; // define variables
    for(const std::pair<double, StateVector>& data: *this) {
        t = data.first;
        sv = data.second;
        orbit_series.add(t, sv.to_orbit(central));
    }
    return orbit_series;
}


Trajectory& Trajectory::operator=(const TimeSeries<StateVector>& trajectory) { // TO DO: in principle, this should not be required but an error comes up
    this->clear();
    this->insert(this->begin(), trajectory.begin(), trajectory.end());
    return *this;
}