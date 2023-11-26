#include <math/Vector.hpp>
#include <bodies/Body.hpp>
#include <time/Epoch.hpp>

#ifndef _STATE_VECTOR_HPP_
#define _STATE_VECTOR_HPP_

// forward classes
class Orbit; 
class Body;

/**
 * @class StateVector
 * @brief It handles position and velocity with a Epoch time stamp
*/
class StateVector {
    Epoch epoch;
    math::vector rv; // [x, y, z, vx, vy, vz]
public:
    /**
     * @brief State vector constructor
    */
    StateVector(double rx, double ry, double rz, double vx, double vy, double vz, Epoch epoch=Epoch());
    /**
     * @brief State vector constructor
     * @param rv [x, y, z, vx, vy, vz]
     * @param epoch
    */
    StateVector(math::vector rv, Epoch epoch);

    /**
     * @brief Position velocity getter
     * @return [x, y, z, vx, vy, vz]
    */
    math::vector get_rv() const;

    /**
     * @brief Epoch getter
    */
    Epoch get_epoch() const;

    /**
     * @brief Conversion to orbital elements
     * @param central body around which the orbit is going to be computed
     * @return Orbit object with the associated epoch
    */
    Orbit to_orbit(const Body& central);

    // Overload operators
    
    friend std::ostream& operator<<(std::ostream& os, const StateVector& obj);
};

#endif //_STATE_VECTOR_HPP_