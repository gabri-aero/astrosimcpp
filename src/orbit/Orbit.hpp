#ifndef _ORBITAL_ELEMENTS_HPP
#define _ORBITAL_ELEMENTS_HPP

#include <math/Vector.hpp>
#include <bodies/Body.hpp>
#include <iostream>

class StateVector; // forward class
class Body;

enum OrbitType {
    ELLIPTICAL,
    PARABOLIC,
    HYPERBOLIC
};

/**
 * @class Orbit
 * @brief State representation as keplerian orbital elements: a, e, i, raan, aop, ta.
*/
class Orbit : public math::vector { // [a, e, i, raan, aop, ta]
public:
    /**
     * @brief Orbit constructor
     * @param a semi-major axis [m]
     * @param e eccentricity
     * @param i inclination [rad]
     * @param raan right ascension of ascending node [rad]
     * @param aop argument of periapsis [rad]
     * @param ta true anomaly [rad]
    */
    Orbit(double a, double e, double raan, double i, double aop, double ta); 
    // TO DO: correct mistake with raan, inc input argument position

    Orbit(math::vector oe);

    /**
     * @brief Gives type of orbit
     * @return ELLIPTICAL, PARABOLIC or HYPERBOLIC
    */
    OrbitType get_type() const;

    /**
     * @brief Conversion into state vector
     * @return [x, y, z, vx, vy, vz]
    */
    StateVector to_sv(const Body&);

    // Overload operators
    friend std::ostream& operator<<(std::ostream& os, const Orbit& obj);
};

#endif // _ORBITAL_ELEMENTS_HPP