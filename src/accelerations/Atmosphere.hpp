#ifndef _ATMOSPHERE_HPP_
#define _ATMOSPHERE_HPP_

#include <math/Vector.hpp>

class Body;  // forward declaration


class Atmosphere {
public:
    virtual double density() = 0;
    
    virtual double temperature() = 0;
    
    virtual double pressure() = 0;
    
    virtual double speed_of_sound() = 0;

    /**
     * @brief Function to compute the aerodynamic acceleration caused
     * by the atmosphere of body j in body i.
     * 
     * @param i Body that experiences the acceleration
     * @param j Body thah creates the acceleration
     * 
     * @return 3D acceleration vector 
    */
    virtual math::vector aerodynamic_acceleration(const Body& i, const Body& j) = 0;
};

#endif // _ATMOSPHERE_HPP_
