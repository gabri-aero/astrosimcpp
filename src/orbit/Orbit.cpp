#include "Orbit.hpp"
#include "StateVector.hpp"

#include <iomanip>
#include <math/Utils.hpp>
#include <math/Rotation.hpp>

Orbit::Orbit(double a, double e, double raan, double i, double aop, double ta) 
    : oe{math::vector{a, e, raan, i, aop, ta}}{

}

math::vector Orbit::get_oe() {
    return oe;
}

OrbitType Orbit::get_type() {
    double a = oe.at(0);
    if(a < 0) {
        return OrbitType::HYPERBOLIC;
    } else if (a > 0) {
        return OrbitType::ELLIPTICAL;
    } else {
        return OrbitType::PARABOLIC; // numerically not likely to happen...
    }
}

StateVector Orbit::to_sv(Body body) {
    double a = oe.at(0);
    double e = oe.at(1);
    double raan = oe.at(2);
    double i = oe.at(3);
    double aop = oe.at(4);
    double ta = oe.at(5);

    // Orbital plane
    double r = a*(1-pow(e,2)) / (1+e*cos(ta));  // scalar r and v
    double v = sqrt(body.get_mu()*(2/r - 1/a));
    math::vector ur{cos(ta), sin(ta), 0}; // polar coordinates unary vectors
    math::vector ut{-sin(ta), cos(ta), 0};
    auto r_orb = r*ur; // position vector
    double gamma = atan2(e*sin(ta), 1+e*cos(ta)); // flight path angle
    auto uv = cos(gamma)*ut + sin(gamma)*ur;
    auto v_orb = v*uv; // velocity vector

    // Rotate from orbital plane orientation
    auto L = R3(-raan)*R1(-i)*R3(-aop); // rotation matrix into space-fixed frame
    auto r_vec = L*r_orb;
    auto v_vec = L*v_orb;

    return StateVector{
        r_vec.at(0),
        r_vec.at(1),
        r_vec.at(2),
        v_vec.at(0),
        v_vec.at(1),
        v_vec.at(2)
    };
}

bool Orbit::operator==(const Orbit& obj) {
    return this->oe == obj.oe;
}

std::ostream& operator<<(std::ostream& os, const Orbit& obj) {
    os << "a : " << std::fixed << std::setprecision(3) << obj.oe[0] * 1e-3 << " km" << std::endl;
    os << "e : " << std::fixed << std::setprecision(6) << obj.oe[1] << std::endl;
    os << "RAAN : " << std::fixed << std::setprecision(3) << rad2deg(obj.oe[2]) << " deg" << std::endl;
    os << "i : " << std::fixed << rad2deg(obj.oe[3]) << " deg" << std::endl;
    os << "aop : " << std::fixed << rad2deg(obj.oe[4]) << " deg" << std::endl;
    os << "ta : " << std::fixed << rad2deg(obj.oe[5]) << " deg" << std::endl;
    return os;
}


