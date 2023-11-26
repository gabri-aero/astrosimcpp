#include <stdexcept>
#include <cmath>
#include <math/Vector.hpp>

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

unsigned long long factorial(int n);
int C(int n, int k);
double rad2deg(double rad);
double deg2rad(double deg);
double wrapTo2Pi(double angle);

math::vector cart_to_sph(math::vector r_cart);
math::vector sph_to_cart(math::vector r_sph);

#endif //_UTILS_HPP_