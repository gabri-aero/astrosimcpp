#include "BaseIntegrator.hpp"

#ifndef _RK4_HPP_
#define _RK4_HPP_

class RK4: public BaseIntegrator {
public:
    using BaseIntegrator::BaseIntegrator;

    std::pair<double, math::vector> integrate() override;
};

#endif // _RK4_HPP_
