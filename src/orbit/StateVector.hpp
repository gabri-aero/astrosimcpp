#include <math/Vector.hpp>
#include <bodies/Body.hpp>

#ifndef _STATE_VECTOR_HPP_
#define _STATE_VECTOR_HPP_

// forward classes
class Orbit; 
class Body;

/**
 * @class StateVector
 * @brief It handles position and velocity
*/
class StateVector {
    math::vector rv; // [x, y, z, vx, vy, vz]
public:
    /**
     * @brief Default constructor
    */
   StateVector() = default;
    /**
     * @brief State vector constructor
    */
    StateVector(double rx, double ry, double rz, double vx, double vy, double vz);
    /**
     * @brief State vector constructor
     * @param rv [x, y, z, vx, vy, vz]
    */
    StateVector(math::vector rv);

    /**
     * @brief Position velocity getter
     * @return [x, y, z, vx, vy, vz]
    */
    math::vector get_rv() const;

    /**
     * @brief Conversion to orbital elements
     * @param central body around which the orbit is going to be computed
    */
    Orbit to_orbit(const Body& central);

    // Overload operators
    
    friend std::ostream& operator<<(std::ostream& os, const StateVector& obj);
};

#endif //_STATE_VECTOR_HPP_