#ifndef _ORBITAL_ELEMENTS_HPP
#define _ORBITAL_ELEMENTS_HPP

#include <bodies/Body.hpp>
#include <iostream>

class Cartesian; // forward class
class Body;

/**
 * @class Keplerian
 * @brief State representation as keplerian orbital elements: a, e, i, raan, aop, ta.
*/
class Keplerian : public math::vector { // [a, e, i, raan, aop, ta]
public:
    /**
     * @brief Keplerian constructor
     * @param a semi-major axis [m]
     * @param e eccentricity
     * @param i inclination [rad]
     * @param raan right ascension of ascending node [rad]
     * @param aop argument of periapsis [rad]
     * @param ta true anomaly [rad]
    */
    Keplerian(double a, double e, double raan, double i, double aop, double ta); 
    // TO DO: correct mistake with raan, inc input argument position

    Keplerian(math::vector kep);

    /**
     * @brief Conversion into Cartesian state vector
     * @return [x, y, z, vx, vy, vz]
    */
    Cartesian to_cartesian(const Body&);

    // Overload operators
    friend std::ostream& operator<<(std::ostream& os, const Keplerian& obj);
};

#endif // _ORBITAL_ELEMENTS_HPP