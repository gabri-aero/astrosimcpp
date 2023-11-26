#include "Gravity.hpp"
#include <bodies/Body.hpp>

math::vector gravity(const Body& i, const Body& j) {
    // Compute relative position vector
    math::vector rij = j.get_pos() - i.get_pos();
    // Retrieve body mass
    double mi = i.get_mass();   
    double mj = j.get_mass();
    // Point-mass gravity
    return G*mj/pow(norm(rij), 3)*rij;
}