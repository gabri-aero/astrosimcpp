#include <time/TimeSeries.hpp>
#include <orbit/StateVector.hpp>
#include <orbit/Orbit.hpp>

#ifndef _TRAJECTORY_HPP_
#define _TRAJECTORY_HPP_

class Trajectory : public TimeSeries<StateVector> {

public:
    /**
     * This function converts a StateVector TimeSeries (Trajectory) to the associated Orbit TimeSeries given the central body
     * It applies the conversion to orbital elements to every StateVector element to the Trajectory
     * @param central central body as reference for keplerian orbital elements calculation
    */
    TimeSeries<Orbit> to_orbit(const Body& central) {
        TimeSeries<Orbit> orbit_series; // create orbit time series
        Epoch epoch; StateVector sv; // define variables
        for(const std::pair<Epoch, StateVector>& data: *this) {
            epoch = data.first;
            sv = data.second;
            orbit_series.add(epoch, sv.to_orbit(central));
        }
        return orbit_series;
    }
};

#endif //_TRAJECTORY_HPP_