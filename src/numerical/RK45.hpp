#include "BaseIntegrator.hpp"

#ifndef _RK45_HPP_
#define _RK45_HPP_

class RK45: public BaseIntegrator {
    double tol;
public:
    RK45(double init_step, double tol) : BaseIntegrator(init_step), tol{tol} {};

    std::pair<double, math::vector> integrate() override;
};

#endif // _RK45_HPP_
