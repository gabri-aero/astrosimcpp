#ifndef _GRAVITY_HPP_
#define _GRAVITY_HPP_

#include <math/Vector.hpp>

const double G = 6.673e-11; // Gravitational constant

class Body;  // forward declaration


class Gravity {
public:
    /**
     * @brief Function to compute the gravitational acceleration caused
     * by body j in body i.
     * 
     * @param i Body that experiences the acceleration
     * @param j Body thah creates the acceleration
     * 
     * @return 3D acceleration vector 
    */
    virtual math::vector gravity(const Body& i, const Body& j) = 0;
};

class PointMass : public Gravity {
public:
    math::vector gravity(const Body& i, const Body& j) override final;
};

#endif // _GRAVITY_HPP_
