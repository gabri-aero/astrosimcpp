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

class Exponential: public Atmosphere {
private:
    double rho_0;
    double Hs;
public:
    Exponential(double rho_0, double Hs) {
        this->rho_0 = rho_0;
        this->Hs = Hs;
    };
    double density(double h) {
        return rho_0 * exp(-h/Hs);
    };
    double temperature() override {
        return 0;
    };
    double pressure() override {
        return 0;
    };
    double speed_of_sound() override {
        return 0;
    };
    math::vector aerodynamic_acceleration(const Body& i, const Body& j) override {
        return math::vector{0, 0, 0};
    }
};

#endif // _ATMOSPHERE_HPP_
