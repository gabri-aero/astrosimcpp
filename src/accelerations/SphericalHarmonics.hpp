#ifndef _SPHERICAL_HARMONICS_HPP_
#define _SPHERICAL_HARMONICS_HPP_

#include <accelerations/Gravity.hpp>
#include <math/Legendre.hpp>

class NaturalBody;

class SphericalHarmonics : public Gravity {
    ALP associated_legendre;
    int n_max;
    // Stokes coefficients
    math::matrix C;
    math::matrix S;
    // Brillouin sphere radius
    double R; 
    // Gravitational parameter
    double mu;
public:
    SphericalHarmonics(int n_max);
    SphericalHarmonics(std::string filename);
    math::vector gravity(const Body& i, const Body& j);
    void set_coefficients(math::matrix C, math::matrix S);
    math::matrix get_C() const;
    double get_C(int n, int m) const;
    math::matrix get_S() const;
    double get_S(int n, int m) const;
};



#endif // _SPHERICAL_HARMONICS_HPP_