#include <gtest/gtest.h>
#include <numerical/Euler.hpp>

// simple function case
math::vector dX(double t, math::vector X) {
    math::vector dX(X.size());
    dX.at(0) = X.at(0);
    dX.at(1) = 0.5 * X.at(1);
    return dX;
};

TEST(EulerTest, Integration) {
    Euler integrator{1};
    integrator.set_ic(0, {1, 2});
    integrator.set_dX(dX);
    integrator.run(1);
    std::cout << integrator.get_data().back().second << std::endl;
}