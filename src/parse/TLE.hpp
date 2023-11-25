#include <string>
#include <time/Epoch.hpp>

#ifndef _TLE_HPP_
#define _TLE_HPP_

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
    TLE(int norad_id);

    // Overload operator<<
    friend std::ostream& operator<<(std::ostream& os, TLE& tle) {
        os << tle.lines[0] << std::endl << tle.lines[1] << std::endl << tle.lines[2];
        return os;
    }
};

#endif //_TLE_HPP_
