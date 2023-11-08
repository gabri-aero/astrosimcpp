#include <math/Legendre.hpp>

#ifndef _SPHERICAL_HARMONICS_HPP
#define _SPHERICAL_HARMONICS_HPP

double spherical_harmonics(int l, int m, double theta, double phi) {
    if (m>=0) {
        return legendre(l, m, cos(theta)) * cos(m*phi);
    } else {
        return legendre(l, abs(m), cos(theta)) * sin(m*phi);
    }
}

#endif //_SPHERICAL_HARMONICS_HPP