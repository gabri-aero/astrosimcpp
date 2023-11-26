#include "BaseIntegrator.hpp"

#ifndef _RK45_HPP_
#define _RK45_HPP_

class RK45: public BaseIntegrator {
    double tol;
public:
    /**
     * @param init_step initial step size. It will be adapted by the method.
     * @param tol numerical error tolerance
    */
    RK45(double init_step, double tol) : BaseIntegrator(init_step), tol{tol} {}; // override parent constructor to enable tolerance set up

    /**
     * @brief RK45 method integration algorithm
     * @return next iteration result
    */
    std::pair<double, math::vector> integrate() override;
};

#endif // _RK45_HPP_
