#include "Trajectory.hpp"

TimeSeries<Keplerian> Trajectory::to_keplerian(const Body& central) {
    TimeSeries<Keplerian> kep_series; // create Keplerian elements time series
    double t; Cartesian sv; // define variables
    for(const std::pair<double, Cartesian>& data: *this) {
        t = data.first;
        sv = data.second;
        kep_series.add(t, sv.to_keplerian(central));
    }
    return kep_series;
}


Trajectory& Trajectory::operator=(const TimeSeries<Cartesian>& trajectory) { // TO DO: in principle, this should not be required but an error comes up
    this->clear();
    this->insert(this->begin(), trajectory.begin(), trajectory.end());
    return *this;
}