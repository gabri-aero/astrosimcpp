#include <time/Epoch.hpp>

#ifndef _FRAME_UTILS_HPP_
#define _FRAME_UTILS_HPP_

/**
 * Compute Earth Rotation Angle according to Vallado (2013)
 * 
 * @param epoch Epoch object
*/
double era(const Epoch& epoch);  

#endif //_FRAME_UTILS_HPP_