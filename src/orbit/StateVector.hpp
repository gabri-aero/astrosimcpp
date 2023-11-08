#include <math/Vector.hpp>
#include <bodies/Body.hpp>

#ifndef _STATE_VECTOR_HPP_
#define _STATE_VECTOR_HPP_

class Orbit; // forward class

class StateVector {
    math::vector rv;
public:
    StateVector(double rx, double ry, double rz, double vx, double vy, double vz);
    StateVector(math::vector rv);
    math::vector get_rv() const;
    Orbit to_orbit(Body central);
    friend std::ostream& operator<<(std::ostream& os, const StateVector& obj);
};

#endif //_STATE_VECTOR_HPP_