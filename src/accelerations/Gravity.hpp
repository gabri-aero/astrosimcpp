#include <math/Vector.hpp>

#ifndef _GRAVITY_HPP_
#define _GRAVITY_HPP_

const float G = 6.673e-11; // Gravitational constant

class Body;  // forward declaration

/**
 * @brief Function to compute the gravitational acceleration caused
 * by body j in body i. Point-mass assumption taken.
 * 
 * @param i Body that experiences the acceleration
 * @param j Body thah creates the acceleration
*/
math::vector gravity(Body i, Body j);

#endif // _GRAVITY_HPP_
