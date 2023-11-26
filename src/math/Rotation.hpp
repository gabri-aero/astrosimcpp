#include <math/Matrix.hpp>

// Pasive rotation matrices (used to express a vector into the rotated coordinate system)
// TO DO: enable both passive and active rotation matrices

/**
 * @brief Passive rotation matrix about the X axis
 * @param a - rotation angle
 * @return [3x3] rotation matrix
*/
math::matrix R1(double a) {
    return math::matrix{
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
math::matrix R2(double a) {
    return math::matrix{
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
math::matrix R3(double a) {
    return math::matrix{
        {cos(a), sin(a), 0},
        {-sin(a), cos(a), 0},
        {0, 0, 1}
    };
}