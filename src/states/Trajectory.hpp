#ifndef _TRAJECTORY_HPP_
#define _TRAJECTORY_HPP_

#include <time/TimeSeries.hpp>
#include <orbit/StateVector.hpp>
#include <orbit/Orbit.hpp>

class Trajectory : public TimeSeries<StateVector> {
public:
    /**
     * This function converts a StateVector TimeSeries (Trajectory) to the associated Orbit TimeSeries given the central body
     * It applies the conversion to orbital elements to every StateVector element to the Trajectory
     * @param central central body as reference for keplerian orbital elements calculation
    */
    TimeSeries<Orbit> to_orbit(const Body& central);

    Trajectory& operator=(const TimeSeries<StateVector>& trajectory);

};

#endif //_TRAJECTORY_HPP_