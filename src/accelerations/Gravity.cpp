#include "Gravity.hpp"
#include <bodies/Body.hpp>

math::vector gravity(Body i, Body j) {
    math::vector rij = j.get_pos() - i.get_pos();
    double mi = i.get_mass();   
    double mj = j.get_mass();
    return G*mj/pow(norm(rij), 3)*rij;
}