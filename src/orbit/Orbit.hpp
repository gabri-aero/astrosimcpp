#include <math/Vector.hpp>
#include <bodies/Body.hpp>
#include <time/Epoch.hpp>
#include <iostream>

#ifndef _ORBITAL_ELEMENTS_HPP
#define _ORBITAL_ELEMENTS_HPP

class StateVector; // forward class

enum OrbitType {
    ELLIPTICAL,
    PARABOLIC,
    HYPERBOLIC
};

class Orbit {
    Epoch epoch;
    math::vector oe;
public:
    Orbit(double a, double e, double raan, double i, double aop, double ta, Epoch epoch=Epoch());
    math::vector get_oe() const;
    Epoch get_epoch() const;
    OrbitType get_type() const;
    StateVector to_sv(Body);
    bool operator==(const Orbit& obj);
    friend std::ostream& operator<<(std::ostream& os, const Orbit& obj);
};

#endif // _ORBITAL_ELEMENTS_HPP