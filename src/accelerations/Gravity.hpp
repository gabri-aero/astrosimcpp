#include <math/Vector.hpp>

#ifndef _GRAVITY_HPP_
#define _GRAVITY_HPP_

const float G = 6.673e-11;

class Body;  // forward declaration

// Body i is the body where the gravity acceleration is computed
math::vector gravity(Body i, Body j);

#endif // _GRAVITY_HPP_
