#ifndef _FRAME_UTILS_HPP_
#define _FRAME_UTILS_HPP_

#include <time/Epoch.hpp>
#include <math/Vector.hpp>

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

#endif //_FRAME_UTILS_HPP_