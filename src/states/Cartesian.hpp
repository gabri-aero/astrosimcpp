#ifndef _STATE_VECTOR_HPP_
#define _STATE_VECTOR_HPP_

#include <bodies/Body.hpp>

// forward classes
class Keplerian; 
class Body;

/**
 * @class Cartesian
 * @brief It handles position and velocity
*/
class Cartesian : public math::vector {
public:
    /**
     * @brief Default constructor
    */
   Cartesian() = default;
    /**
     * @brief State vector constructor
    */
    Cartesian(double rx, double ry, double rz, double vx, double vy, double vz);
    /**
     * @brief State vector constructor
     * @param rv [x, y, z, vx, vy, vz]
    */
    Cartesian(math::vector rv);

    /**
     * @brief Conversion to orbital elements
     * @param central body around which the orbit is going to be computed
    */
    Keplerian to_keplerian(const Body& central);

    // Overload operators
    
    friend std::ostream& operator<<(std::ostream& os, const Cartesian& obj);
};

#endif //_STATE_VECTOR_HPP_