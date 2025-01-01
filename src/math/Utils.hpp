#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <stdexcept>
#include <cmath>
#include <math/Vector.hpp>

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
 * @brief Conversion from arcseconds to degrees
 * @param as angle in arcseconds to be converted
*/
double as2deg(double as);

/**
 * @brief Conversion from degrees to arcseconds
 * @param deg angle in radians to be converted
*/
double deg2as(double rad);

/**
 * @brief Conversion from arcseconds to radians
 * @param as angle in arcseconds to be converted
*/
double as2rad(double as);

/**
 * @brief Conversion from radians to arcseconds
 * @param rad angle in radians to be converted
*/
double rad2as(double rad);

/**
 * @brief Wrap angle (rad) to [0, 2pi)
*/
double wrapTo2Pi(double angle);

/**
 * @brief Wrap angle (deg) to [0, 360)
*/
double wrapTo360(double angle_deg);

/**
 * @brief Compute sine from degrees
 */
double sind(double angle_deg);

/**
 * @brief Compute cosine from degrees
 */
double cosd(double angle_deg);

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