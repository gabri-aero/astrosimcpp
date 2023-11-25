#include <math/Vector.hpp>
#include <bodies/Body.hpp>
#include <time/Epoch.hpp>

#ifndef _STATE_VECTOR_HPP_
#define _STATE_VECTOR_HPP_

class Orbit; // forward class

class StateVector {
    Epoch epoch;
    math::vector rv;
public:
    StateVector(double rx, double ry, double rz, double vx, double vy, double vz, Epoch epoch=Epoch());
    StateVector(math::vector rv, Epoch epoch);
    math::vector get_rv() const;
    Epoch get_epoch() const;
    Orbit to_orbit(Body central);
    friend std::ostream& operator<<(std::ostream& os, const StateVector& obj);
};

#endif //_STATE_VECTOR_HPP_