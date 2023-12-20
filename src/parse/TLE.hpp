#include <string>
#include <time/Epoch.hpp>
#include <orbit/Orbit.hpp>

#ifndef _TLE_HPP_
#define _TLE_HPP_

/**
 * @class TLE
 * @brief Class to handle TLE information. For now, it only enables TLE retrieval from www.celestrak.org and Orbit construction at TLE epoch.
*/
class TLE {
private:
    std::array<std::string, 3> lines;
    std::string int_designator;
    Epoch epoch;
    double n_dot;
    double n_ddot;
    double b_star;
    int set_number;
    int checksum;
    int norad_id;
    double i; // degrees
    double raan; // degrees
    double e;
    double aop;
    double M; // degrees
    double n; // rev per day
    int n_rev;

public:
    /**
     * @brief TLE constructor
     * @param norad_id
    */
    TLE(int norad_id);

    // Member functions

    /**
     * @brief Transform the TLE data into orbital elements and construct an orbit
     * @param body Earth
    */
    Orbit get_orbit(Body body=Body(5.972e24)) const;
    /**
     * @brief Getter for Epoch associated to TLE
    */
    Epoch get_epoch() const;

    // Overload operator<<
    friend std::ostream& operator<<(std::ostream& os, TLE& tle) {
        os << tle.lines[0] << std::endl << tle.lines[1] << std::endl << tle.lines[2];
        return os;
    }
};

#endif //_TLE_HPP_
