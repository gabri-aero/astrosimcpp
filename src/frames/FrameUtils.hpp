#ifndef _FRAME_UTILS_HPP_
#define _FRAME_UTILS_HPP_

#include <time/Epoch.hpp>
#include <math/Vector.hpp>
#include <time/TimeUtils.hpp>
#include <math/Utils.hpp>
#include <variant>

/**
 * \brief Compute Earth Rotation Angle according to Vallado (2013)
 * 
 * @param epoch Epoch object
*/
double era(const Epoch& epoch);  

/**
 * Compute transformation from spherical to cartesian coordinates
 * @param r radius
 * @param lambda longitude
 * @param phi latitude
 * 
 * @return Cartesian position vector: [x, y, z]
*/
math::vector sph2cart(double r, double lambda, double phi);

/**
 * Compute transformation from cartesian to spherical coordinates
 * @param r cartesian vector
 * 
 * @return A vector with the following components:
 *  - r: radius
 *  - lambda: longitude
 *  - phi: latitude
*/
math::vector cart2sph(math::vector r);

/**
 * Greenwich Mean Sidereal Time
 */
template <typename T>
T gmst(Epoch epoch);
double gmst(Epoch epoch);

/**
 * Local Solar Time
 */
template <typename T>
T lst(Epoch epoch, double longitude_deg);
double lst(Epoch epoch, double longitude_deg);

// Precesion-nutation theory fundamental angles
long double l(long double t);
long double lp(long double t);
long double F(long double t);
long double Om(long double t);
long double D(long double t);
long double L_Me(long double t);
long double L_Ve(long double t);
long double L_E(long double t);
long double L_Ma(long double t);
long double L_J(long double t);
long double L_Sa(long double t);
long double L_U(long double t);
long double L_Ne(long double t);
long double p_A(long double t);

#endif //_FRAME_UTILS_HPP_