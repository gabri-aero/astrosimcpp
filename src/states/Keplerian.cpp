#include "Keplerian.hpp"
#include "Cartesian.hpp"

#include <iomanip>
#include <math/Utils.hpp>
#include <math/Rotation.hpp>

Keplerian::Keplerian(double a, double e, double raan, double i, double aop, double ta) {
    this->assign({a, e, raan, i, aop, ta});
}

Keplerian::Keplerian(math::vector kep) {
    this->assign({kep.at(0), kep.at(1), kep.at(2), kep.at(3), kep.at(4), kep.at(5)});
}

Cartesian Keplerian::to_cartesian(const Body& body) {
    // Retrieve orbital elements
    double a = this->at(0);
    double e = this->at(1);
    double raan = this->at(2);
    double i = this->at(3);
    double aop = this->at(4);
    double ta = this->at(5);

    // Keplerianal plane
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

    // Arrange cartesian state vector
    return Cartesian{
        r_vec.at(0),
        r_vec.at(1),
        r_vec.at(2),
        v_vec.at(0),
        v_vec.at(1),
        v_vec.at(2)
    };
}

std::ostream& operator<<(std::ostream& os, const Keplerian& obj) {
    os << "a : " << std::fixed << std::setprecision(3) << obj[0] * 1e-3 << " km" << std::endl;
    os << "e : " << std::fixed << std::setprecision(6) << obj[1] << std::endl;
    os << "RAAN : " << std::fixed << std::setprecision(3) << rad2deg(obj[2]) << " deg" << std::endl;
    os << "i : " << std::fixed << rad2deg(obj[3]) << " deg" << std::endl;
    os << "aop : " << std::fixed << rad2deg(obj[4]) << " deg" << std::endl;
    os << "ta : " << std::fixed << rad2deg(obj[5]) << " deg" << std::endl;
    return os;
}


