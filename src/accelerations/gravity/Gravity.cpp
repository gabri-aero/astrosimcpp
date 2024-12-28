#include "Gravity.hpp"
#include <bodies/Body.hpp>

math::vector PointMass::gravity(const Body& i, const Body& j) {
    // Compute relative position vector
    math::vector rij = j.get_pos() - i.get_pos();
    // Retrieve body j gravitational constant
    double mu_j = j.get_mu();
    // Point-mass gravity
    return mu_j/pow(norm(rij), 3)*rij;
}