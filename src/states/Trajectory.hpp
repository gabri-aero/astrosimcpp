#ifndef _TRAJECTORY_HPP_
#define _TRAJECTORY_HPP_

#include <time/TimeSeries.hpp>
#include <states/Cartesian.hpp>
#include <states/Keplerian.hpp>

class Trajectory : public TimeSeries<Cartesian> {
public:
    /**
     * This function converts a Cartesian TimeSeries (Trajectory) to the associated Keplerian TimeSeries given the central body
     * It applies the conversion to orbital elements to every Cartesian element to the Trajectory
     * @param central central body as reference for keplerian orbital elements calculation
    */
    TimeSeries<Keplerian> to_keplerian(const Body& central);

    Trajectory& operator=(const TimeSeries<Cartesian>& trajectory);

};

#endif //_TRAJECTORY_HPP_