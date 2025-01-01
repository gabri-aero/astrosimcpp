#ifndef _ROTATION_HPP_
#define _ROTATION_HPP_

#include <math/Matrix.hpp>

// Passive rotation matrices (used to express a vector into the rotated coordinate system)

/**
 * @brief Passive rotation matrix about the X axis
 * @param a - rotation angle
 * @return [3x3] rotation matrix
*/

template<typename T>
math::Matrix<T> R1(T a) {
    return math::Matrix<T>{
        {1, 0, 0},
        {0, cos(a), sin(a)},
        {0, -sin(a), cos(a)}
    };
}

/**
 * @brief Passive rotation matrix about the Y axis
 * @param a - rotation angle
 * @return [3x3] rotation matrix
*/

template<typename T>
math::Matrix<T> R2(T a) {
    return math::Matrix<T>{
        {cos(a), 0, -sin(a)},
        {0, 1, 0},
        {sin(a), 0, cos(a)}
    };
}

/**
 * @brief Passive rotation matrix about the Z axis
 * @param a - rotation angle
 * @return [3x3] rotation matrix
*/
template<typename T>
math::Matrix<T> R3(T a) {
    return math::Matrix<T>{
        {cos(a), sin(a), 0},
        {-sin(a), cos(a), 0},
        {0, 0, 1}
    };
}

#endif //_ROTATION_HPP_