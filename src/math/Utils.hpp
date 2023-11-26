#include <stdexcept>
#include <cmath>
#include <math/Vector.hpp>

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

/**
 * @brief Computation of factorial number n!
 * @param n
*/
unsigned long long factorial(int n);

/**
 * @brief Compute combinatorial number n over k
 * @param n
 * @param k
*/
int C(int n, int k);

/**
 * @brief Conversion from radians to degrees
 * @param rad angle in radians to be converted
*/
double rad2deg(double rad);

/**
 * @brief Conversion from degrees to radians
 * @param deg angle in degrees to be converted
*/
double deg2rad(double deg);

/**
 * @brief Wrap angle to [0, 2pi)
*/
double wrapTo2Pi(double angle);

/**
 * @brief Conversion from cartesian coordinates to spherical
 * @param cart [x, y, z] coordinates
 * @return [r, longitude, latitude]
*/
math::vector cart_to_sph(math::vector cart);
/**
 * @brief Conversion from spherical coordinates to cartesian
 * @param sph [r, longitude, latitude]
 * @return [x, y, z] coordinates
*/
math::vector sph_to_cart(math::vector sph);

#endif //_UTILS_HPP_