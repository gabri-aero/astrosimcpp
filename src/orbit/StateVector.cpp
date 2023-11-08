#include "StateVector.hpp"
#include "Orbit.hpp"
#include <bodies/Body.hpp>

StateVector::StateVector(double rx, double ry, double rz, double vx, double vy, double vz) 
    : rv{math::vector{rx, ry, rz, vx, vy, vz}} {
}

StateVector::StateVector(math::vector rv) 
    : rv{rv} {
}

math::vector StateVector::get_rv() const {
    return rv;
}

Orbit StateVector::to_orbit(Body central) {
    math::vector r_vec = rv.subvec(0,3);
    math::vector v_vec = rv.subvec(3,6);
    double r = norm(r_vec);
    double v = norm(v_vec);
    // Compute angular momentum 
    math::vector h_vec = cross(r_vec, v_vec);
    double h = norm(h_vec);
    // Retrieve mu
    double mu = central.get_mu();
    // Compute semi-major axis
    double a = 1 / (-pow(v, 2)/mu + 2/r);
    // Compute eccentricity
    math::vector e_vec = cross(v_vec, h_vec)/mu - r_vec/r;
    double e = norm(e_vec);

    // Make use of perifocal frame
    double i, raan, aop, ta;
    math::vector ip, jp, kp, ur;
    kp = h_vec/h;
    i = acos(kp[2]);   // Compute inclination
    if (i == 0) {
        raan = 0; // Zero-inclination exception
    } else {
        raan = atan2(kp[0], -kp[1]); // Right ascension of ascending node
    }
    if (e==0) {
        ip = math::vector{cos(raan), sin(raan), 0}; // Circular orbit exception
    } else {
        ip = e_vec/e; // Perifocal X-axis
    }
    jp = cross(kp, ip);
    // Define radial unary vector
    ur = r_vec/r;
    // Compute argument of periapsis
    if (i==0) {
        math::vector raan_vec{cos(raan), sin(raan), 0};
        aop = atan2(dot(cross(raan_vec, ip), kp), dot(raan_vec, ip));
    } else {
        aop = atan2(ip[2], jp[2]);
    }
    ta = atan2(dot(cross(ip, ur), kp), dot(ip, ur));

    // Check angles range
    if (i<0) {
        i += M_PI;
    }
    if (raan < 0) {
        raan += 2 * M_PI;
    }
    if (aop < 0) {
        aop += 2* M_PI;
    }
    if (ta < 0) {
        ta += 2 * M_PI;
    }

    return Orbit{a, e, raan, i, aop, ta};
}

std::ostream& operator<<(std::ostream& os, const StateVector& obj) {
    os << "r: " << obj.rv.subvec(0, 3) << std::endl << "v: " << obj.rv.subvec(3, 6) << std::endl;
    return os;
}