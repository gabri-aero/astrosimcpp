#include "BaseIntegrator.hpp"

#ifndef _EULER_HPP_
#define _EULER_HPP_

/**
 * @class Euler
 * @brief Integrator that makes use of the Euler method
*/
class Euler: public BaseIntegrator {
public:
    using BaseIntegrator::BaseIntegrator;

    /**
     * @brief Euler method integration algorithm
     * @return next iteration result
    */
    std::pair<double, math::vector> integrate() override;
};

#endif // _EULER_HPP_
